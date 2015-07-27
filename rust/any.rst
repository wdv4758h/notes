============================================
Rust's runtime reflection - "Any" type trait
============================================

Rust 有一個 module 叫 ``std::any`` ，
裡面的 ``Any`` trait 可以讓 ``'static`` type 藉由 runtime reflection 來做到 dynamic typing

簡單範例：

.. code-block:: rust

    use std::any::Any;

    fn func(data: &Any) {
        if data.is::<i32>() {
            println!("i32: {}", data.downcast_ref::<i32>().unwrap_or(&0));
        } else if data.is::<f64>() {
            println!("f64: {}", data.downcast_ref::<f64>().unwrap_or(&0.0));
        } else {
            println!("unknown : {:?}", data);
        }
    }

    fn main() {
        let x = 3;
        func(&x);
        let y = 1.3;
        func(&y);
    }

這邊可以看到 function parameter 的 type 寫的是 ``Any`` ，
如此一來這邊就可以吃各種 type，
下面在 main function 的地方就分別傳入了 ``i32`` 和 ``f64`` 的資料，
``Any`` type 可以用 ``.is::<TYPE>()`` 來判斷說是不是某種 type，
而後續可以用 ``.downcast_ref::<TYPE>()`` 來取得 reference (不過記得先 unwrap)。


官方範例：

.. code-block:: rust

    use std::fmt::Debug;
    use std::any::Any;

    // Logger function for any type that implements Debug.
    fn log<T: Any + Debug>(value: &T) {
        let value_any = value as &Any;

        // try to convert our value to a String.  If successful, we want to
        // output the String's length as well as its value.  If not, it's a
        // different type: just print it out unadorned.
        match value_any.downcast_ref::<String>() {
            Some(as_string) => {
                println!("String ({}): {}", as_string.len(), as_string);
            }
            None => {
                println!("{:?}", value);
            }
        }
    }

    // This function wants to log its parameter out prior to doing work with it.
    fn do_work<T: Any + Debug>(value: &T) {
        log(value);
        // ...do some other work
    }

    fn main() {
        let my_string = "Hello World".to_string();
        do_work(&my_string);

        let my_i8: i8 = 100;
        do_work(&my_i8);
    }

官方的範例是要對程式做紀錄，
但是 log function 不能確定要紀錄的變數的 type，
此時可以使用 ``Any`` type 就可以接收各種不同的 type 來處理。


Reference
========================================

* `Rust - Module std::any <https://doc.rust-lang.org/std/any/>`_
* `Rust - any.rs <https://doc.rust-lang.org/src/core/any.rs.html>`_
* `Rust - Reflect <https://doc.rust-lang.org/std/marker/trait.Reflect.html>`_
* `Wikipedia - Reflection (computer programming) <https://en.wikipedia.org/wiki/Reflection_%28computer_programming%29>`_
