Forecasting volatility with neural regression: A contribution to model adequacy
===============================================================================

Ref: http://ieeexplore.ieee.org/document/935095/

- 2001

- 當時對 overfitting 沒嚴謹的驗證。
    the lack of rigorous procedures for model identification, selection
    and adequacy testing.

- 本篇貢獻：methodology for neural model misspecification testing

    - Specification: https://en.wikipedia.org/wiki/Specification_(regression)

      建立、發展 regression model 的過程。 選 function、選變數。

    - generalization of the Durbin–Watson statistic for neural regression
        - https://en.wikipedia.org/wiki/Durbin%E2%80%93Watson_statistic

    - NN are universal approximators and are thus capable of providing a model
      which fits any data with an arbitrary degree of accuracy.

    - misspecification testing for neural regression

- build a neural predictor of implied volatility for options pricing

- 如果我們做 error 是 independent 這個假設。
  autocorrlation 的 error 就會被嚴重低估。
