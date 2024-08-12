//
// Created by goksu on 4/6/19.
//

#include "rasterizer.hpp"

#include <math.h>

#include <algorithm>
#include <opencv2/opencv.hpp>
#include <vector>

rst::pos_buf_id rst::rasterizer::load_positions(
    const std::vector<Eigen::Vector3f>& positions) {
  auto id = get_next_id();
  pos_buf.emplace(id, positions);

  return {id};
}

rst::ind_buf_id rst::rasterizer::load_indices(
    const std::vector<Eigen::Vector3i>& indices) {
  auto id = get_next_id();
  ind_buf.emplace(id, indices);

  return {id};
}

rst::col_buf_id rst::rasterizer::load_colors(
    const std::vector<Eigen::Vector3f>& cols) {
  auto id = get_next_id();
  col_buf.emplace(id, cols);

  return {id};
}

auto to_vec4(const Eigen::Vector3f& v3, float w = 1.0f) {
  return Vector4f(v3.x(), v3.y(), v3.z(), w);
}

static bool insideTriangle(float x, float y, const Vector3f* _v) {
  // TODO: Implement this function to check if the point (x, y) is inside the
  // triangle represented by _v[0], _v[1], _v[2]
  /**
   * z = x1 * y2 - y1 * x2
   * x1 = xb - xa, y1 = yb - ya
   * x2 = xp - xa, y2 = yp - ya
   * z = (xb - xa) * (yp - ya) - (yb - ya) * (xp - xa)
   */
  float crossZ0 = (_v[1].x() - _v[0].x()) * (y - _v[0].y()) -
                  (_v[1].y() - _v[0].y()) * (x - _v[0].x());
  float crossZ1 = (_v[2].x() - _v[1].x()) * (y - _v[1].y()) -
                  (_v[2].y() - _v[1].y()) * (x - _v[1].x());
  float crossZ2 = (_v[0].x() - _v[2].x()) * (y - _v[2].y()) -
                  (_v[0].y() - _v[2].y()) * (x - _v[2].x());

  if (crossZ0 >= 0 && crossZ1 >= 0 && crossZ2 >= 0) return true;

  return crossZ0 <= 0 && crossZ1 <= 0 && crossZ2 <= 0;
}

static std::tuple<float, float, float> computeBarycentric2D(float x, float y,
                                                            const Vector3f* v) {
  float c1 =
      (x * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * y +
       v[1].x() * v[2].y() - v[2].x() * v[1].y()) /
      (v[0].x() * (v[1].y() - v[2].y()) + (v[2].x() - v[1].x()) * v[0].y() +
       v[1].x() * v[2].y() - v[2].x() * v[1].y());
  float c2 =
      (x * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * y +
       v[2].x() * v[0].y() - v[0].x() * v[2].y()) /
      (v[1].x() * (v[2].y() - v[0].y()) + (v[0].x() - v[2].x()) * v[1].y() +
       v[2].x() * v[0].y() - v[0].x() * v[2].y());
  float c3 =
      (x * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * y +
       v[0].x() * v[1].y() - v[1].x() * v[0].y()) /
      (v[2].x() * (v[0].y() - v[1].y()) + (v[1].x() - v[0].x()) * v[2].y() +
       v[0].x() * v[1].y() - v[1].x() * v[0].y());
  return {c1, c2, c3};
}

void rst::rasterizer::draw(pos_buf_id pos_buffer, ind_buf_id ind_buffer,
                           col_buf_id col_buffer, Primitive type) {
  auto& buf = pos_buf[pos_buffer.pos_id];
  auto& ind = ind_buf[ind_buffer.ind_id];
  auto& col = col_buf[col_buffer.col_id];

  float f1 = (50 - 0.1) / 2.0;
  float f2 = (50 + 0.1) / 2.0;

  Eigen::Matrix4f mvp = projection * view * model;
  for (auto& i : ind) {
    Triangle t;
    Eigen::Vector4f v[] = {mvp * to_vec4(buf[i[0]], 1.0f),
                           mvp * to_vec4(buf[i[1]], 1.0f),
                           mvp * to_vec4(buf[i[2]], 1.0f)};
    // Homogeneous division
    for (auto& vec : v) {
      vec /= vec.w();
    }
    // Viewport transformation
    for (auto& vert : v) {
      vert.x() = 0.5 * width * (vert.x() + 1.0);
      vert.y() = 0.5 * height * (vert.y() + 1.0);
      vert.z() = vert.z() * f1 + f2;
    }

    for (int i = 0; i < 3; ++i) {
      t.setVertex(i, v[i].head<3>());
      t.setVertex(i, v[i].head<3>());
      t.setVertex(i, v[i].head<3>());
    }

    auto col_x = col[i[0]];
    auto col_y = col[i[1]];
    auto col_z = col[i[2]];

    t.setColor(0, col_x[0], col_x[1], col_x[2]);
    t.setColor(1, col_y[0], col_y[1], col_y[2]);
    t.setColor(2, col_z[0], col_z[1], col_z[2]);

    rasterize_triangle(t);
  }

  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      int index = get_index(x, y);

      for (int i = 1; i < msaa_level * msaa_level; i++) {
        frame_bufs[0][index] += frame_bufs[i][index];
      }

      frame_bufs[0][index] /= msaa_level * msaa_level;
    }
  }
}

