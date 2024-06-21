#include <Eigen/Eigen>
#include <iostream>
#include <opencv2/opencv.hpp>

#include "Triangle.hpp"
#include "rasterizer.hpp"

constexpr double MY_PI = 3.1415926;

Eigen::Matrix4f get_view_matrix(Eigen::Vector3f eye_pos) {
  Eigen::Matrix4f view = Eigen::Matrix4f::Identity();

  Eigen::Matrix4f translate;
  translate << 1, 0, 0, -eye_pos[0], 0, 1, 0, -eye_pos[1], 0, 0, 1, -eye_pos[2],
      0, 0, 0, 1;

  view = translate * view;

  return view;
}

// MAX: rotation_angle 是 +10 + 10 應該也是 degree
Eigen::Matrix4f get_model_matrix(float rotation_angle) {
  Eigen::Matrix4f model = Eigen::Matrix4f::Identity();
  float radian = rotation_angle * 180 / MY_PI;
  model << cos(radian), -sin(radian), 0.0, 0.0,  //
      sin(radian), cos(radian), 0.0, 0.0,        //
      0.0, 0.0, 1.0, 0.0,                        //
      0.0, 0.0, 0.0, 1.0;

  return model;
}

/**
 * MAX:
 * 後續程式碼呼叫是 get_projection_matrix(45, 1, 0.1, 50)
 * 所以 eye_fov 是 degree
 * 投影矩陣是 [
 *   [n, 0,     0,     0],
 *   [0, n,     0,     0],
 *   [0, 0, n + f, -1 * n * f],
 *   [0, 0,     1,     0]
 * ]
 */
Eigen::Matrix4f get_projection_matrix(float eye_fov, float aspect_ratio,
                                      float zNear, float zFar) {
  Eigen::Matrix4f projection = Eigen::Matrix4f::Identity();

  projection << zNear, 0.0, 0.0, 0.0,             //
      0.0, zNear, 0.0, 0.0,                       //
      0.0, 0.0, zNear + zFar, -1 * zNear * zFar,  //
      0.0, 0.0, 1.0, 0.0;

  /**
   * MAX:
   * 接下來把空間縮放進 NDC
   * height = abs(zNear) * tan(eye_fov) * 2
   * width = height * aspect_ratio
   * length = zNear - zFar
   */
  float eye_fov_radian = eye_fov * 180 / MY_PI;
  float height = abs(zNear) * tan(eye_fov_radian) * 2;
  float width = height * aspect_ratio;
  float length = zNear - zFar;

  Eigen::Matrix4f ndc;
  ndc << 2.0 / width, 0, 0, 0,  //
      0, 2.0 / height, 0, 0,    //
      0, 0, 2.0 / length, 0,    //
      0, 0, 0, 1;

  return ndc * projection;
}

Eigen::Matrix4f get_rotation(Eigen::Vector3f axis, float angle) {
  float cosX = axis[2] / sqrt(axis[1] * axis[1] + axis[2] * axis[2]);
  float sinX = axis[1] / sqrt(axis[1] * axis[1] + axis[2] * axis[2]);
  Matrix4f rotAxisToXZ;
  rotAxisToXZ << 1, 0, 0, 0,  //
      0, cosX, -sinX, 0,      //
      0, sinX, cosX, 0,       //
      0, 0, 0, 1;

  float cosY = sqrt(axis[1] * axis[1] + axis[2] * axis[2]) /
               sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
  float sinY =
      axis[0] / sqrt(axis[0] * axis[0] + axis[1] * axis[1] + axis[2] * axis[2]);
  Matrix4f rotXZToZ;
  rotXZToZ << cosY, 0, -sinY, 0,  //
      0, 1, 0, 0,                 //
      sinY, 0, cosY, 0,           //
      0, 0, 0, 1;

  Matrix4f rotAxisToZ = rotXZToZ * rotAxisToXZ;
  Matrix4f rotZToAxis = rotAxisToZ.transpose();

  Matrix4f rotAroundZ;
  rotAroundZ << cos(angle), -sin(angle), 0, 0,  //
      sin(angle), cos(angle), 0, 0,             //
      0, 0, 1, 0,                               //
      0, 0, 0, 1;

  return rotZToAxis * rotAroundZ * rotAxisToZ;
}

int main(int argc, const char** argv) {
  float angle = 0;
  bool command_line = false;
  std::string filename = "output.png";

  if (argc >= 3) {
    command_line = true;
    angle = std::stof(argv[2]);  // -r by default
    if (argc == 4) {
      filename = std::string(argv[3]);
    } else
      return 0;
  }

  rst::rasterizer r(700, 700);

  Eigen::Vector3f eye_pos = {0, 0, 5};

  std::vector<Eigen::Vector3f> pos{{2, 0, -2}, {0, 2, -2}, {-2, 0, -2}};

  std::vector<Eigen::Vector3i> ind{{0, 1, 2}};

  auto pos_id = r.load_positions(pos);
  auto ind_id = r.load_indices(ind);

  int key = 0;
  int frame_count = 0;

  if (command_line) {
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);

    r.set_model(get_model_matrix(angle));
    r.set_view(get_view_matrix(eye_pos));
    r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

    r.draw(pos_id, ind_id, rst::Primitive::Triangle);
    cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
    image.convertTo(image, CV_8UC3, 1.0f);

    cv::imwrite(filename, image);

    return 0;
  }

  while (key != 27) {
    r.clear(rst::Buffers::Color | rst::Buffers::Depth);

    r.set_model(get_model_matrix(angle));
    r.set_view(get_view_matrix(eye_pos));
    // MAX: 幹怎麼正的
    r.set_projection(get_projection_matrix(45, 1, 0.1, 50));

    r.draw(pos_id, ind_id, rst::Primitive::Triangle);

    cv::Mat image(700, 700, CV_32FC3, r.frame_buffer().data());
    image.convertTo(image, CV_8UC3, 1.0f);
    cv::imshow("image", image);
    key = cv::waitKey(10);

    std::cout << "frame count: " << frame_count++ << '\n';

    if (key == 'a') {
      angle += 10;
    } else if (key == 'd') {
      angle -= 10;
    }
  }

  return 0;
}
