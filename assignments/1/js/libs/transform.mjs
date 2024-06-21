export const rotateZ = radian => [
  [Math.cos(radian), -Math.sin(radian), 0, 0],
  [Math.sin(radian), Math.cos(radian), 0, 0],
  [0, 0, 1, 0],
  [0, 0, 0, 1],
];
const transform = {
  rotateZ,
};
export default transform;
