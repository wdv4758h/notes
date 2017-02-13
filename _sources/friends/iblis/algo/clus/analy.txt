Analytical Clustering
===============================================================================

Moment-Preserving


3-dim: google scholar Ja-Chen Lin, Real-time and automatic two-class clustering
by analytical formulas


k clusters => {p_1, p_2, ... p_k } & {x_1 x_2 ... x_k}
\because 2k 個變數, \therefore 2k 個式子

p_1 + p_2 + ... + p_k = 100%
p_1 x_1 + p_2 x_2 + ... + p_k x_k = \overline{x}
p_1 x_1^{2k -1} + ... + p_x x_k^{2k - 1} = \overline{x^{2k - 1}}

ps. k > 4 就解不出來了(by Galoi's 定理), computer 可 approximation

2-dim IEEE PAMI


Principal Axis(PA) of {\vec{x_i}}_1 ^3000

Definition
    PA of {(x_i, y_i)}_i
    過質量中心 (\overline{x}, \overline{y}) 的一條線
    且個點到此線的距離平方需最小化


在 2-dim 分群後得到 \vec{x_A} \vec{x_B} 之後
{\vec{x_A} .. } 打上 3000 x p_A 個點
{\vec{x_B} .. }      3000 x p_B
新的 PA 為 \vec{x_A} \vec{x_B} 連線
我們希望 PA 在分群前後不變

\because p_A \theta_a + p_B \theta_B = \overline{\theta}
\therefore p_A \theta_A + p_B (\theta_A = \pi) = \overline{\theta}

\because p_B \pi = \overline{\theta} - (p_a + p_b) \theta_A
可解 p_A



proof

P_A X_A + P_B X_B = \bar{X} = 0

\therefore P_A X_A = - P_B x_B
also \bar{y} = 0

P_A Y_A = - P_B Y_B

P_A^2 X_A^2 = P_B^2 X_B^2  .. (1)
P_A^2 Y_A^2 = P_B^2 Y_B^2  .. (2)

(1) + (2) =  P_A^2(X_A^2 + Y_A^2) = P_B^2(Y_A^2 + Y_B^2)
P_A^2 r_A^2 = P_B^2 r_B^2

P_A r_A = P_B r_B

P_A r_A + P_B r_B = \bar{r}

2 P_A r_A = 2 P_B r_B = \bar{r}

r_B = 0.5 \bar{r} / P_B

r_A = 0.5 \bar{r} / P_A

與 k-means when k=2 時 很像 但是沒 initial 的問題


1. Fast, without iterations
2. No initial
3. Automatic


How to setup Equetions

1-dim: no need to memory answer
2-dim: need
3-dim: the only one using r
