const makeArray = length => Array.from({ length });
export const makeMatrix = (r, c, initialValue = 0) => {
  return makeArray(r).map(() => {
    return makeArray(c).map(() => initialValue);
  });
};
const size = m => {
  return [m.length, m[0].length];
};
export const add = (m, n) => {
  const [r1, c1] = size(m);
  const [r2, c2] = size(n);
  if (r1 !== r2 || c1 !== c2) {
    throw new Error(`M${r1}x${c1} can not add M${r2}x${c2}`);
  }
  const result = makeMatrix(r1, c1);
  for (let i = 0; i < r1; i++) {
    for (let j = 0; j < c1; j++) {
      result[i][j] = m[i][j] + n[i][j];
    }
  }
  return result;
};
export const subtract = (m, n) => {
  const [r1, c1] = size(m);
  const [r2, c2] = size(n);
  if (r1 !== r2 || c1 !== c2) {
    throw new Error(`M${r1}x${c1} can not subtract M${r2}x${c2}`);
  }
  const result = makeMatrix(r1, c1);
  for (let i = 0; i < r1; i++) {
    for (let j = 0; j < c1; j++) {
      result[i][j] = m[i][j] - n[i][j];
    }
  }
  return result;
};
export const scale = (m, k) => {
  const [r, c] = size(m);
  const result = makeMatrix(r, c);
  for (let i = 0; i < r; i++) {
    for (let j = 0; j < c; j++) {
      result[i][j] = m[i][j] * k;
    }
  }
  return result;
};
export const multiply = (m, n) => {
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
export const transpose = m => {
  const [r, c] = size(m);
  const result = makeMatrix(c, r);
  for (let i = 0; i < r; i++) {
    for (let j = 0; j < c; j++) {
      result[j][i] = m[i][j];
    }
  }
  return result;
};
export const compose = (...ms) => {
  const last = ms[ms.length - 1];
  return ms.slice(0, ms.length - 1).reduceRight((result, m) => {
    return multiply(m, result);
  }, last);
};
const matrix = {
  makeMatrix,
  size,
  add,
  subtract,
  scale,
  multiply,
  transpose,
  compose,
};
export default matrix;
