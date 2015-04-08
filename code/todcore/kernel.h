#pragma once
#include <map>
#include "todcore/macro.h"
#include "todcore/module.h"
#include "todcore/node.h"
#include "todcore/ref.h"
#include "todcore/singleton.h"
#include "todcore/string.h"
namespace tod
{ 

class Module;
class TODEXPORT Kernel sealed : public Singleton<Kernel>
{
public:
    typedef std::map<String, Module*> Modules;
    typedef std::map<String, Type*> Types;    
    typedef std::stack<Ref<Node>> NodeStack;

public:
    Kernel();
    ~Kernel();

    Object* create(const str_t* type_name);

    Node* create(const str_t* type_name, const str_t* path);
    Node* find(const str_t* path);

    void pushNode(Node* node);
    Node* popNode();
    Node* topNode();

    void addModule(Module* module);
    Module* findModule(const str_t* name);
    Module* findModuleByTypeName(const str_t* type_name);
    uint32 getNumModules();
    Modules& getModules();
    Types& getTypes();
    Type* findType(const str_t* name);

    Node* getRoot();

private:
    Modules modules;
    Modules modulesByType;
    Types types;
    Ref<Node> root;
    NodeStack nodeStack;

};

}
