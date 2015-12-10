#include <Python.h>

////////////////////////////////////////
// Methods
////////////////////////////////////////

static PyObject* hello_world(PyObject *self, PyObject *args) {
    return Py_BuildValue("s", "Hello World");
}

////////////////////////////////////////
// Module Definition
////////////////////////////////////////

PyDoc_STRVAR(module_doc, "Simple 'Hello World' Module");

static PyMethodDef methods[] = {
    { "hello_world", hello_world, METH_VARARGS, "Say hello." },
    {NULL, NULL},
};

static PyModuleDef moduledef = {
    PyModuleDef_HEAD_INIT,  // PyModuleDef_HEAD_INIT
    "hello",    // module name
    module_doc, // docstring
    0,          // size of per-module area
    methods,    // methods (table of module-level functions)
    NULL,       // array of slot definitions
    NULL,       // traverse function for GC
    NULL,       // clear function for GC
    NULL        // deallocation function
};

PyMODINIT_FUNC PyInit_hello(void) {
    return PyModule_Create(&moduledef);
}

////////////////////////////////////////
