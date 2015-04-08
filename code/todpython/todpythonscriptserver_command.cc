#include "todpython/todpythonscriptserver.h"
#include "todcore/kernel.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_newobj(PyObject* self, PyObject* args)
{
    // parse argument
    char* type_name = nullptr;
    if (!PyArg_ParseTuple(args, "s:newobject", &type_name))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    TodObject* o = reinterpret_cast<TodObject*>(s_TodObjectType.tp_new(&s_TodObjectType, 0, 0));
    if (nullptr == o) return nullptr;
    o->object = Kernel::instance()->create(String().format("%s", type_name).u_str());
    o->createdByPython = true;
    if (0 == o->object)
    {
        Py_DECREF(o);
        return nullptr;
    }
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_new(PyObject* self, PyObject* args)
{
    // parse argument
    char* type_name = nullptr;
    char* path = 0;
    if (!PyArg_ParseTuple(args, "ss:new", &type_name, &path))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    // create new object on NOH and create new TodNode
    TodNode* o = new_todnode(String().format(S("%s"), type_name).u_str(), String().format(("%s"), path).u_str());
    if (nullptr == o) return PyErr_Format(PyExc_Exception, "unable to create");
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_get(PyObject* self, PyObject* args)
{
    str_t* path = nullptr;
    if (!PyArg_ParseTuple(args, "s:get", &path))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    TodNode* exist = find_todnode(String().format("%s", path).u_str());
    if (exist)
    {
        Py_INCREF(exist);
        return reinterpret_cast<PyObject*>(exist);
    }

    Node* node = Kernel::instance()->find(String().format("%s", path).u_str());
    if (nullptr == node) return PyErr_Format(PyExc_Exception, "not found node in NOH");

    TodNode* o = reinterpret_cast<TodNode*>(s_TodNodeType.tp_new(&s_TodNodeType, 0, 0));
    if (nullptr == o) return nullptr;

    o->node = node;
    s_todobjects.insert(TodNodes::value_type(node->getAbsolutePath(), o));
    return reinterpret_cast<PyObject*>(o);
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_delete(PyObject* self, PyObject* args)
{
    char* path = nullptr;
    if (!PyArg_ParseTuple(args, "s:delete", &path))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    TodNode* exist = find_todnode(String().format("%s", path).u_str());
    if (exist)
    {
        Py_DECREF(exist);
    }
    else
    {
        Node* node = Kernel::instance()->find(String().format("%s", path).u_str());
        if (nullptr == node) return PyErr_Format(PyExc_Exception, "not found path[%s]", path);
        node->release();
    }

    Py_INCREF(Py_None);
    return Py_None;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_ls(PyObject* self, PyObject* args)
{
    Node* node = Kernel::instance()->topNode();    
    PyObject* children_names = PyTuple_New(node->getNumChildren());

    int index = 0;
    for (auto i = node->getChildren().begin(); i != node->getChildren().end(); ++i, ++index)
    {
        PyTuple_SET_ITEM(children_names, index, PyString_FromString(i->second->getName().u_str()));
    }
    return children_names;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_pushCwn(PyObject* self, PyObject* args)
{
    TodNode* o = nullptr;
    if (!PyArg_ParseTuple(args, "O:pushcwn", &o))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    Kernel::instance()->pushNode(o->node);
    Py_INCREF(Py_True);
    return Py_True;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_popCwn(PyObject* self, PyObject* args)
{
    Kernel::instance()->popNode();
    Py_INCREF(Py_True);
    return Py_True;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_todprint(PyObject* self, PyObject* args)
{
    return 0;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_exit(PyObject* self, PyObject* args)
{    
    Py_INCREF(Py_True);
    return Py_True;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_serialize(PyObject* self, PyObject* args)
{
    TodNode* o = nullptr;
    char* fname = nullptr;
    if (!PyArg_ParseTuple(args, "sO:serialize", &fname, &o))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    Py_INCREF(Py_False);
    return Py_False;

    /*XmlSerializer s;
    if (s.serialize(String(uri), o->node))
    {
        Py_INCREF(Py_True);
        return Py_True;
    }
    else
    {
        Py_INCREF(Py_False);
        return Py_False;
    }*/
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_deserialize(PyObject* self, PyObject* args)
{
    TodNode* parent_o = nullptr;
    char* fname = nullptr;
    char* name = nullptr;
    if (!PyArg_ParseTuple(args, "Os|s:deserialize", &parent_o, &fname, &name))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    return nullptr;

    /*XmlSerializer s;
    Object* result_o = 0;
    if (name)
        result_o = s.deserialize(
            parent_o->node, String(uri), String(name).c_str());
    else
        result_o = s.deserialize(parent_o->node, String(uri), 0);
    if (0 == result_o)
        return PyErr_Format(PyExc_Exception, "resource not found(%s)", uri);

    TodObject* o = reinterpret_cast<TodObject*>(
        s_TodObjectType.tp_new(&s_TodObjectType, 0, 0));
    if (0 == o)
    {
        Py_INCREF(Py_None);
        return Py_None;
    }
    o->object = result_o;
    return reinterpret_cast<PyObject*>(o);*/

}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_getModuleList(PyObject* self, PyObject* args)
{
    PyObject* result = PyTuple_New(Kernel::instance()->getNumModules());

    int i = 0;
    for (auto m=Kernel::instance()->getModules().begin();m!=Kernel::instance()->getModules().end();++m,++i)
    {
        Module* module = m->second;
        PyTuple_SET_ITEM(result, i, PyString_FromString(module->getName().u_str()));
    }

    return result;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_getTypeList(PyObject* self, PyObject* args)
{
    char* module_name = nullptr;
    if (!PyArg_ParseTuple(args, "s:getTypeList", &module_name))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    PyObject* result = nullptr;
    Module* module = Kernel::instance()->findModule(String(module_name).c_str());
    if (nullptr == module)
    {
        result = PyTuple_New(0);
        return result;
    }
    else
    {
        result = PyTuple_New(module->getNumTypes());
    }
    
    int i = 0;
    for (auto t=module->getTypes().begin();t!=module->getTypes().end();++t,++i)
    {
        Type* type = t->second;
        PyTuple_SET_ITEM(result, i, PyString_FromString(type->getName().u_str()));
    }

    return result;

}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_getDerivedTypes(PyObject* self, PyObject* args)
{
	char* type_name = nullptr;
    if (!PyArg_ParseTuple(args, "s:getDerivedTypes", &type_name))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    return nullptr;

	/*PyObject* result = nullptr;
    const Type* type = Kernel::instance()->findType(type_name);
    if (nullptr == type)
		return PyErr_Format(PyExc_TypeError, "there're no exist specified name of type \'%s\'", type_name);

	const Type::Types& types = type->getDerivedTypes();
	result = PyTuple_New(types.size());

	int i = 0;
	for (auto t = types.begin();t!=types.end();++t,++i)
    {
        Type* type = t->second;
        PyTuple_SET_ITEM(result, i, PyString_FromString(type->getName().u_str()));
    }

	return result;*/
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::command_getTypeInfo(PyObject* self, PyObject* args)
{
	char* type_name = nullptr;
    if (!PyArg_ParseTuple(args, "s:getTypeInfo", &type_name))
        return PyErr_Format(PyExc_Exception, "mismatch argument");

    Type* type = Kernel::instance()->findType(type_name);
    if (nullptr == type)
		return PyErr_Format(PyExc_TypeError, "there're no exist specified name of type \'%s\'", type_name);

	PyObject* result = PyTuple_New(3);

	// name
    PyTuple_SET_ITEM(result, 0, PyString_FromString(type->getName().u_str()));
	// abstract
	PyTuple_SET_ITEM(result, 1, PyBool_FromLong(type->isAbstract()));
	// module name
	PyTuple_SET_ITEM(result, 2, PyString_FromString(Kernel::instance()->findModuleByTypeName(type_name)->getName().u_str()));

	return result;
}
