#include <sys/param.h>
#include <sys/module.h>
#include <sys/kernel.h>
#include <sys/systm.h>

// The function called at load/unload
static int event_handler(struct module *module, int event, void *arg) {
        int err = 0;    // Error, 0 for normal return status
        switch (event) {
        case MOD_LOAD:
                uprintf("simple module: Hello\n");
                break;
        case MOD_UNLOAD:
                uprintf("simple module: Goodbye\n");
                break;
        default:
                err = EOPNOTSUPP;   // Error, Operation Not Supported
                break;
        }

        return(err);
}

// The second argument of DECLARE_MODULE
static moduledata_t hello_conf = {
    "hello",         // module name
     event_handler,  // event handler
     NULL            // extra data
};

DECLARE_MODULE(hello_fsm, hello_conf, SI_SUB_DRIVERS, SI_ORDER_MIDDLE);