// Screen space rasterization
void rst::rasterizer::rasterize_triangle(const Triangle& t) {
  auto v = t.toVector4();

  // MAX: Find the bounding box
  float top = v[0].y();
  float right = v[0].x();
  float bottom = v[0].y();
  float left = v[0].x();

  for (int i = 1; i < 3; i++) {
    top = std::max(top, v[i].y());
    right = std::max(right, v[i].x());
    bottom = std::min(bottom, v[i].y());
    left = std::min(left, v[i].x());
  }

  for (int x = left; x <= right; x++) {
    for (int y = bottom; y <= top; y++) {
      for (int i = 0; i < msaa_level; i++) {
        float x_shift = x + mass_shifts[i];

        for (int j = 0; j < msaa_level; j++) {
          float y_shift = y + mass_shifts[j];

          if (!insideTriangle(x_shift, y_shift, t.v)) continue;

          //  MAX: 助教給的 z 插值程式碼
          auto [alpha, beta, gamma] =
              computeBarycentric2D(x_shift, y_shift, t.v);
          float w_reciprocal =
              1.0 / (alpha / v[0].w() + beta / v[1].w() + gamma / v[2].w());
          float z_interpolated = alpha * v[0].z() / v[0].w() +
                                 beta * v[1].z() / v[1].w() +
                                 gamma * v[2].z() / v[2].w();
          z_interpolated *= w_reciprocal;

          int index = get_index(x, y);
          int buffer_index = i * msaa_level + j;

          if (z_interpolated < depth_bufs[buffer_index][index]) continue;
          frame_bufs[buffer_index][index] = t.getColor();
          depth_bufs[buffer_index][index] = z_interpolated;
        }
      }
    }
  }
}

void rst::rasterizer::set_model(const Eigen::Matrix4f& m) { model = m; }

void rst::rasterizer::set_view(const Eigen::Matrix4f& v) { view = v; }

void rst::rasterizer::set_projection(const Eigen::Matrix4f& p) {
  projection = p;
}

void rst::rasterizer::clear(rst::Buffers buff) {
  if ((buff & rst::Buffers::Color) == rst::Buffers::Color) {
    for (std::vector<Eigen::Vector3f>& frame_buf : frame_bufs) {
      int size = frame_buf.size();
      std::fill(frame_buf.begin(), frame_buf.end(), Eigen::Vector3f{0, 0, 0});
    }
  }
  if ((buff & rst::Buffers::Depth) == rst::Buffers::Depth) {
    for (std::vector<float>& depth_buf : depth_bufs) {
      std::fill(depth_buf.begin(), depth_buf.end(),
                std::numeric_limits<float>::infinity() * -1.0);
    }
  }
}

rst::rasterizer::rasterizer(int w, int h, int msaa_level) {
  this->width = w;
  this->height = h;
  this->msaa_level = msaa_level;

  /**
   * 取樣點
   * 1 => 0.50
   * 2 => 0.33 0.66
   * 3 => 0.25 0.50 0.75
   */

  for (int i = 0; i < msaa_level; i++) {
    mass_shifts.push_back(1.0 / (msaa_level + 1) * (i + 1));
  }

  frame_bufs.resize(msaa_level * msaa_level);
  depth_bufs.resize(msaa_level * msaa_level);
  for (int i = 0; i < msaa_level * msaa_level; i++) {
    frame_bufs[i] = std::vector<Eigen::Vector3f>(w * h);
    depth_bufs[i] = std::vector<float>(w * h);
  }
}

int rst::rasterizer::get_index(int x, int y) {
  return (height - 1 - y) * width + x;
}
