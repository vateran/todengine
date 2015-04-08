#pragma once
#include <python.h>
#include "todcore/scriptserver.h"
namespace tod
{






class TODEXPORT TodPythonScriptServer : public Derive<TodPythonScriptServer, ScriptServer>
{
public:
    TodPythonScriptServer();
    virtual~TodPythonScriptServer();

    OVERRIDE bool run(const str_t* command, OUT String* result);
    OVERRIDE bool call(const str_t* func_name, Params& params);
    OVERRIDE bool runFile(const str_t* fname, OUT String* result);

private:
    void initialize_python();

public:
    struct TodObject
    {
        PyObject_HEAD
        tod::Object* object;
        tod::Method* method;
        bool createdByPython;
    
        TodObject():method(0), createdByPython(false) {}
    };
    struct TodNode
    {
        PyObject_HEAD
        tod::Ref<tod::Node> node;
        tod::Method* method;

        TodNode():method(0) {}
    };
    typedef std::map<String, TodNode*> TodNodes;

private:
    static PyObject* s_module;
    static PyMethodDef TodPythonScriptServer::s_TodPythonMethods[];
    static PyTypeObject s_TodObjectType;    
    static PyTypeObject s_TodNodeType;
    static TodNodes s_todobjects;

public:
    static PyObject* build_property_to_pyobject(Object* obj, Property* prop);
    static PyObject* build_variable_to_pyobject(Variable* variable);
    static PyObject* build_input_paramter(Variables* v, PyObject* args, const str_t* method_name);
    static int set_property(Object* object, const str_t* path, PyObject* name, PyObject* value);
    static PyObject* invoke_method(Object* object, tod::Method* method, PyObject* args, PyObject* keys);
    static TodNode* find_todnode(const str_t* path);
    static TodNode* new_todnode(const str_t* type_name, const str_t* path);
    static int todpython_toint(PyObject* value);

    static PyObject* command_newobj(PyObject* self, PyObject* args);
    static PyObject* command_new(PyObject* self, PyObject* args);
    static PyObject* command_get(PyObject* self, PyObject* args);
    static PyObject* command_delete(PyObject* self, PyObject* args);
    static PyObject* command_ls(PyObject* self, PyObject* args);
    static PyObject* command_pushCwn(PyObject* self, PyObject* args);
    static PyObject* command_popCwn(PyObject* self, PyObject* args);
    static PyObject* command_todprint(PyObject* self, PyObject* args);
    static PyObject* command_exit(PyObject* self, PyObject* args);
    static PyObject* command_serialize(PyObject* self, PyObject* args);
    static PyObject* command_deserialize(PyObject* self, PyObject* args);
    static PyObject* command_getModuleList(PyObject* self, PyObject* args);
    static PyObject* command_getTypeList(PyObject* self, PyObject* args);
    static PyObject* command_getDerivedTypes(PyObject* self, PyObject* args);
    static PyObject* command_getTypeInfo(PyObject* self, PyObject* args);

    static PyObject* TodObject_new(PyTypeObject* type, PyObject* args, PyObject* keys);
    static void TodObject_dealloc(PyObject* self);
    static PyObject* TodObject_getattro(TodObject* self, PyObject* name);
    static PyObject* TodObject_call(PyObject* self, PyObject* args, PyObject* keys);
    static int TodObject_setattro(TodObject* self, PyObject* name, PyObject* value);

    static PyObject* TodNode_new(PyTypeObject* type, PyObject* args, PyObject* keys);
    static void TodNode_dealloc(PyObject* self);
    static PyObject* TodNode_repr(TodNode* self);
    static PyObject* TodNode_getattro(TodNode* self, PyObject* name);
    static PyObject* TodNode_call(PyObject* self, PyObject* args, PyObject* keys);
    static int TodNode_setattro(TodNode* self, PyObject* name, PyObject* value);

};






}


