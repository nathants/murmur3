//-----------------------------------------------------------------------------
// MurmurHash3 was written by Austin Appleby, and is placed in the public
// domain. The author hereby disclaims copyright to this source code.


#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <Python.h>
#include "murmur3.h"

static PyObject *
murmur3_hash(PyObject *self, PyObject *args, PyObject *keywds)
{
    const char *target_str;
    int target_str_len;
    uint32_t seed = 0;
    int32_t result[1];

    static char *kwlist[] = {(char *)"key", (char *)"seed", NULL};

    if (!PyArg_ParseTupleAndKeywords(args, keywds, "s#|i", kwlist,
        &target_str, &target_str_len, &seed)) {
        return NULL;
    }

    MurmurHash3_x86_32(target_str, target_str_len, seed, result);

    return PyLong_FromLong(result[0]);
}

struct module_state {
  PyObject *error;
};


#define GETSTATE(m) ((struct module_state*)PyModule_GetState(m))

static PyMethodDef Murmur3Methods[] = {
    {"hash", (PyCFunction)murmur3_hash, METH_VARARGS | METH_KEYWORDS, "hash(key[, seed=0]) -> hash value\n Return a 32 bit integer."},
    {NULL, NULL, 0, NULL}
};

static int murmur3_traverse(PyObject *m, visitproc visit, void *arg) {
    Py_VISIT(GETSTATE(m)->error);
    return 0;
}

static int murmur3_clear(PyObject *m) {
    Py_CLEAR(GETSTATE(m)->error);
    return 0;
}

static struct PyModuleDef murmur3module = {
    PyModuleDef_HEAD_INIT,
    "murmur3",
    "",
    sizeof(struct module_state),
    Murmur3Methods,
    NULL,
    murmur3_traverse,
    murmur3_clear,
    NULL
};

#define INITERROR return NULL

PyMODINIT_FUNC
PyInit_murmur3(void)

{

    PyObject *module = PyModule_Create(&murmur3module);

    if (module == NULL)
        INITERROR;

    struct module_state *st = GETSTATE(module);

    st->error = PyErr_NewException((char *) "murmur3.Error", NULL, NULL);
    if (st->error == NULL) {
        Py_DECREF(module);
        INITERROR;
    }

    return module;

}
