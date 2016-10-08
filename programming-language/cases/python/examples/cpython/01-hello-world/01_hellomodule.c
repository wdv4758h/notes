#include <Python.h>

////////////////////////////////////////
// Module Definition
////////////////////////////////////////

static PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,  // PyModuleDef_HEAD_INIT
    "hello",    // module name
    NULL,       // docstring
    0,          // size of per-module area
    NULL,       // methods (table of module-level functions)
    NULL,       // array of slot definitions
    NULL,       // traverse function for GC
    NULL,       // clear function for GC
    NULL        // deallocation function
};

PyMODINIT_FUNC PyInit_hello(void) {
    return PyModule_Create(&moduledef);
}

////////////////////////////////////////
