1. `Rust for Python Programmers <http://lucumr.pocoo.org/2015/5/27/rust-for-pythonistas/>`_

- Hello World example::

    fn main(){
        for count in 0..3 {
            println!("{}. Hello World!", count);
        }
    }

  - Rust has format string
  - ``!`` in ``println!`` is Rust macro

- Traits vs Protocols::

    use std::ops::Add;

    struct MyType {
        value: i32,
    }

    impl MyType {
        fn new(value: i32) -> MyType {
            MyType { value: value }
        }
    }

    impl Add for MyType {
        type Output = MyType;

        fn add(self, other: MyType) -> MyType {
            MyType { value: self.value + other.value }
        }
    }

  - struct => class, impl => class method
  - ``impl``'s implementation is defining function in it.
  - ``impl`` is traits, which has scope and can be modified?
  - Python's ``__init__()``: initialize object
  - Rust's constructor: allocate + initialize(construct) object

- Error Handling

  - Python: try exception, Rust: error code.
  - success + error return value, ex. ``Result<i32, MyError>``
  - multiple error simutaneously: ``Box<Error>``, user defined error type
  - ``try!``: if error occur, return from function and fill in error return value?? ``from`` trait??
  - ``unwrap``: if error occur, program abort (like c assert())

- Mutability and Ownership

  - Rust memory management: no garbage collection, use ownership tracking.

    - All things you can create are owned by another thing.
    - Ownership: Function calls <- list of objects <- objects
    - lifetime annotations and the function signatures
    - switch the reference to one object: need to "move" the owner.
    - two reference of one object: "borrow"

Misc
----
- Why Rust for Low-level Linux programming?: http://groveronline.com/2016/06/why-rust-for-low-level-linux-programming/
- [Software Engineer Daily Podcast] 由 Steve Klabnik 介紹 Rust: https://www.facebook.com/groups/857846870916793/permalink/1191448607556616/

- Rust vs C/C++ Pitfalls: http://www.garin.io/rust-vs-c-pitfalls
- Rust recursive structure: http://yodalee.blogspot.tw/2016/03/rust-recursive-structure.html
- & vs. ref in Rust patterns: http://xion.io/post/code/rust-patterns-ref.html#fnref:2
- Rust Borrow and Lifetimes: https://www.facebook.com/groups/857846870916793/permalink/1193541934013950/
- Dropbox 分享他們怎麼用 Rust: https://www.facebook.com/groups/857846870916793/permalink/1213125188722291/
- Baby Steps: Slowly Porting musl to Rust: http://blog.adamperry.me/rust/2016/06/11/baby-steps-porting-musl-to-rust/

- Rust 讀書會筆記(mozilla, 2016/07/26): https://gist.github.com/caasi/99064e12e7cf0a3c32c87e9276d1f6fe
