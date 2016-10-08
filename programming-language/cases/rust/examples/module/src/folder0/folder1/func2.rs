pub fn func2() {
    {
        // src -> func0
        use ::func0::func0;
        func0();
    }
    {
        // src -> folder0 -> func1
        use ::folder0::func1::func1;
        func1();
    }
    {
        // src -> folder0 -> folder1 -> func2
        use ::folder0::folder1::func2::func2;   // me
        // func2();
    }
    {
        // func2.rs -----> folder1 -----> folder0 -----> src -> func0
        //          super          super          super
        use super::super::super::func0::func0;
        func0();
    }
    {
        // func2.rs -----> folder1 -----> folder0 -> func1
        //          super          super
        use super::super::func1::func1;
        func1();
    }
    {
        // func2.rs -----> folder1 -> func2
        //          super
        use super::func2::func2;   // me
        // func2();
    }
}
