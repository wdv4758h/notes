#include <linux/module.h>

extern int rust_init(void);
extern void rust_exit(void);

static int hello_init(void) {
    return rust_init();
}

static void hello_exit(void) {
    return rust_exit();
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
