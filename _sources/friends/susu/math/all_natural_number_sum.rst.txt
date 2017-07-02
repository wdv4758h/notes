`尼斯的靈魂 - 1+2+3+…=-1/12? <https://frankliou.wordpress.com/2014/05/18/123-112/>`_

- 弦論應用: Polchinski 弦論書《String Theory》
- 數學出處: 複變函數論, zeta 函數, Gamma 函數.
- 黎曼 zeta 函數

  - :math:`\displaystyle\zeta(s)=\sum_{n=1}^{\infty}\frac{1}{n^{s}}.`
  - s = 1 為調和數列和, s = 2 為調和數列平方和. s = -1 為所有的自然數和, s = -2 為所有的自然數平方和.
  - 實數系中
    
    - s > 1 會使無窮級數收斂, zeta 函數有值 
    - s <= 1 無窮級數發散, zeta 函數無值
    - 微積分 p 測試法
    - 可參考: 過調和級數 (over-harmonic series) 與 p 級數 (`<https://www.wikiwand.com/en/Harmonic_series_(mathematics)#/p-series>`_)

  - 複數系中, 可用解析延拓 (Analytic Continuation) 拓展到 s != 1 的複數上 (複變函數論中的方法)

    - 所有的自然數和 => ``s = -1`` => :math:`\displaystyle\zeta(-1)` => -1/12

  - Bernoulli 數

`如何广义地理解“所有自然数之和”？ <https://www.zhihu.com/question/22506418>`_ 

- 發散級數在其他意義下的求和

  - Cauchy 收斂: 傳統微積分使用的收斂
  - Cesaro 平均收斂
  - Abel 收斂
  - https://www.wikiwand.com/zh-tw/%E5%8F%91%E6%95%A3%E7%BA%A7%E6%95%B0
  - 在實際的數學研究及物理等其它學科的應用中，經常需對發散級數進行運算，於是數學家們便給發散級數定義各種不同的「和」

- Casimir effect (卡西米爾效應) 與權重因子

  - A Zee 的 Quantum Field Theory in a Nutshell 之中, 對於 Casimir effect 的推導有用到 "所有的自然數和"
  - Polchinski 的《String Theory》的書後習題
  - 量子場論的正規化 (regularization) 跟重整化 (renormalization)
  - `卡西米爾效應/真空中的零點能 <https://www.wikiwand.com/zh-tw/卡西米爾效應>`_

- zeta 函數與解析延拓 

  - 直接看上面那篇吧XD

- 總結

  - 在解析延拓的意義下 :math:`\sum_{n=1}^\infty n=-\frac{1}{12}` 這個式子為何會有物理上的效應.
    粗略的說是因為解析延拓可以反映求和的某些漸進行為, 而這背後蘊含的是物理中正規化跟重整化的思想.
