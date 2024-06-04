const { dot, scale, add, cross,round } = require('./utils');

const N = [3, 4, 5];
const P = [3, 1, 2];
const N_u = scale(N, 1 / Math.sqrt(dot(N, N)));

const P_rot = degree => {
  const radian = (degree / 180) * Math.PI;
  const cos = Math.cos(radian);
  const sin = Math.sin(radian);

  return add(
    scale(P, cos),
    scale(N_u, (1 - cos) * dot(P, N_u)),
    scale(cross(N_u, P), sin),
  );
};

const result = Array.from({ length: 12 }, (_, index) => {
  return P_rot(index * 30).map(round).join(', ');
});

console.log(result);
