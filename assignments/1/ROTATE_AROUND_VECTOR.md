# 羅德里格旋轉公式

## 題目

給定一個過原點的單位向量 $\vec{N}$ ，求點 $P$ 繞著 $\vec{N}$ 逆時鐘旋轉 $\theta$ 度的旋轉結果

## 證明

首先把 $P$ 看成從原點到 $P$ 的向量 $\vec{P}$

$\vec{P}$ 可以投影到 $\vec{N}$ 獲得 $\vec{P_{\parallel}}$ （與 $\vec{N}$ 平行），並從 $\vec{P} - \vec{P_{\parallel}} = \vec{P_\perp}$

把 $\vec{N}$ 當作 Y 軸，把 $\cfrac{\vec{P_\perp}}{\vert\vec{P_\perp}\vert}$ 當作是 X 軸，並且藉由 X 軸 $\times$ Y 軸得到 Z 軸

三向量都是單位向量，可是視作新的坐標系

在新的座標系中， $\vec{P}$ 的座標為 $(\vert\vec{P_\perp}\vert, \vert\vec{P_\parallel}\vert, 0)$

題目就等於是頂點 P 繞著新 Y 軸旋轉，這樣就可以套用 Y 軸旋轉矩陣

可得旋轉後的 $\vec{P_{rot}} = (\cos{\theta} * \vert\vec{P_\perp}\vert, \vert\vec{P_\parallel}\vert, -\sin{\theta} * \vert\vec{P_\perp}\vert)$，之後再把 XYZ 轉換回去就好

$$
\begin{aligned}
Y &= \vec{N} \\
\\
\vec{P_\parallel} &= \cos{\alpha} * \vec{N} \\
  &= \vec{P} \cdot \vec{N} * \vec{N} \\
\\
\vec{P_\perp} &= \vec{P} - \vec{P_\parallel} \\
  &= \vec{P} - \vec{P} \cdot \vec{N} * \vec{N} \\
\\
X &= \cfrac{\vec{P_\perp}}{\vert\vec{P_\perp}\vert} \\
\\
Z &= X \times Y \\
  &= \cfrac{\vec{P_\perp} \times \vec{N}}{\vert\vec{P_\perp}\vert} \\
  &= \cfrac{(\vec{P} - \vec{P} \cdot \vec{N} * \vec{N}) \times \vec{N}}{\vert\vec{P_\perp}\vert} \\
  &= \cfrac{\vec{P} \times \vec{N} - (\vec{P} \cdot \vec{N}) * (\vec{N} \times \vec{N})}{\vert\vec{P_\perp}\vert} \\
  &= \cfrac{\vec{P} \times \vec{N} - (\vec{P} \cdot \vec{N}) * 0}{\vert\vec{P_\perp}\vert} \\
  &= \cfrac{\vec{P} \times \vec{N}}{\vert\vec{P_\perp}\vert} \\
\end{aligned}
$$

XYZ 都有了，再來轉換座標回去

$$
\begin{aligned}
\vec{P_{rot}} &= \cos{\theta} * \vert\vec{P_\perp}\vert * X + \vert\vec{P_\parallel}\vert * Y -\sin{\theta} * \vert\vec{P_\perp}\vert *Z \\
\\
\cos{\theta} * \vert\vec{P_\perp}\vert * X &= \cos{\theta} * \vert\vec{P_\perp}\vert * \cfrac{\vec{P_\perp}}{\vert\vec{P_\perp}\vert} \\
  &= \cos{\theta} * \vec{P_\perp} \\
  &= \cos{\theta} * \vec{P} -\cos{\theta} * \vec{P} \cdot \vec{N} * \vec{N} \\
\\
\vert\vec{P_\parallel}\vert * Y &=  \vert\vec{P} \cdot \vec{N} * \vec{N} \vert * \vec{N} \\
  &= \vec{P} \cdot \vec{N} * \vec{N} \\
\\
-\sin{\theta} * \vert\vec{P_\perp}\vert * Z &= -\sin{\theta} * \vert\vec{P_\perp}\vert * \cfrac{\vec{P} \times \vec{N}}{\vert\vec{P_\perp}\vert} \\
  &= -\sin{\theta} * \vec{P} \times \vec{N} \\
\\
\vec{P_{rot}} &= \cos{\theta} * \vec{P} -\cos{\theta} * \vec{P} \cdot \vec{N} * \vec{N} +  \vec{P} \cdot \vec{N} * \vec{N} -\sin{\theta} * \vec{P} \times \vec{N} \\
  &=  \cos{\theta} * \vec{P} + (1 - \cos{\theta}) * \vec{P} \cdot \vec{N} * \vec{N} -\sin{\theta} * \vec{P} \times \vec{N}
\end{aligned}
$$

得證！

