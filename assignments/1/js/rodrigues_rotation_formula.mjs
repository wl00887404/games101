import matrix from './libs/matrix.mjs';
import vector from './libs/vector.mjs';

export const get_rotation = (N, degree) => {
  const [nx, ny, nz] = N;
  const radian = (degree / 180) * Math.PI;
  const cosTheta = Math.cos(radian);
  const sinTheta = Math.sin(radian);

  const part1 = [
    [cosTheta, 0, 0, 0],
    [0, cosTheta, 0, 0],
    [0, 0, cosTheta, 0],
    [0, 0, 0, 1],
  ];

  const part2 = matrix.scale(
    [
      [nx * nx, nx * ny, nx * nz, 0],
      [nx * ny, ny * ny, ny * nz, 0],
      [nx * nz, ny * nz, nz * nz, 0],
      [0, 0, 0, 0],
    ],
    1 - cosTheta,
  );

  const part3 = matrix.scale(
    [
      [0, -nz, ny, 0],
      [nz, 0, -nx, 0],
      [-ny, nx, 0, 0],
      [0, 0, 0, 0],
    ],
    sinTheta,
  );

  return matrix.add(matrix.add(part1, part2), part3);
};

export const P_rot = (N, degree, P) => {
  const radian = (degree / 180) * Math.PI;
  const cos = Math.cos(radian);
  const sin = Math.sin(radian);

  const part1 = vector.scale(P, cos);
  const part2 = vector.scale(N, (1 - cos) * vector.dot(P, N));
  const part3 = vector.scale(vector.cross(N, P), sin);

  return vector.add(vector.add(part1, part2), part3);
};

export default P_rot;
