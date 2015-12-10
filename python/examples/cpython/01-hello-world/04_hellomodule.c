#include <Python.h>
#include <structmember.h>   // PyMemberDef, T_INT

////////////////////////////////////////
// New Type
////////////////////////////////////////

typedef struct {
    PyObject_HEAD   // macro for every type in Python
    // Type-specific fields go here
    int life;
} LifeObject;

// Members

static PyMemberDef Life_members[] = {
    {"life", T_INT, offsetof(LifeObject, life), 0, "number of life"},
    {NULL}
};

static int LifeObject_init(LifeObject *self, PyObject *args, PyObject *kwds) {
    self->life = 42;

    // "|" : remaining arguments in the Python argument list are optional
    // "i" : convert a plain C int to a Python integer object.
    if (!PyArg_ParseTuple(args, "|i", &(self->life)))
        return 0;

    return 0;
}

static PyTypeObject LifeType = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "hello.Life",               // tp_name, for printing, "<module>.<name>"
    sizeof(LifeObject),         // tp_basicsize, for allocation
    0,                          // tp_itemsize, for allocation

    // Methods to implement standard operations

    0,                          // tp_dealloc
    0,                          // tp_print
    0,                          // tp_getattr
    0,                          // tp_setattr
    0,                          // tp_as_async, formerly known as tp_compare (Python 2) or tp_reserved (Python 3)
    0,                          // tp_repr

    // Methods for standard classes

    0,                          // tp_as_number
    0,                          // tp_as_sequence
    0,                          // tp_as_mapping

    // More standard operations (here for binary compatibility)

    0,                          // tp_hash
    0,                          // tp_call
    0,                          // tp_str
    0,                          // tp_getattro
    0,                          // tp_setattro

    ////////////////////////////////////////

    0,                          // tp_as_buffer, functions to access object as input/output buffer
    Py_TPFLAGS_DEFAULT,         // tp_flags, flags to define presence of optional/expanded features
    "Life Object",              // tp_doc, docstring

    ////////////////////////////////////////

    0,                          // tp_traverse, assigned meaning in release 2.0, call function for all accessible objects
    0,                          // tp_clear, delete references to contained objects
    0,                          // tp_richcompare, assigned meaning in release 2.1, rich comparisons
    0,                          // tp_weaklistoffset, weak reference enabler
    0,                          // tp_iter, iterators
    0,                          // tp_iternext, iterators

    // Attribute descriptor and subclassing stuff

    0,                          // tp_methods
    Life_members,               // tp_members
    0,                          // tp_getset
    0,                          // tp_base
    0,                          // tp_dict
    0,                          // tp_descr_get
    0,                          // tp_descr_set
    0,                          // tp_dictoffset
    (initproc)LifeObject_init,  // tp_init
    0,                          // tp_alloc
    PyType_GenericNew,          // tp_new
    0,                          // tp_free, low-level free-memory routine
    0,                          // tp_is_gc, for PyObject_IS_GC
    0,                          // tp_bases
    0,                          // tp_mro, method resolution order
    0,                          // tp_cache
    0,                          // tp_subclasses
    0,                          // tp_weaklist
    0,                          // tp_del

    0,                          // tp_version_tag, type attribute cache version tag. Added in version 2.6
    0,                          // tp_finalize
};

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

    // Types

    if (PyType_Ready(&LifeType) < 0)
        return NULL;

    // Module

    PyObject *m = PyModule_Create(&moduledef);

    // Types

    if (m == NULL)
        return NULL;

    Py_INCREF(&LifeType);
    PyModule_AddObject(m, "Life", (PyObject *)&LifeType);

    return m;
}

////////////////////////////////////////
// Examples
////////////////////////////////////////

// >>> import hello
// >>> hello.hello_world()
// 'Hello World'
// >>> hello.Life
// <class 'hello.Life'>
// >>> hello.Life().life
// 42
// >>> hello.Life(10).life
// 10
