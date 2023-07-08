========================================
遊戲
========================================


.. contents:: 目錄


遊戲引擎（Game Engine）
========================================

Bevy - refreshingly simple data-driven game engine
--------------------------------------------------

:site: https://bevyengine.org
:repo: https://github.com/bevyengine/bevy


基於 Amethyst 經驗而改造的遊戲引擎。


Amethyst - data-driven game engine
----------------------------------

:site: https://amethyst.rs/
:repo: https://github.com/amethyst/amethyst



ggez (Good Game Easily)
------------------------------

:site: https://ggez.rs/
:repo: https://github.com/ggez/ggez



Piston - modular game engine
------------------------------

:site: https://www.piston.rs/
:repo: https://github.com/PistonDevelopers/piston


是 Rust 社群內很早投入遊戲開發的。
因為很早投入，
所以也開發了不少 Rust 生態圈內的基礎套件，
例如 Rust 生態圈內最大宗的圖像處理套件
`image-rs <https://github.com/PistonDevelopers/piston>`_
以前就是在 Piston 組織底下。

但 Rust 遊戲開發圈後續發展後，
資源重心逐漸移往新的專案如 Amethyst 和 Bevy。



ECS (Entity-Component-System)
==============================================

Specs - Parallel ECS
------------------------------

:site: https://specs.amethyst.rs
:repo: https://github.com/amethyst/specs


Legion
------------------------------

:repo: https://github.com/amethyst/legion
:docs: https://docs.rs/legion/


Bevy ECS
------------------------------

:repo: https://github.com/bevyengine/bevy/tree/master/crates/bevy_ecs


Shipyard
------------------------------

:repo: https://github.com/leudz/shipyard


ECS Bench Suite
------------------------------

:repo: https://github.com/rust-gamedev/ecs_bench_suite



物理引擎（Physics Engines）
========================================

Rapier
------------------------------

:site: https://rapier.rs
:repo: https://github.com/dimforge/rapier
:org: https://dimforge.com
:blog: https://dimforge.com/blog


Rapier 的前身爲 nphysics，
由 `Dimforge <https://dimforge.com/>`_ （Dimforge 的前身爲組織 Rustsim）負責開發，
爲 Dimforge 的旗艦專案。

Dimforge 幾乎每個專案都有不錯的網站與文件，
而且都支援 WebAssembly。

組織下的專案：

* `Simba <https://github.com/dimforge/simba>`_
    - 抽象代數 library
    - 支援 SIMD
* `nalgebra <https://github.com/dimforge/nalgebra>`_
    - 提供基本的線性代數運算
    - 網站 `nalgebra <http://nalgebra.org/>`_
* `Parry <https://github.com/dimforge/parry>`_
    - 2D/3D 幾何 library
    - 網站 `parry <https://parry.rs/>`_
    - "Parry is born from the merge of most of the geometry code we had in Rapier, and some of the geometric code we ported from ncollide"
* `Rapier <https://github.com/dimforge/rapier>`_
    - 2D/3D 物理模擬引擎
    - 網站 `rapier <https://rapier.rs>`_
* `Salva <https://github.com/dimforge/salva>`_
    - 2D/3D 流體模擬
    - 網站 `salva <https://salva.rs/>`_


先前專案：

* `ncollide <https://github.com/sebcrozet/ncollide>`_
    - 被 Parry 取代的專案
    - 2D/3D 碰撞與幾何 library
    - 網站 `ncollide <http://ncollide.org/>`_
* `nphysics <https://github.com/dimforge/ncollide>`_
    - 被 Rapier 取代的專案
    - 2D/3D 即時物理引擎
    - 網站 `nphysics <https://nphysics.org/>`_
* `Alga <https://github.com/dimforge/alga>`_
    - 被 Simba 取代的專案
    - 抽象代數 library


參考：

* [2021] `Physics simulation with Rapier 2021 roadmap | Dimforge <https://dimforge.com/blog/2021/01/01/physics-simulation-with-rapier-2021-roadmap/>`_
    - 2021 年的計劃是讓 Rapier 的功能更完整，足以匹配市場上的其他套件（如 Box2d、Bullet Physics、PhysX）
    - GPU 還沒有在計劃內，可能要 2022 以後
* [2020] `Announcing the Rapier physics engine | Dimforge <https://dimforge.com/blog/2020/08/25/announcing-the-rapier-physics-engine/>`_
    - 有一些當時的效能測試，跟前身 nphysics 比起來快非常多（4 倍以上）
    - [都使用 CPU] 3D 的狀況下，效能和市場上的 PhysX 差不多
    - [都使用 CPU] 2D 的狀況下，效能比市場上的 Box2d 稍微快一點



Rust Console
========================================

:repo: https://github.com/rust-console


數個遊戲機 (Game Console) 相關的開發工具，
例如 GBA、Nintendo 64 等等。



參考
========================================

* `bracket-lib - Roguelike Toolkit (RLTK) <https://github.com/thebracket/bracket-lib>`_
* `vek - Generic 2D-3D math swiss army knife for game engines, with SIMD support and focus on convenience <https://github.com/yoanlcq/vek>`_
