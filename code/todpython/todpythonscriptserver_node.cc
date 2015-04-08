#include "todpython/todpythonscriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::TodNode_new(PyTypeObject* type, PyObject* args, PyObject* keys)
{
    TodNode* o = reinterpret_cast<TodNode*>(type->tp_alloc(type, 0));
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
void TodPythonScriptServer::TodNode_dealloc(PyObject* self)
{
    TodNode* o = reinterpret_cast<TodNode*>(self);
    if (o->node.valid())
    {
        size_t c = TodPythonScriptServer::s_todobjects.erase(o->node->getAbsolutePath());
        if (0 == c)
        {
            for (auto i=TodPythonScriptServer::s_todobjects.begin();
                i!=TodPythonScriptServer::s_todobjects.end(); ++i)
            {
                if ((o->node) == (i->second->node))
                {
                    TodPythonScriptServer::s_todobjects.erase(i);
                    break;
                }
            }
        }
    }
    o->node.release();
    self->ob_type->tp_free(self);
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::TodNode_repr(TodNode* self)
{   
    return PyString_FromString(self->node->getAbsolutePath().u_str());
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::TodNode_getattro(TodNode* self, PyObject* name)
{
    char* attr_name = PyString_AsString(name);
    Type* type = self->node->getType();

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
        if (prop) return TodPythonScriptServer::build_property_to_pyobject(self->node.get(), prop);
    }

    return PyErr_Format(PyExc_Exception,
        "\'%s\' Node has no attribute \'%s\'",
            self->node->getAbsolutePath().u_str(), attr_name);
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::TodNode_call(PyObject* self, PyObject* args, PyObject* keys)
{
    TodNode* o = reinterpret_cast<TodNode*>(self);
    if (o->node.invalid()) return PyErr_Format(PyExc_Exception, "invalid TodNode");
    return TodPythonScriptServer::invoke_method(o->node, o->method, args, keys);
}


//-----------------------------------------------------------------------------
int TodPythonScriptServer::TodNode_setattro(TodNode* self, PyObject* name, PyObject* value)
{
    if (self->node.valid())
    {
        TodPythonScriptServer::set_property(self->node, self->node->getAbsolutePath().u_str(), name, value);
    }
    return 0;
}


//-----------------------------------------------------------------------------
PyTypeObject TodPythonScriptServer::s_TodNodeType =
{
    PyObject_HEAD_INIT(0)
    0,                                                              // ob_size
    "TodNode",                                                      // tp_name
    sizeof(TodNode),                                                // tp_basicssize
    0,                                                              // tp_itemsize
    TodPythonScriptServer::TodNode_dealloc,                         // tp_dealloc
    0,                                                              // tp_print
    (getattrfunc)0,                                                 // tp_getattr
    (setattrfunc)0,                                                 // tp_setattr
    0,                                                              // tp_compare
    0,                                                              // tp_repr
    0,                                                              // tp_as_number
    0,                                                              // tp_as_mapping
    0,                                                              // tp_as_sequence
    0,                                                              // tp_as_hash
    (ternaryfunc)TodPythonScriptServer::TodNode_call,               // tp_call
    (reprfunc)TodPythonScriptServer::TodNode_repr,                  // tp_str
    (getattrofunc)TodPythonScriptServer::TodNode_getattro,          // tp_getattro
    (setattrofunc)TodPythonScriptServer::TodNode_setattro,          // tp_setattro
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
    TodPythonScriptServer::TodNode_new,                             // tp_new
};



