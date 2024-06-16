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

## 從羅德里格旋轉公式提取旋轉矩陣

假設 $N = (nx, ny, nz)$ 以及 $P = (px, py, pz)$ 帶入羅德里格旋轉公式

$$
\begin{aligned}
P_{rot} &=  \cos{\theta} * \vec{P} + (1 - \cos{\theta}) * \vec{P} \cdot \vec{N} * \vec{N} -\sin{\theta} * \vec{P} \times \vec{N} \\
  &= \begin{bmatrix} \cos{\theta} * px \\
  \cos{\theta} * py \\
  \cos{\theta} * pz \end{bmatrix} + \begin{bmatrix} (1 - \cos{\theta}) * (nx * px + ny * py + nz * pz) * nx \\
  (1 - \cos{\theta}) * (nx * px + ny * py + nz * pz) * ny \\
  (1 - \cos{\theta}) * (nx * px + ny * py + nz * pz) * nz \end{bmatrix} + \begin{bmatrix} \sin{\theta} * (ny * pz - nz* py) \\
  \sin{\theta} * (nz * px - nx * pz) \\
  \sin{\theta} * (nx * py - ny* px)\end{bmatrix} \\
  &=\begin{bmatrix} \cos{\theta} * px \\
  \cos{\theta} * py \\
  \cos{\theta} * pz \end{bmatrix} + \begin{bmatrix} (1 - \cos{\theta}) * (nx^2 * px + (nx * ny) * py + (nx * nz) * pz) \\
  (1 - \cos{\theta}) * ((nx * ny) * px + ny^2 * py + (ny * nz) * pz) \\
  (1 - \cos{\theta}) * ((nx * nz) * px + (ny * nz) * py + nz^2 * pz) \end{bmatrix} + \begin{bmatrix} \sin{\theta} * (- nz* py + ny * pz ) \\
  \sin{\theta} * (nz * px - nx * pz) \\
  \sin{\theta} * (- ny* px + nx * py)\end{bmatrix} \\
  &= (\cos{\theta} * \begin{bmatrix} 1 & 0 & 0 \\
  0 & 1 & 0 \\
  0 & 0 & 1 \end{bmatrix} +(1 - \cos{\theta}) * \begin{bmatrix} nx^2 & nx * ny & nx * nz \\
  nx * ny  & ny^2 & ny * nz \\
  nx * nz & ny * nz & nz^2 \end{bmatrix} + \sin{\theta} * \begin{bmatrix} 0 & -nz & ny \\
  nz & 0 & -nx \\
  -ny & nx & 0\end{bmatrix})* \begin{bmatrix} px \\
  py \\
  pz\end{bmatrix}\\
  &= (\cos{\theta} * I +(1 - \cos{\theta}) * N * N^T+ \sin{\theta} * \begin{bmatrix} 0 & -nz & ny \\
  nz & 0 & -nx \\
  -ny & nx & 0\end{bmatrix})* \begin{bmatrix} px \\
  py \\
  pz\end{bmatrix}
\end{aligned}
$$

也就是 [Games101 第 4 講投影片](https://sites.cs.ucsb.edu/~lingqi/teaching/resources/GAMES101_Lecture_04.pdf) 第 10 頁上的公式

這裡得到的旋轉矩陣，與透過歐拉角得到的矩陣是完全一樣的

直接從程式運算可以證明，也可以花點時間藉由數學展開證明

## 後計

這個公式是在 [Games101 第 4 講](https://www.bilibili.com/video/BV1X7411F744?p=4&vd_source=a16a592878ecb424b56a5a4112d932a5) 上補充的

老師在課上沒有特別花時間證明，但有附上 [手寫的補充教材](https://sites.cs.ucsb.edu/~lingqi/teaching/resources/GAMES101_Lecture_04_supp.pdf)

其實我沒有看懂老師的證明，但我在 [良葛格的 Blog](https://openhome.cc/Gossip/WebGL/Rodrigues.html) 找到了該證明的詳細解說，並重新寫成我自己的版本

我原始證明想法其實是歐拉角的作法，思想比較直觀，我第一時間其實也是挑戰用歐拉角把證明寫出來

遇到的第一個困難是矩陣展開的過程實在是太過繁瑣了（其實有[網站](https://matrixcalc.org/zh-TW/) 提供矩陣展開的運算）

再來是我寫錯了把 $\vec{N_{rot(xz)}}$ 轉到 Z 軸的角度，我直接使用 $\vec{N}$ 投影到 XZ 的向量夾角

實際上 $\vec{N_{rot(xz)}}$ 與此投影向量並不會重疊，用 [Geogebra](https://www.geogebra.org/calculator) 把畫出向量之後才發現錯誤

我強烈建議有想要寫任何 3D 幾何證明的人，先使用 Geogebra 把向量畫出來，單純用想像的實在太困難了

另外，如果想專心在圖形學上，不需要花這麼多心思在此公式的證明上，大致聽一聽推導的思想就好了

我實在是花了太多時間了，尤其是親手展開矩陣乘法的部分，覺得後悔

<!--

## 比較歐拉角與羅德里格旋轉公式

在歐拉角的版本是直接用 N 推導出旋轉矩陣

雖然都是取角度，所以 N 的長度不重要

但為了簡化運算，還是必須先把 N 正規化

$$
\begin{aligned}
\vec{N} &= (nx, ny, nz) \\
a &= \cfrac{nz}{\sqrt{ny^2 + nz^2}} \\
b &= \cfrac{ny}{\sqrt{ny^2 + nz^2}} \\
c &= \cfrac{\sqrt{ny^2 + nz^2}}{\sqrt{nx^2 + ny^2 + nz^2}} = \sqrt{ny^2 + nz^2} \\
d &= \cfrac{nx}{\sqrt{nx^2 + ny^2 + nz^2}} = nx \\
e &= \cos{\theta} \\
f &= \sin{\theta} \\
\\
result &= \begin{bmatrix}
d^2+c^2e & bcd-acf-bcde & acd+bcf-acde \\
bcd+acf-bcde & b^2c^2+a^2e+b^2d^2e & abc^2-a^2df-b^2df-abe+abd^2e \\
acd-bcf-acde & abc^2+a^2df+b^2df-abe+abd^2e & a^2c^2+b^2e+a^2d^2e
\end{bmatrix}
\end{aligned}
$$
-->
