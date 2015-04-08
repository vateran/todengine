#include "todpython/todpythonscriptserver.h"
#include "todcore/kernel.h"
#include "todcore/method.h"
#include "todcore/params.h"
#include "todcore/property.h"
#include "todcore/simpleproperty.h"
#include "todcore/typeid.h"

using namespace tod;

//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::build_property_to_pyobject(Object* obj, Property* prop)
{
    if (TypeId<bool>::check(prop->getType()))
    {   
        return Py_BuildValue("b", reinterpret_cast<SimpleProperty<bool>*>(prop)->get(obj));
    }
    else if (TypeId<short>::check(prop->getType()))
    {   
        return Py_BuildValue("h", reinterpret_cast<SimpleProperty<short>*>(prop)->get(obj));
    }
    else if (TypeId<long>::check(prop->getType()))
    {   
        return Py_BuildValue("l", reinterpret_cast<SimpleProperty<long>*>(prop)->get(obj));
    }
    else if (TypeId<int>::check(prop->getType()))
    {   
        return Py_BuildValue("i", reinterpret_cast<SimpleProperty<int>*>(prop)->get(obj));
    }
    else if (TypeId<int16>::check(prop->getType()))
    {   
        return Py_BuildValue("h", reinterpret_cast<SimpleProperty<int16>*>(prop)->get(obj));
    }
    else if (TypeId<uint16>::check(prop->getType()))
    {   
        return Py_BuildValue("H", reinterpret_cast<SimpleProperty<uint16>*>(prop)->get(obj));
    }
    else if (TypeId<int32>::check(prop->getType()))
    {   
        return Py_BuildValue("i", reinterpret_cast<SimpleProperty<int32>*>(prop)->get(obj));
    }
    else if (TypeId<uint32>::check(prop->getType()))
    {   
        return Py_BuildValue("I", reinterpret_cast<SimpleProperty<uint32>*>(prop)->get(obj));
    }
    else if (TypeId<int64>::check(prop->getType()))
    {
        return Py_BuildValue("L", reinterpret_cast<SimpleProperty<int64>*>(prop)->get(obj));
    }
    else if (TypeId<uint64>::check(prop->getType()))
    {
        return Py_BuildValue("K", reinterpret_cast<SimpleProperty<uint64>*>(prop)->get(obj));
    }
    else if (TypeId<float>::check(prop->getType()))
    {
        return Py_BuildValue("f", reinterpret_cast<SimpleProperty<float>*>(prop)->get(obj));
    }
    else if (TypeId<double>::check(prop->getType()))
    {
        return Py_BuildValue("d", reinterpret_cast<SimpleProperty<double>*>(prop)->get(obj));
    }
    else if (TypeId<const String&>::check(prop->getType()))
    {
        return Py_BuildValue("s", reinterpret_cast<SimpleProperty<const String&>*>(prop)->get(obj).u_str());
    }
    else if (TypeId<String>::check(prop->getType()))
    {
        return Py_BuildValue("s", reinterpret_cast<SimpleProperty<String>*>(prop)->get(obj).u_str());
    }
    /*else if (TypeId<const Vector3&>::check(prop->getType()))
    {
        const Vector3* v = &reinterpret_cast<
            SimpleProperty<const Vector3&>*>(prop)->get(obj);
        return Py_BuildValue("(d, d, d)", v->x_, v->y_, v->z_);
    }
    else if (TypeId<const Color&>::check(prop->getType()))
    {
        const Color* c = &reinterpret_cast<
            SimpleProperty<const Color&>*>(prop)->get(obj);
        return Py_BuildValue("(i, i, i, i)", c->r_, c->g_, c->b_, c->a_);
    }*/
    else if (TypeId<Object*>::check(prop->getType()))
    {
        Object* object = reinterpret_cast<SimpleProperty<Object*>*>(prop)->get(obj);
        if (0 == object)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        TodObject* o = reinterpret_cast<TodObject*>(s_TodObjectType.tp_new(&s_TodObjectType, 0, 0));
        if (0 == o)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        o->object = object;
        o->createdByPython = true;
        return reinterpret_cast<PyObject*>(o);
    }
    else if (TypeId<Node*>::check(prop->getType()))
    {
        Node* node = reinterpret_cast<SimpleProperty<Node*>*>(prop)->get(obj);
        if (0 == node)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        TodNode* o = reinterpret_cast<TodNode*>(
            s_TodNodeType.tp_new(&s_TodNodeType, 0, 0));
        if (0 == o)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        o->node = node;
        return reinterpret_cast<PyObject*>(o);
    }
    return 0;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::build_variable_to_pyobject(Variable* variable)
{
    if (TypeId<bool>::check(variable->getType()))
    {   
        return Py_BuildValue("b", reinterpret_cast<VariableBinder<bool>*>(variable)->get());
    }
    else if (TypeId<short>::check(variable->getType()))
    {   
        return Py_BuildValue("h", reinterpret_cast<VariableBinder<short>*>(variable)->get());
    }
    else if (TypeId<long>::check(variable->getType()))
    {   
        return Py_BuildValue("l", reinterpret_cast<VariableBinder<long>*>(variable)->get());
    }
    else if (TypeId<int>::check(variable->getType()))
    {   
        return Py_BuildValue("i", reinterpret_cast<VariableBinder<int>*>(variable)->get());
    }
    else if (TypeId<int16>::check(variable->getType()))
    {   
        return Py_BuildValue("h", reinterpret_cast<VariableBinder<int16>*>(variable)->get());
    }
    else if (TypeId<uint16>::check(variable->getType()))
    {   
        return Py_BuildValue("H", reinterpret_cast<VariableBinder<uint16>*>(variable)->get());
    }
    else if (TypeId<int32>::check(variable->getType()))
    {   
        return Py_BuildValue("i", reinterpret_cast<VariableBinder<int32>*>(variable)->get());
    }
    else if (TypeId<uint32>::check(variable->getType()))
    {   
        return Py_BuildValue("I", reinterpret_cast<VariableBinder<uint32>*>(variable)->get());
    }
    else if (TypeId<int64>::check(variable->getType()))
    {
        return Py_BuildValue("L", reinterpret_cast<VariableBinder<int64>*>(variable)->get());
    }
    else if (TypeId<uint64>::check(variable->getType()))
    {
        return Py_BuildValue("K", reinterpret_cast<VariableBinder<uint64>*>(variable)->get());
    }
    else if (TypeId<float>::check(variable->getType()))
    {
        return Py_BuildValue("f", reinterpret_cast<VariableBinder<float>*>(variable)->get());
    }
    else if (TypeId<double>::check(variable->getType()))
    {
        return Py_BuildValue("d", reinterpret_cast<VariableBinder<double>*>(variable)->get());
    }
    else if (TypeId<String>::check(variable->getType()))
    {
        return Py_BuildValue("s", reinterpret_cast<VariableBinder<String>*>(variable)->get().u_str());
    }
    /*else if (TypeId<Uri>::check(variable->getType()))
    {
        return Py_BuildValue("s",
            reinterpret_cast<VariableBinder<Uri>*>(variable)->get().u_str());
    }
    else if (TypeId<Vector3>::check(variable->getType()))
    {
        Vector3* v = &reinterpret_cast<VariableBinder<Vector3>*>(variable)->get();
        return Py_BuildValue("(d, d, d)", v->x_, v->y_, v->z_);
    }
    else if (TypeId<Color>::check(variable->getType()))
    {
        Color* c = &reinterpret_cast<VariableBinder<Color>*>(variable)->get();
        return Py_BuildValue("(i, i, i, i)", c->r_, c->g_, c->b_, c->a_);
    }*/
    else if (TypeId<Object*>::check(variable->getType()))
    {
        Object* object = reinterpret_cast<VariableBinder<Object*>*>(variable)->get();
        if (0 == object)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        TodObject* o = reinterpret_cast<TodObject*>(
            s_TodObjectType.tp_new(&s_TodObjectType, 0, 0));
        if (0 == o)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        o->object = object;
        o->createdByPython = true;
        return reinterpret_cast<PyObject*>(o);
    }
    else if (TypeId<Node*>::check(variable->getType()))
    {
        Node* node = reinterpret_cast<VariableBinder<Node*>*>(variable)->get();
        if (0 == node)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        TodNode* o = reinterpret_cast<TodNode*>(
            s_TodNodeType.tp_new(&s_TodNodeType, 0, 0));
        if (0 == o)
        {
            Py_INCREF(Py_None);
            return Py_None;
        }
        o->node = node;
        return reinterpret_cast<PyObject*>(o);
    }
    return 0;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::build_input_paramter(tod::Variables* v, PyObject* args, const str_t* method_name)
{
    uint32 num_args = static_cast<uint32>(PyTuple_Size(args));
    for (uint32 a=0; a<num_args; ++a)
    {
        PyObject* arg = PyTuple_GET_ITEM(args, a);        
        if (TypeId<bool>::check(v->getVariable(a)->getType()))
        {
            typedef bool type;
            if (PyBool_Check(arg))
            {
                v->get<type>(a) = PyInt_AsLong(arg)?true:false;
                continue;
            }
            else if (PyInt_Check(arg))
            {
                v->get<type>(a) = PyInt_AsLong(arg)?true:false;
                continue;
            }
            else if (PyFloat_Check(arg))
            {
                v->get<type>(a) = PyFloat_AsDouble(arg)?true:false;
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'int\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<int>::check(v->getVariable(a)->getType()))
        {
            typedef int type;
            if (PyInt_Check(arg))
            {
                v->get<type>(a) = PyInt_AsLong(arg);
                continue;
            }
            else if (PyFloat_Check(arg))
            {
                v->get<type>(a) = static_cast<int>(PyFloat_AsDouble(arg));
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'int\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<float>::check(v->getVariable(a)->getType()))
        {
            typedef float type;
            if (PyInt_Check(arg))
            {
                v->get<type>(a) = static_cast<type>(PyInt_AsLong(arg));
                continue;
            }
            else if (PyFloat_Check(arg))
            {
                v->get<type>(a) = static_cast<type>(PyFloat_AsDouble(arg));
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'float\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<String>::check(v->getVariable(a)->getType()))
        {
            if (PyString_Check(arg))
            {
                v->get<String>(a) = String().format("%s", PyString_AsString(arg));
                continue;
            }
            else if (PyUnicode_Check(arg))
            {
                v->get<String>(a) = String().format((str_t*)(PyUnicode_AS_DATA(arg)));
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'String\'",
                    method_name, arg->ob_type->tp_name);
        }
        /*else if (TypeId<Uri>::check(v->get(a)->getType()))
        {
            if (PyString_Check(arg))
            {
                v->get<Uri>(a) = String("%s", PyString_AsString(arg));
                continue;
            }
            else if (PyUnicode_Check(arg))
            {
                v->get<Uri>(a) = String((char_t*)(PyUnicode_AS_DATA(arg)));
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'Uri\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<Vector3>::check(v->get(a)->getType()))
        {
            if (PyTuple_Check(arg))
            {
                Vector3& tv = v->get<Vector3>(a).get();
                if (PyTuple_Size(arg) == 3)
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        float value = 0;
                        PyObject* o = PyTuple_GET_ITEM(arg, i);
                        if (PyInt_Check(o))
                            value = static_cast<float>(PyInt_AsLong(o));
                        else if (PyFloat_Check(o))
                            value = static_cast<float>(PyFloat_AsDouble(o));
                        tv.a_[i] = value;
                    }
                    continue;
                }
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'Vector3\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<Color>::check(v->get(a)->getType()))
        {
            if (PyTuple_Check(arg))
            {
                Color& tc = v->get<Color>(a).get();
                if (PyTuple_Size(arg) == 4)
                {
                    for (int i = 0; i < 4; ++i)
                    {
                        int value = 0;
                        PyObject* o = PyTuple_GET_ITEM(arg, i);
                        if (PyInt_Check(o))
                            value = PyInt_AsLong(o);
                        else if (PyFloat_Check(o))
                            value = static_cast<int>(PyFloat_AsDouble(o));
                        tc.array_[i] = value;
                    }
                    continue;
                }
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'Color\'",
                    method_name, arg->ob_type->tp_name);
        }*/
        else if (TypeId<Object*>::check(v->getVariable(a)->getType()))
        {
            if (PyObject_TypeCheck(arg, &s_TodObjectType))
            {
                TodObject* o = reinterpret_cast<TodObject*>(arg);
                v->get<Object*>(a) = o->object;
                continue;
            }
            
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'TodObject\'",
                    method_name, arg->ob_type->tp_name);
        }
        else if (TypeId<Node*>::check(v->getVariable(a)->getType()))
        {
            if (PyObject_TypeCheck(arg, &s_TodNodeType))
            {
                TodNode* o = reinterpret_cast<TodNode*>(arg);
                v->get<Node*>(a) = o->node;
                continue;
            }
            return PyErr_Format(PyExc_TypeError,
                "%s() : cannot convert parameter from \'%s\' to \'TodNode\'",
                    method_name, arg->ob_type->tp_name);
        }
        else
        {
            return PyErr_Format(PyExc_TypeError,
                "%s() : not supported parameter type \'%s\'",
                    method_name, arg->ob_type->tp_name);
        }
    }

    return Py_True;
}


//-----------------------------------------------------------------------------
int TodPythonScriptServer::set_property(tod::Object* object, const str_t* path, PyObject* name, PyObject* value)
{
    //find property
    char* prop_name = PyString_AsString(name);
    Property* prop = object->getType()->findProperty(String().format("%s", prop_name).u_str());
    if (nullptr == prop)
    {
        PyErr_Format(PyExc_AttributeError,
            "\'%s\' object has no property \'%s\'", path, prop_name);
        return -1;
    }

    //set property    
    if (TypeId<bool>::check(prop->getType()))
    {
        typedef SimpleProperty<bool> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        if (PyBool_Check(value))
            ap->set(object, Py_True == value ? true:false);
        else if (PyInt_Check(value))
            ap->set(object, PyInt_AsLong(value) ? true:false);
        else if (PyFloat_Check(value))
            ap->set(object, PyFloat_AsDouble(value) ? true:false);
        else if (PyString_Check(value))
        {
            char* v = PyString_AsString(value);
            if (stricmp(v, "true") == 0 ||
                stricmp(v, "t") == 0 ||
                stricmp(v, "on") == 0)
                ap->set(object, true);
            else
                ap->set(object, false);
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'int\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<int>::check(prop->getType()))
    {
        typedef SimpleProperty<int> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        if (PyInt_Check(value))
            ap->set(object, PyInt_AsLong(value));
        else if (PyFloat_Check(value))
            ap->set(object, static_cast<int>(PyFloat_AsDouble(value)));
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'int\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<float>::check(prop->getType()))
    {
        typedef SimpleProperty<float> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        if (PyFloat_Check(value))
            ap->set(object, static_cast<float>(PyFloat_AsDouble(value)));
        else if (PyInt_Check(value))
            ap->set(object, static_cast<float>(PyInt_AsLong(value)));
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'float\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<double>::check(prop->getType()))
    {
        typedef SimpleProperty<double> AdaptiveProperty;
        AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
        if (PyFloat_Check(value))
            ap->set(object, PyFloat_AsDouble(value));
        else if (PyInt_Check(value))
            ap->set(object, PyInt_AsLong(value));
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'double\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    if (TypeId<String>::check(prop->getType()))
    {
        if (PyString_Check(value))
        {
            typedef SimpleProperty<const String&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(object, String().format("%s", PyString_AsString(value)));
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'String\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    /*else if (TypeId<Uri>::check(prop->getType()))
    {
        if (PyString_Check(value))
        {
            typedef SimpleProperty<const Uri&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->set(object, String("%s", PyString_AsString(value)).u_str());
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Uri\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<Vector3>::check(prop->getType()))
    {
        if (PyTuple_Check(value))
        {
            typedef SimpleProperty<const Vector3&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            Vector3 v;
            for (int i = 0; i < 3; ++i)
            {
                PyObject* e = PyTuple_GET_ITEM(value, i);
                if (PyInt_Check(e))
                    v.set(i, static_cast<float>(PyInt_AsLong(e)));
                else if (PyFloat_Check(e))
                    v.set(i, static_cast<float>(PyFloat_AsDouble(e)));
            }
            ap->set(object, v);
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Vector3\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<Color>::check(prop->getType()))
    {
        if (PyTuple_Check(value))
        {
            typedef SimpleProperty<const Color&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            Color v(
                todpython_toint(PyTuple_GET_ITEM(value, 0)),
                todpython_toint(PyTuple_GET_ITEM(value, 1)),
                todpython_toint(PyTuple_GET_ITEM(value, 2)),
                todpython_toint(PyTuple_GET_ITEM(value, 3)));
            ap->set(object, v);
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Color\'",
                value->ob_type->tp_name);
            return -1;
        }
    }
    else if (TypeId<Format>::check(prop->getType()))
    {
        if (PyString_Check(value))
        {
            typedef SimpleProperty<const Format&> AdaptiveProperty;
            AdaptiveProperty* ap = static_cast<AdaptiveProperty*>(prop);
            ap->fromString(object, String("%s", PyString_AsString(value)).u_str());
        }
        else
        {
            PyErr_Format(PyExc_TypeError,
                "cannot convert value from \'%s\' to \'Format\'",
                value->ob_type->tp_name);
            return -1;
        }
    }*/

    return 0;
}


//-----------------------------------------------------------------------------
PyObject* TodPythonScriptServer::invoke_method(Object* object, Method* method, PyObject* args, PyObject* keys)
{
    // make input parameter
    uint32 num_args = static_cast<uint32>(PyTuple_Size(args));
    Params& params = method->getParams();
    if (num_args != params.in().size())
        return PyErr_Format(PyExc_TypeError,
            "%s() takes exactly %d argument(%d given)",
                method->getName().u_str(), params.in().size(), num_args);

    if (!TodPythonScriptServer::build_input_paramter(&params.in(), args, method->getName().u_str())) return nullptr;

    // invoke method
    method->invoke(object);

    // make output parameter
    switch (params.out().size())
    {
        // parameter size == 0
    case 0:
        Py_INCREF(Py_None);
        return Py_None;
        // parameter size == 1
    case 1:
        return build_variable_to_pyobject(params.out().getVariable(0));
        // parameter size > 1
    default:
        {
            PyObject* result = PyTuple_New(params.out().size());
            for (uint32 a=0; a<params.out().size(); ++a)
            {
                PyTuple_SET_ITEM(result, a, build_variable_to_pyobject(params.out().getVariable(a)));
            }
            return result;
        }
    }
}


//-----------------------------------------------------------------------------
TodPythonScriptServer::TodNode* TodPythonScriptServer::find_todnode(const str_t* path)
{
    auto i = s_todobjects.find(path);
    if (i == s_todobjects.end()) return nullptr;
    return i->second;
}


//-----------------------------------------------------------------------------
TodPythonScriptServer::TodNode* TodPythonScriptServer::new_todnode(const str_t* type_name, const str_t* path)
{
    TodNode* exist_obj = find_todnode(path);
    if (exist_obj)
    {
        Py_INCREF(exist_obj);
        return exist_obj;
    }

    TodNode* o = reinterpret_cast<TodNode*>(s_TodNodeType.tp_new(&s_TodNodeType, 0, 0));
    if (nullptr == o) return nullptr;

    o->node = Kernel::instance()->create(type_name, path);
    if (o->node.invalid())
    {
        Py_DECREF(o);
        return nullptr;
    }

    s_todobjects.insert(TodNodes::value_type(o->node->getAbsolutePath(), o));
    return o;
}


//-----------------------------------------------------------------------------
int TodPythonScriptServer::todpython_toint(PyObject* value)
{
    if (PyInt_Check(value)) return PyInt_AsLong(value);
    else if (PyFloat_Check(value)) return static_cast<int>(PyFloat_AsDouble(value));
    return 0;
}