實作請參考 [rodrigues_rotation_formula.js](./rodrigues_rotation_formula.js)

## 其他想法

既然 $\vec{N}$ 是過原點的向量，就可以用歐拉角表示

只要把 $\vec{N}$ 旋轉回 Z 軸，就可以套用 Z 軸旋轉公式，之後再轉回去就行了

把 $\vec{N}$ 轉到 XZ 平面，角度是將 $\vec{N}$ 投影到 YZ 平面，該向量與 Z 軸的夾角，之後藉由 X 軸旋轉

$$
\begin{aligned}
\vec{N} &= (nx, ny, nz) \\
\vec{N_{proj(yz)}} &= (0, ny, nz) \\
\cos{x} &= \cfrac{nz}{\sqrt{ny^2 + nz^2}} \\
\sin{x} &= \cfrac{ny}{\sqrt{ny^2 + nz^2}} \\
\vec{N_{rot(xz)}} &=(nx, 0, \sqrt{ny^2 + nz^2}) \\
\end{aligned}
$$

再來把 $\vec{N_{rot(xz)}}$ 轉到 Z 軸上，因為此向量已經在 XZ 平面了，所以等同於做一個二維的旋轉

$$
\begin{aligned}
\vec{N_{rot(xz)}} &=(nx, 0, \sqrt{ny^2 + nz^2}) \\
\cos{y} &= \cfrac{\sqrt{ny^2 + nz^2}}{\sqrt{nx^2 + ny^2 + nz^2}} \\
\sin{y} &= \cfrac{nx}{\sqrt{nx^2 + ny^2 + nz^2}} \\
\end{aligned}
$$

接著進行 Z 軸旋轉，再將 N 軸逆向操作回原本的位置，就可以得到旋轉後的 P 點了

$$
\begin{aligned}
\cos{x} &= \cfrac{nz}{\sqrt{ny^2 + nz^2}} \\
\sin{x} &= \cfrac{ny}{\sqrt{ny^2 + nz^2}} \\
\cos{y} &= \cfrac{\sqrt{ny^2 + nz^2}}{\sqrt{nx^2 + ny^2 + nz^2}} \\
\sin{y} &= \cfrac{nx}{\sqrt{nx^2 + ny^2 + nz^2}} \\
\\
Rot(N \rightarrow XZ) &= \begin{bmatrix}1 & 0 & 0 \\
  0 & \cos{x} & -\sin{x} \\
  0 & \sin{x} & \cos{x} \end{bmatrix} \\
\\
Rot(XZ \rightarrow Z) &= \begin{bmatrix}\cos{y} & 0 & -\sin{y} \\
  0 & 1 & 0 \\
  \sin{y} & 0 & cos{y} \end{bmatrix} \\
\\
Rot(\theta) &= \begin{bmatrix}\cos{\theta} & -\sin{\theta} & 0 \\
  \sin{\theta} & \cos{\theta}  & 0 \\
  0 & 0 & 1 \end{bmatrix}\\
\\
Rot(N \rightarrow  Z) &= Rot(XZ \rightarrow Z) * Rot(N \rightarrow XZ) \\
\\
P_{rot} &= Rot(Z \rightarrow  N) *  Rot(\theta) * Rot(XZ \rightarrow Z) * Rot(N \rightarrow Z) \\
  &= Rot(N \rightarrow  Z)^T *  Rot(\theta) * Rot(XZ \rightarrow Z) * Rot(N \rightarrow Z) \\
\end{aligned}
$$

實作請參考 [euler_angles.js](./euler_angles.js)

<!-- ## 從羅德里格旋轉公式提取旋轉矩陣 -->

<!-- ## 歐拉角優化的可能性

只需要 N 就可以取旋轉矩陣，只需要保留 $\cos{\theta}$ 與 $\sin{\theta}$ 做為參數

$$
\begin{aligned}
\vec{N} &= (nx, ny, nz) \\
a &= \cfrac{nz}{\sqrt{ny^2 + nz^2}} \\
b &= \cfrac{ny}{\sqrt{ny^2 + nz^2}} \\
c &= \cfrac{\sqrt{ny^2 + nz^2}}{\sqrt{nx^2 + ny^2 + nz^2}} \\
d &= \cfrac{nx}{\sqrt{nx^2 + ny^2 + nz^2}} \\
e &= \cos{\theta} \\
f &= \sin{\theta} \\
\\
result &= \begin{bmatrix}
d^2+c^2e & bcd-acf-bcde & acd+bcf-acde \\
bcd+acf-bcde & b^2c^2+a^2e+b^2d^2e & abc^2-a^2df-b^2df-abe+abd^2e \\
acd-bcf-acde & abc^2+a^2df+b^2df-abe+abd^2e & a^2c^2+b^2e+a^2d^2e
\end{bmatrix}
\end{aligned}
$$ -->