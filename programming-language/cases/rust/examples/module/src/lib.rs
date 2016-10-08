mod func0;
mod folder0;

fn root() {
    {
        use func0::func0;
        func0();
    }
    {
        use folder0::func1::func1;
        func1();
    }
    {
        use folder0::folder1::func2::func2;
        func2();
    }
}
