import matrix from './libs/matrix.mjs';
import vector from './libs/vector.mjs';
import eulerAngles from './euler_angles.mjs';
import P_rot, { get_rotation } from './rodrigues_rotation_formula.mjs';

const round = k => Math.round(k * 100) / 100;

const N = vector.normalize(vector.makeVector(3, 4, 5, 0));
const P = vector.makeVector(3, 1, 2, 0);

const rotationByEulerAngles = eulerAngles(N, 30);
const rotationByRodriguesRotationFormula = get_rotation(N, 30);

console.log(matrix.multiply(rotationByEulerAngles, P));
console.log(matrix.multiply(rotationByRodriguesRotationFormula, P));
console.log(P_rot(N, 30, P));

const result = Array.from({ length: 12 }, (_, index) => {
  return P_rot(N, index * 30, P)
    .map(round)
    .join(', ');
});

console.log(result);
