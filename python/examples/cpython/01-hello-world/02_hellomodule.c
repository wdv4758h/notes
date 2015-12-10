#include <Python.h>

////////////////////////////////////////
// Module Definition
////////////////////////////////////////

static PyMethodDef methods[] = {
    {NULL, NULL},
};

static PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,  // PyModuleDef_HEAD_INIT
    "hello",    // module name
    PyDoc_STR("Simple 'Hello World' Module"), // docstring
    0,          // size of per-module area
    methods,    // methods (table of module-level functions)
    NULL,       // array of slot definitions
    NULL,       // traverse function for GC
    NULL,       // clear function for GC
    NULL        // deallocation function
};

PyObject* PyInit_hello(void) {
    return PyModule_Create(&moduledef);
}

////////////////////////////////////////
