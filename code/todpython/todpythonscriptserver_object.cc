#include "todpython/todpythonscriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::TodObject_new(PyTypeObject* type, PyObject* args, PyObject* keys)
{
    TodObject* o = reinterpret_cast<TodObject*>(type->tp_alloc(type, 0));
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
void TodPythonScriptServer::TodObject_dealloc(PyObject* self)
{
    TodObject* o = reinterpret_cast<TodObject*>(self);
    if (o->createdByPython) delete o->object;
    self->ob_type->tp_free(self);
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::TodObject_getattro(TodObject* self, PyObject* name)
{
    char* attr_name = PyString_AsString(name);
    Type* type = self->object->getType();

    // find method
    Method* method = type->findMethod(attr_name);
    if (method)
    {
        self->method = method;
        Py_INCREF(self);
        Py_INCREF(name);
        return (PyObject*)(self);
    }
    // find property
    else
    {   
        Property* prop = type->findProperty(attr_name);
        if (prop) return TodPythonScriptServer::build_property_to_pyobject(self->object, prop);
    }

    return PyErr_Format(PyExc_Exception,
        "\'%p\' Object has no attribute \'%s\'",
            self->object, attr_name);
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::TodObject_call(PyObject* self, PyObject* args, PyObject* keys)
{
    TodObject* o = reinterpret_cast<TodObject*>(self);
    if (0 == o->object)
        return PyErr_Format(PyExc_Exception, "invalid TodObject");
    return TodPythonScriptServer::invoke_method(o->object, o->method, args, keys);
}


//-----------------------------------------------------------------------------
int TodPythonScriptServer::TodObject_setattro(TodObject* self, PyObject* name, PyObject* value)
{
    if (self->object)
    {
        TodPythonScriptServer::set_property(self->object, "", name, value);
    }
    return 0;
}


//-----------------------------------------------------------------------------
PyTypeObject TodPythonScriptServer::s_TodObjectType =
{
    PyObject_HEAD_INIT(0)
    0,                                                              // ob_size
    "TodObject",                                                    // tp_name
    sizeof(TodObject),                                              // tp_basicssize
    0,                                                              // tp_itemsize
    TodPythonScriptServer::TodObject_dealloc,                       // tp_dealloc
    0,                                                              // tp_print
    (getattrfunc)0,                                                 // tp_getattr
    (setattrfunc)0,                                                 // tp_setattr
    0,                                                              // tp_compare
    0,                                                              // tp_repr
    0,                                                              // tp_as_number
    0,                                                              // tp_as_mapping
    0,                                                              // tp_as_sequence
    0,                                                              // tp_as_hash
    (ternaryfunc)TodPythonScriptServer::TodObject_call,             // tp_call
    0,                                                              // tp_str
    (getattrofunc)TodPythonScriptServer::TodObject_getattro,        // tp_getattro
    (setattrofunc)TodPythonScriptServer::TodObject_setattro,        // tp_setattro
    0,                                                              // tp_as_buffer
    Py_TPFLAGS_DEFAULT,                                             // tp_flags
    "TodPython Object",                                             // tp_doc
    0,                                                              // tp_traverse
    0,                                                              // tp_clear
    0,                                                              // tp_richcompare
    0,                                                              // tp_weaklistoffset
    0,                                                              // tp_iter
    0,                                                              // tp_iternext
    0,                                                              // tp_methods,
    0,                                                              // tp_members
    0,                                                              // tp_getset
    0,                                                              // tp_base
    0,                                                              // tp_dict
    0,                                                              // tp_descr_get
    0,                                                              // tp_descr_set
    0,                                                              // tp_dictoffset
    0,                                                              // tp_init
    0,                                                              // tp_alloc
    TodPythonScriptServer::TodObject_new,                           // tp_new
};
