const {
  multiply,
  makeVector,
  rotateZ,
  transpose,
  compose,
  get,
  round
} = require('./utils');

const N = [3, 4, 5];
const P = [3, 1, 2];

const P_rot = degree => {
  const radian = (degree / 180) * Math.PI;

  const cosX = N[2] / Math.sqrt(N[1] * N[1] + N[2] * N[2]);
  const sinX = N[1] / Math.sqrt(N[1] * N[1] + N[2] * N[2]);
  // 原本是 (x, y, z)
  const rx = [
    [1, 0, 0],
    [0, cosX, -sinX],
    [0, sinX, cosX],
  ];
  // 旋轉後是 (x, 0, sqrt(y * y + z * z))
  const cosY =
    Math.sqrt(N[1] * N[1] + N[2] * N[2]) /
    Math.sqrt(N[0] * N[0] + N[1] * N[1] + N[2] * N[2]);
  const sinY = N[0] / Math.sqrt(N[0] * N[0] + N[1] * N[1] + N[2] * N[2]);

  const ryt = [
    [cosY, 0, -sinY],
    [0, 1, 0],
    [sinY, 0, cosY],
  ];

  const back = multiply(ryt, rx);
  const front = transpose(back);

  const result = compose(front, rotateZ(radian), back, makeVector(...P));

  return get(result);
};

const result = Array.from({ length: 12 }, (_, index) => {
  return P_rot(index * 30)
    .map(round)
    .join(', ');
});

console.log(result);
