#include "todpython/todpythonscriptserver.h"

using namespace tod;

//-----------------------------------------------------------------------------
TodPythonScriptServer::TodPythonScriptServer()
{
    if (!Py_IsInitialized())
    {
        Py_Initialize();
    }
    initialize_python();
}


//-----------------------------------------------------------------------------
TodPythonScriptServer::~TodPythonScriptServer()
{
}


//-----------------------------------------------------------------------------
bool TodPythonScriptServer::run(const str_t* command, OUT String* result)
{
    if (PyRun_SimpleString(command) == -1)
        return false;    
    return true;
}


//-----------------------------------------------------------------------------
bool TodPythonScriptServer::call(const str_t* func_name, Params& params)
{
    return false;
}


//-----------------------------------------------------------------------------
bool TodPythonScriptServer::runFile(const str_t* fname, OUT String* result)
{
    return false;
}


//-----------------------------------------------------------------------------
PyMethodDef TodPythonScriptServer::s_TodPythonMethods[] =
{
    { "newobj", TodPythonScriptServer::command_newobj, METH_VARARGS, "create new nonamed TodObject" },
    { "new", TodPythonScriptServer::command_new, METH_VARARGS, "create new TodNode" },
    { "get", TodPythonScriptServer::command_get, METH_VARARGS, "get TobObject from NOH" },
    { "delete", TodPythonScriptServer::command_delete, METH_VARARGS, "delete TodNode" },
    { "ls", TodPythonScriptServer::command_ls, METH_VARARGS, "list current work node" },
    { "pushcwn", TodPythonScriptServer::command_pushCwn, METH_VARARGS, "push current work node" },
    { "popcwn", TodPythonScriptServer::command_popCwn, METH_VARARGS, "pop current work node" },
    { "todprint", TodPythonScriptServer::command_todprint, METH_VARARGS, "debug print" },
    { "exit", TodPythonScriptServer::command_exit, METH_VARARGS, "exit application" },
    { "serialize", TodPythonScriptServer::command_serialize, METH_VARARGS, "serialize objects to resource" },
    { "deserialize", TodPythonScriptServer::command_deserialize, METH_VARARGS, "deserialize objects from resource" },
    { "getModuleList", TodPythonScriptServer::command_getModuleList, METH_VARARGS, "get module list" },
    { "getTypeList", TodPythonScriptServer::command_getTypeList, METH_VARARGS, "get type list specified module name" },
    { NULL, NULL, 0, NULL }        /* Sentinel */
};


//-----------------------------------------------------------------------------
void TodPythonScriptServer::initialize_python()
{
    // initialize TodPython module
    Py_SetProgramName("TodPython");
    //PySys_SetArgv();
    PyObject* g_module = Py_InitModule("todpython", TodPythonScriptServer::s_TodPythonMethods);    

    // initialize exception handler
    PyObject* error_obj = PyErr_NewException("todpython.error", 0, 0);
    Py_INCREF(error_obj);
    PyModule_AddObject(g_module, "error", error_obj);

    // initialize TodObject
    PyType_Ready(&s_TodObjectType);
    Py_INCREF(&s_TodObjectType);
    PyModule_AddObject(g_module, "TodObject", (PyObject*)(&s_TodObjectType));

    // initialize TodNode
    PyType_Ready(&s_TodNodeType);
    Py_INCREF(&s_TodNodeType);
    PyModule_AddObject(g_module, "TodNode", (PyObject*)(&s_TodNodeType));
}


//-----------------------------------------------------------------------------
TodPythonScriptServer::TodNodes TodPythonScriptServer::s_todobjects;
