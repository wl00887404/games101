const makeArray = length => Array.from({ length });
const makeVector = (x, y, z) => {
  const result = [[x], [y], [z]];

  return result;
};

const makeMatrix = (r, c, initialValue = 0) => {
  return makeArray(r).map(() => {
    return makeArray(c).map(() => initialValue);
  });
};

const dot = (v, w) => v[0] * w[0] + v[1] * w[1] + v[2] * w[2];

const cross = (v, w) => {
  return [
    v[1] * w[2] - v[2] * w[1],
    v[2] * w[0] - v[0] * w[2],
    v[0] * w[1] - v[1] * w[0],
  ];
};

const add = (v, w, ...more) => {
  const result = [v[0] + w[0], v[1] + w[1], v[2] + w[2]];

  if (!more.length) return result;

  return add(result, ...more);
};

const scale = (v, k) => v.map(x => x * k);

const size = m => {
  return [m.length, m[0].length];
};

const multiply = (m, n) => {
  const [r1, c1] = size(m);
  const [r2, c2] = size(n);

  if (c1 !== r2) {
    throw new Error(`M${r1}x${c1} can not multiply M${r2}x${c2}`);
  }

  const result = makeMatrix(r1, c2);

  for (let i = 0; i < r1; i++) {
    for (let j = 0; j < c2; j++) {
      for (let k = 0; k < c1; k++) {
        result[i][j] += m[i][k] * n[k][j];
      }
    }
  }

  return result;
};

const transpose = m => {
  const [r, c] = size(m);
  const result = makeMatrix(c, r);

  for (let i = 0; i < r; i++) {
    for (let j = 0; j < c; j++) {
      result[j][i] = m[i][j];
    }
  }

  return result;
};

const compose = (...ms) => {
  const last = ms[ms.length - 1];

  return ms.slice(0, ms.length - 1).reduceRight((result, m) => {
    return multiply(m, result);
  }, last);
};

const rotateZ = radian => [
  [Math.cos(radian), -Math.sin(radian), 0],
  [Math.sin(radian), Math.cos(radian), 0],
  [0, 0, 1],
];

const get = v => [v[0][0], v[1][0], v[2][0]];

const round = k => Math.round(k * 100) / 100;

module.exports = {
  makeVector,
  makeMatrix,
  dot,
  cross,
  add,
  scale,
  size,
  multiply,
  transpose,
  compose,
  rotateZ,
  get,
  round,
};
