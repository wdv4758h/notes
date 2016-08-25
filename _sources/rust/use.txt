========================================
use
========================================

rename
========================================

.. code-block:: rust

    enum One { A, B, C }

    fn main() {
        use One as Two;     // rename
        let b = Two::B;
    }


re-export types under a different identifier
============================================

.. code-block:: rust

    mod foo {
        pub enum One { A, B, C }
    }

    mod bar {
        pub use foo::One as Two;    // re-export
    }

    fn main() {
        use bar::Two;
        let b = Two::B;
    }
