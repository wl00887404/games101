import matrix from './libs/matrix.mjs';
import { rotateZ } from './libs/transform.mjs';

const P_rot = (N, degree) => {
  const radian = (degree / 180) * Math.PI;

  const cosX = N[2] / Math.sqrt(N[1] * N[1] + N[2] * N[2]);
  const sinX = N[1] / Math.sqrt(N[1] * N[1] + N[2] * N[2]);
  // 原本是 (x, y, z)
  const rx = [
    [1, 0, 0, 0],
    [0, cosX, -sinX, 0],
    [0, sinX, cosX, 0],
    [0, 0, 0, 1],
  ];
  // 旋轉後是 (x, 0, sqrt(y * y + z * z))
  const cosY =
    Math.sqrt(N[1] * N[1] + N[2] * N[2]) /
    Math.sqrt(N[0] * N[0] + N[1] * N[1] + N[2] * N[2]);
  const sinY = N[0] / Math.sqrt(N[0] * N[0] + N[1] * N[1] + N[2] * N[2]);

  const ryt = [
    [cosY, 0, -sinY, 0],
    [0, 1, 0, 0],
    [sinY, 0, cosY, 0],
    [0, 0, 0, 1],
  ];

  const back = matrix.multiply(ryt, rx);
  const front = matrix.transpose(back);

  return matrix.compose(front, rotateZ(radian), back);
};

export default P_rot;
