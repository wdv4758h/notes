pub fn func1() {
    {
        // src -> func0
        use ::func0::func0;
        func0();
    }
    {
        // src -> folder0 -> func1
        use ::folder0::func1::func1;    // me
        // func1();
    }
    {
        // src -> folder0 -> folder1 -> func2
        use ::folder0::folder1::func2::func2;
        func2();
    }
    {
        // func1.rs -----> folder0 -----> src -> func0
        //          super          super
        use super::super::func0::func0;
        func0();
    }
    {
        // func1.rs -----> folder0 -> func1
        //          super
        use super::func1::func1;    // me
        // func1();
    }
    {
        // func1.rs -----> folder0 -> folder1 -> func2
        //          super
        use super::folder1::func2::func2;
        func2();
    }
}
