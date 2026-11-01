#define PY_SSIZE_T_CLEAN
#include <Python.h>

#include "mutable_string.h"

typedef struct {
    PyObject_HEAD
    MutableString *value;
} PyMutableString;

static PyObject *MutableString_new(
    PyTypeObject *type,
    PyObject *args,
    PyObject *kwargs
)
{

    PyMutableString *self;
    self = (PyMutableString *)type->tp_alloc(type,0);

    if (self != NULL){
        
      self->value = NULL;
    }

    return (PyObject *)self;

}

static int MutableString_init(
    PyMutableString *self,
    PyObject *args,
    PyObject *kwargs
)
{ 

  PyObject *text_obj;
  const char *text;

  if (!PyArg_ParseTuple(args,"U",&text_obj)){
    
    return -1;
  }

  text = PyUnicode_AsUTF8(text_obj);

  if(text == NULL){

    return -1;
  }

  MutableString *new_value = ms_create(text);

  if (new_value == NULL){
    PyErr_NoMemory();
    return -1; 
  }

  ms_destroy(self->value);
  self->value = new_value;
  return 0;


}

static void MutableString_dealloc(PyMutableString *self)
{

  ms_destroy(self->value);
  Py_TYPE(self)->tp_free((PyObject *)self); 

}

  static PyObject *MutableString_append(
    PyMutableString *self,
    PyObject *args
  )
  {
    PyObject *text_obj;
    const char *text;
  if (!PyArg_ParseTuple(args,"U",&text_obj)){
      return NULL;
    }
  text = PyUnicode_AsUTF8(text_obj);
  if (text==NULL){
      return NULL;
    }

    if (ms_append(self->value,text)!=0){
      PyErr_NoMemory();
      return NULL;
    }

    Py_RETURN_NONE;
}

static PyObject *MutableString_str(PyMutableString *self)
{
    return PyUnicode_DecodeUTF8(
    self->value->data,
    (Py_ssize_t)self->value->length,
    "strict"
  );
}
static Py_ssize_t MutableString_length(PyMutableString *self){
  return (Py_ssize_t)self->value->length;
}
static PyMethodDef MutableString_methods[]={
{
  "append",
  (PyCFunction)MutableString_append,
  METH_VARARGS,
  "Append text to this mutbale string."
  },
  {NULL,NULL,0,NULL}
};

static PySequenceMethods MutableString_sequence = {
  .sq_length = (lenfunc)MutableString_length,
};

static PyTypeObject MutableStringType = {

    PyVarObject_HEAD_INIT(NULL,0)
    .tp_name = "mutable_string.MutableString",
    .tp_doc  = "A mutable_string backed by a C charecter buffer.",
    .tp_basicsize = sizeof(PyMutableString),
    .tp_flags = Py_TPFLAGS_DEFAULT,
    .tp_new = MutableString_new,
    .tp_init = (initproc)MutableString_init,
    .tp_dealloc = (destructor)MutableString_dealloc,
    .tp_str = (reprfunc)MutableString_str,
    .tp_repr = (reprfunc)MutableString_str,
    .tp_methods = MutableString_methods,
    .tp_as_sequence = &MutableString_sequence
};

static PyModuleDef mutable_string_module = {
  PyModuleDef_HEAD_INIT,
  .m_name = "mutable_string",
  .m_doc= "A C-backed mutable string extension",
  .m_size = -1,
};

PyMODINIT_FUNC PyInit_mutable_string(void)
{
    if (PyType_Ready(&MutableStringType) < 0) {
        return NULL;
    }

    PyObject *module = PyModule_Create(&mutable_string_module);

    if (module == NULL) {
        return NULL;
    }

    Py_INCREF(&MutableStringType);

    if (PyModule_AddObject(
            module,
            "MutableString",
            (PyObject *)&MutableStringType
        ) < 0) {
        Py_DECREF(&MutableStringType);
        Py_DECREF(module);
        return NULL;
    }

    return module;

} 


