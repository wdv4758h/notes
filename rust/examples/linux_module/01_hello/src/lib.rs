#![feature(core_str_ext)]
#![no_std]

////////////////////////////////////////
// make some C types
////////////////////////////////////////

#[allow(non_camel_case_types)]
pub type c_char = i8;

////////////////////////////////////////
// get some kernel functions
////////////////////////////////////////

extern {
    pub fn printk(fmt: *const c_char);
}

////////////////////////////////////////
// convenient macros
////////////////////////////////////////

macro_rules! cstr {
    ($arg:expr) => (concat!($arg, "\0"))
}

macro_rules! print {
    ($str:expr) => ({
        use core::str::StrExt;
        let cstring = cstr!($str);
        let ptr = cstring.as_ptr() as *const c_char;
        unsafe { printk(ptr); }
    })
}

macro_rules! println {
    ($str:expr) => (print!(concat!($str, "\n")))
}

////////////////////////////////////////
// Linux Kernel Module's
// basic functions
////////////////////////////////////////

#[no_mangle]
pub fn rust_init() -> i32 {
    println!("[Rust] Hello");
    0
}

#[no_mangle]
pub fn rust_exit() {
    println!("[Rust] Goodbye");
}
