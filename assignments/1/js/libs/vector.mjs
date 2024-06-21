import matrix from './matrix.mjs';
export const makeVector = (x, y, z, w) => {
  const result = [[x], [y], [z]];
  if (w !== undefined) result.push([w]);
  return result;
};
export const add = matrix.add;
export const subtract = matrix.subtract;
export const get = v => [v[0][0], v[1][0], v[2][0], v[3][0]];
export const scale = matrix.scale;
export const dot = (v, w) => {
  const [x1, y1, z1] = get(v);
  const [x2, y2, z2] = get(w);
  return x1 * x2 + y1 * y2 + z1 * z2;
};
export const cross = (v, w) => {
  const [x1, y1, z1] = get(v);
  const [x2, y2, z2] = get(w);
  return makeVector(y1 * z2 - z1 * y2, z1 * x2 - x1 * z2, x1 * y2 - y1 * x2, 0);
};
export const length = v => {
  return Math.sqrt(dot(v, v));
};
export const normalize = v => {
  if (isVector(v)) {
    return scale(v, 1 / length(v));
  }
  const [x, y, z, w] = get(v);
  return makeVector(x / w, y / w, z / w, 1);
};
export const isPoint = v => v[3][0] !== 0;
export const isVector = v => v[3][0] === 0;
const vector = {
  makeVector,
  normalize,
  add,
  subtract,
  get,
  scale,
  dot,
  cross,
  length,
  isPoint,
  isVector,
};
export default vector;
