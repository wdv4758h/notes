========================================
Pattern Matching
========================================


.. contents:: 目錄


範例
========================================

match
------------------------------

.. code-block:: rust

    let x = 5;

    match x {
        1 => println!("one"),
        2 => println!("two"),
        3 => println!("three"),
        4 => println!("four"),
        5 => println!("five"),
        _ => println!("something else"),
    }


match + assign
------------------------------

.. code-block:: rust

    let x = 5;

    let number = match x {
        1 => "one",
        2 => "two",
        3 => "three",
        4 => "four",
        5 => "five",
        _ => "something else",
    };


match + enum & destructing
------------------------------

.. code-block:: rust

    enum MyEnum {
        A,
        B(i32),
        C { x: i32, y: i32 },
        D(String),
    }

    fn func(data: MyEnum) {
        match data {
            MyEnum::A => println!("it's A"),
            MyEnum::B(x) => println!("it's {}", x),
            MyEnum::C { x, y: 0 } => println!("it's {} and 0", x),
            MyEnum::C { x, y: foo } => println!("it's {}, {}", x, foo),
            MyEnum::D(x) => println!("{}", x),
        };
    }


match + ignoring binding
------------------------------

.. code-block:: rust

    enum MyEnum {
        A,
        B(i32),
        C { x: i32, y: i32 },
        D(String),
    }

    fn func(data: MyEnum) {
        match data {
            MyEnum::C { _, y: 0 } => println!("y is 0"),  // ignore the x
            _ => println!("rest of things"),              // ignore whatever it gets
        };
    }


multiple pattern
------------------------------

.. code-block:: rust

    let x = 1;

    match x {
        1 | 2 => println!("one or two"),
        3 => println!("three"),
        _ => println!("anything"),
    }


match + ref/ref mut
------------------------------

.. code-block:: rust

    let x = 5;

    match x {
        ref r => println!("Got a reference to {}", r),
    }


.. code-block:: rust

    let mut x = 5;

    match x {
        ref mut mr => println!("Got a mutable reference to {}", mr),
    }


match + ranges
------------------------------

.. code-block:: rust

    let x = 1;

    match x {
        1 ... 5 => println!("one through five"),
        _ => println!("anything"),
    }


.. code-block:: rust

    let x = '💅';

    match x {
        'a' ... 'j' => println!("early letter"),
        'k' ... 'z' => println!("late letter"),
        _ => println!("something else"),
    }


match + binding
------------------------------

.. code-block:: rust

    let x = 1;

    match x {
        e @ 1 ... 5 => println!("got a range element {}", e),
        _ => println!("anything"),
    }


.. code-block:: rust

    let x = 5;

    match x {
        e @ 1 ... 5 | e @ 8 ... 10 => println!("got a range element {}", e),
        _ => println!("anything"),
    }


.. code-block:: rust

    #[derive(Debug)]
    struct Person {
        name: Option<String>,
    }

    let name = "Steve".to_string();
    let x: Option<Person> = Some(Person { name: Some(name) });
    match x {
        Some(Person { name: ref a @ Some(_), .. }) => println!("{:?}", a),
        _ => {}
    }


match + guards
------------------------------

.. code-block:: rust

    let x = 4;
    let y = false;

    match x {
        4 | 5 if y => println!("yes"),  // (4 | 5) if y
        _ => println!("no"),
    }


.. code-block:: rust

    enum OptionalInt {
        Value(i32),
        Missing,
    }

    let x = OptionalInt::Value(5);

    match x {
        OptionalInt::Value(i) if i > 5 => println!("Got an int bigger than five!"),
        OptionalInt::Value(..) => println!("Got an int!"),
        OptionalInt::Missing => println!("No such luck."),
    }


if let
------------------------------

.. code-block:: rust

    if let Some(x) = option {
        foo(x);
    } else {
        bar();
    }


while let
------------------------------

.. code-block:: rust

    let mut v = vec![1, 3, 5, 7, 11];
    while let Some(x) = v.pop() {
        println!("{}", x);
    }


FizzBuzz
------------------------------

.. code-block:: rust

    fn main() {
        for x in 1..100 {
            match (x % 3 == 0, x % 5 == 0) {
                (true, true) => println!("FizzBuzz"),
                (true, false) => println!("Fizz"),
                (false, true) => println!("Buzz"),
                (false, false) => println!("{}", x)
            }
        }
    }


Fibonacci
------------------------------

.. code-block:: rust

    fn fibo(number: u32) -> u32 {
        match number {
            x @ 0...1 => x,
            x => std::iter::repeat((0, 0))
                     .take((x-2) as usize)
                     .fold((1, 1), |acc, _| (acc.1, acc.0+acc.1)).1,
        }
    }


nested match
------------------------------

``match`` 是 expression，可以連續使用很多次

.. code-block:: rust

    let x = 42;
    let y = match match x {
                42 => Some(56),
                _ => None,
            } {
        Some(val) => val,
        None => 0,
    };
