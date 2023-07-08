========================================
Meta Algorithm
========================================


.. contents:: 目錄


Metaheuristic
========================================

Metaheuristic 爲高階的法則或啓發式演算法（經驗法則），
在有限的資訊、運算能力、資源下，
對最佳化問題（Optimization Problem）尋找足夠好的啓發式演算法。

並不保證 globally optimal

許多 Metaheuristic 帶有隨機最佳化（Stochastic Optimization）


性質：

* Metaheuristics are strategies that guide the search process.
* The goal is to efficiently explore the search space in order to find near–optimal solutions.
* Techniques which constitute metaheuristic algorithms range from simple local search procedures to complex learning processes.
* Metaheuristic algorithms are approximate and usually non-deterministic.
* Metaheuristics are not problem-specific.


不同分類方式：

* Local search vs. global search
    - 基本版的爬山演算法（hill climbing）屬於 local search
    - 把 local search 擴增到 global search
        + simulated annealing
        + tabu search
        + iterated local search
        + variable neighborhood search
        + GRASP (Greedy Randomized Adaptive Search Procedure)
    - 單純 global serach（非基於 local search 衍生），通常是 population-based
        + ant colony optimization
        + evolutionary computation
        + particle swarm optimization
        + genetic algorithm
        + rider optimization algorithm
* Single-solution vs. population-based
    - 單一解決方案：專注在一種候選解決方案
        + simulated annealing
        + iterated local search
        + variable neighborhood search
        + guided local search
    - 多重解決方案：有多個候選解決方案在調整
        + evolutionary computation
        + genetic algorithms
        + particle swarm optimization
    - Swarm intelligence (collective behavior of decentralized, self-organized agents in a population or swarm)
        + Ant colony optimization
        + particle swarm optimization
        + social cognitive optimization
* Hybridization and memetic algorithms
    - hybrid metaheuristic：並行使用 metaheuristic 和其他最佳化演算法，兩者間可以同時進行並互相交換資訊來引導搜尋
        + 可搭配 mathematical programming, constraint programming, machine learning
    - memetic algorithm：傳統基因演算法的擴增
        + 例如使用 local search 取代原本的變動運算，藉此減少過早收斂的機會
* Parallel metaheuristics
    - 同時跑多種 metaheuristic，甚至可能是分散式到許多機器嘗試多種方案
* Nature-inspired and metaphor-based metaheuristics
    - 從大自然中獲得設計想法
    - simulated annealing
    - evolutionary algorithms
    - ant colony optimization
    - particle swarm optimization


Metaheuristic Optimization Frameworks (MOFs)，蒐集許多演算法實作供快速取用：

* `GitHub Topics - metaheuristic-framework <https://github.com/topics/metaheuristic-framework>`_
* `GitHub Topics - metaheuristics <https://github.com/topics/metaheuristics>`_
* `jMetal <https://github.com/jMetal/jMetal>`_
* `OptaPlanner <https://github.com/kiegroup/optaplanner>`_



參考
========================================

* `Wikipedia - Metaheuristic <https://en.wikipedia.org/wiki/Metaheuristic>`_
* `Wikipedia - Meta learning (computer science) <https://en.wikipedia.org/wiki/Meta_learning_(computer_science)>`_
* `Wikipedia - Meta-optimization <https://en.wikipedia.org/wiki/Meta-optimization>`_
* `Wikipedia - Memetic algorithm <https://en.wikipedia.org/wiki/Memetic_algorithm>`_
