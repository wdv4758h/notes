===============================================
RFC 2565 - Formal Function Parameter Attributes
===============================================


:URL: https://github.com/rust-lang/rfcs/blob/master/text/2565-formal-function-parameter-attributes.md


讓函式參數也可以使用 procedural macro，
藉此可以更方便地製作 DSL、控制編譯器優化、簡化測試程式、輔助 FFI 程式等等。


範例：

.. code-block:: rust

    #[resource(path = "/foo/bar")]
    impl MyResource {
        #[get("/person/:name")]
        fn get_person(
            &self,
            #[path_param = "name"] name: String, // <-- formal function parameter.
            #[query_param = "limit"] limit: Option<u32>, // <-- here too.
        ) {
            ...
        }
    }
