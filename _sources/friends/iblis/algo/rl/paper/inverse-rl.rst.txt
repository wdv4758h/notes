Algorithm for Inverse Reinforcement Learning
===============================================================================

這篇提出 Inverse Reinforcement Learning 的解法，
而 inverse reinforcement learning problem 是別人定義的。

Problem Setting

    #. Given agent 在各種狀況下的 behaviour，抑或是有 environment model
       的話。

    #. 請找出 Reward function。

為何找 reward function？在很多狀況下，觀察生物的決策，但我們無法精確得知
到底根據怎麼樣的 reward 而行動，而且很多是多個 factor 考慮後的結果。
在經濟學上，有類似的發展， `Multi-attribute utility` ，但是這些在經濟學上的
發展是 one-shot（single decision then got immediate reward）。

第二個 motivation 則是，透過 expert 給出的 information 來學習，學得像 expert，
這類的方法是屬於 `imitation learning` 跟 `apprenticeship learning` 。
在這類的問題之下，有 expert 的 trajectory 而沒有直接的 policy，目的是想要
得出 policy；因為可能 expert 自己也沒有明確的 policy，抑或是考慮的東西很複雜，
難以量化。
所以透過 inverse reinforcement learning 來 `recover` reward function。
而且作者認為，讓整個 reinforcement learning 的解法建構在 reward function，
而非 policy，
能夠比用 policy 簡潔且提供 task 的 `transferable definition` (註：沒辦法翻)。

這篇提出三個演算法，分別用在 finite MDP，large or infinite state space，
第三個則是在只有 trajectory samples 的狀況下是用。
