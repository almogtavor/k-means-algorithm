# define PY_SSIZE_T_CLEAN
# include <Python.h>
# include <stdio.h>
# include "demolib.h"

int counter = 0;
// wrapper function for cfactorial_sum
static PyObject *DemoLib_cFactorialSum(PyObject *self, PyObject *args) {
    char *char_nums;
    if (!PyArg_ParseTuple(args, "s", &char_nums)) {
        return NULL;
    }

    unsigned long fact_sum;
    fact_sum = cfactorial_sum(char_nums);

    return Py_BuildValue("i", fact_sum);
}

// wrapper function for ifactorial_sum
static PyObject *DemoLib_iFactorialSum(PyObject *self, PyObject *args) {
    PyObject *lst;
    PyObject *item;
    long num;
    if (!PyArg_ParseTuple(args, "O", &lst)) {
        return NULL;
    }

    int n = PyObject_Length(lst);
    if (n < 0) {
        return NULL;
    }

    long *nums = (long *)malloc(n * sizeof(long));
    if (nums == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return NULL;
    }
    int i;
    for (i = 0; i < n; i++) {
        item = PyList_GetItem(lst, i);
        num = PyLong_AsLong(item);
        nums[i] = num;
    }

    unsigned long fact_sum;
    fact_sum = ifactorial_sum(nums, n);
    free(nums);
    return Py_BuildValue("i", fact_sum);
}

static PyObject* GetList(PyObject* self, PyObject* args)
{
    int N,r;
    PyObject* python_val;
    PyObject* python_int;
    if (!PyArg_ParseTuple(args, "i", &N)) {
        return NULL;
    }
    python_val = PyList_New(N);
    for (int i = 0; i < N; ++i)
    {
        r = i;
        python_int = Py_BuildValue("i", r);
        PyList_SetItem(python_val, i, python_int);
    }
    return python_val;
}

/* Module method function table */
static PyMethodDef kmeansMethods[] = {
    {"fit", fit, METH_VARARGS, "Run the k-means algorithm"},
    {NULL, NULL, 0, NULL}  // Sentinel
};

/* Module definition */
static struct PyModuleDef kmeansmodule = {
    PyModuleDef_HEAD_INIT,
    "mykmeanssp",  // Module name in python
    "Python interface for the k-means algorithm",  // Module documentation
    -1,  // Module state
    kmeansMethods
};

/* Module initialization function */
PyMODINIT_FUNC PyInit_mykmeanssp(void) {
    return PyModule_Create(&kmeansmodule);
}
