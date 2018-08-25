Annealing Method
===============================================================================

避免 Local min of TSSE

1. DA (Deterministic Annealing)

2. SA (Simulated Annealing)

DA (\beta 是控制 Fuzziness 的參數)

令 \beta = 0^+ (e.g. 0.00001)
任意取 k 個群中心 {y_1 ... y_k}

step1. update {y_1 .. y_k} by

y_j = \frac{ \sum{ (u_ij) x_i}, i = 1..N}{ \sum{u_ij} }

where, u_ij = \frac{ e^(- \beta ( | x_i - y_j | )^2 )}{ \sum{ e^( - \beta ( | x_i - y_l | )^2), l=1..k} }

ps. y_j 同時出現在 等式兩邊，只能找 approximation sol

常用 y_j^new = (用 y_j^new), 重複 update 直到 y_j 不太改變

實際上就是 Fuzzy k-means with given \beta

step2. increase \beta 以降低 Fuzziness 如此可以跳出 local min

step3. goto step1. 除非 \beta >= user defined threshold


DA Experiment

\beta_init = 0.0001 (fuzzy 程度大)
Assume \beta_new = 1.1 * \beta_old ,\beta_final = 0.1 (fuzzy 程度小)

ps. (1.1)^72.5 = 1000
\therefore 73 次的 \beta 增加, 約 74 次的 Fuzzy clustering
(each fuzzy k-means is very time-comsuming)


SImulated Annealing
----------------------------------------------------------------------

Target function: min E(P)  (Partition P)

e.g. E 是 TSSE 這種分群的 error

符號: S 是個 Pertirbation Rule (打破現狀之攪動)
   \sigma
 P ---> P' 是個由 P 這種分群結果變成 P'

 T = 溫度 (控制用)

 Random number: 由某 Random number generator 產生0..1 之間的數字
           0 <= # <= 1

 MAXIT: Max number of iteration

 \alpha: 降溫比例 (e.g \alpha=0.9)

 T_0 以及 T_final: Initial and Final temperture (given)


S.A

T <- T_0
P 任意

step 1.
    For i = 1 to MAXIT do
            \sigma
        P' <---- P

        \Delta = E(P') - E(P) (若 error 變小 E(P) 變小，則改進是好的)
        接受 P' 以取代 P , if \Delta < 0
                         , if \Delta > 0 and P^(- \Delta / T) >= random number
                                             ^^^^ 抽籤決定要不要留下不好的 P
                                             ^^^^ 是哪來跳出 local min

step 2.
    降 T: T_new = \alpha T_old

step 3.
    if T_new > T_final, goto step1


SA accept a *bad* clustering criteria
    e.g. if e^(-\delta/T) >= random number
    e.g. (-\delta / T) >= ln(random number)
    e.g. (\delta / T) <= -ln(n) = ln(1/n)
