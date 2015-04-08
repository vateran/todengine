#include "todcore/kernel.h"
#include "todcore/builtinmodule.h"
#include "todcore/tokenizer.h"

namespace tod
{

//-----------------------------------------------------------------------------
Kernel::Kernel()
{
    this->addModule(new BuiltinModule());
    this->root = dynamic_cast<Node*>(this->create(S("Node")));
    this->nodeStack.push(this->root);
}


//-----------------------------------------------------------------------------
Kernel::~Kernel()
{
    while (this->nodeStack.size()) this->nodeStack.pop();
    Module* m = this->findModule("builtin");
    SAFE_DELETE(m);
}


//-----------------------------------------------------------------------------
Object* Kernel::create(const str_t* type_name)
{
    auto i = this->types.find(type_name);
    if (this->types.end() == i) return nullptr;

    Type* type = i->second;
    return type->create();
}


//-----------------------------------------------------------------------------
Node* Kernel::create(const str_t* type, const str_t* path)
{
    Tokenizer tok(path, S('/'));

    Node* cur = nullptr;
    if (path[0] == S('/')) cur = this->root;
    else cur = this->nodeStack.top();

    for (auto i=tok.begin();i!=tok.end();++i)
    {
        Node* child = cur->findChildByName(i->u_str());
        if (nullptr == child)
        {
            Node* new_node = nullptr;
            auto e = i;
            if (tok.end() == ++e)
                new_node = static_cast<Node*>(this->create(type));
            else
                new_node = static_cast<Node*>(this->create(S("Node")));
            if (nullptr == new_node) return nullptr;
            new_node->setName(i->u_str());
            cur->addChild(new_node);
            cur = new_node;
        }
        else
            cur = child;
    }
    
    return cur;
}


//-----------------------------------------------------------------------------
Node* Kernel::find(const str_t* path)
{
    if (TOD_STRCMP(path, S("/"))==0) return this->root;
    if (path[0] == S('/')) return this->root->relativeNode(path);
    return this->nodeStack.top()->relativeNode(path);
}


//-----------------------------------------------------------------------------
void Kernel::pushNode(Node* node)
{
    this->nodeStack.push(node);
}


//-----------------------------------------------------------------------------
Node* Kernel::popNode()
{
    Node* node = this->nodeStack.top();
    this->nodeStack.pop();
    return node;
}


//-----------------------------------------------------------------------------
Node* Kernel::topNode()
{
    return this->nodeStack.top();
}


//-----------------------------------------------------------------------------
void Kernel::addModule(Module* module)
{
    this->modules.insert(Modules::value_type(module->getName(), module));

    for (auto i : module->getTypes())
    {
        this->types.insert(Types::value_type(i.first, i.second));
        this->modulesByType.insert(Modules::value_type(i.first, module));
    }
}


//-----------------------------------------------------------------------------
Module* Kernel::findModule(const str_t* name)
{
    auto i = this->modules.find(name);
    if (this->modules.end() == i) return nullptr;
    return i->second;
}


//-----------------------------------------------------------------------------
Module* Kernel::findModuleByTypeName(const str_t* type_name)
{
    auto i = this->modulesByType.find(type_name);
    if (this->modulesByType.end() == i) return nullptr;
    return i->second;
}


//-----------------------------------------------------------------------------
uint32 Kernel::getNumModules()
{
    return this->modules.size();
}


//-----------------------------------------------------------------------------
Kernel::Modules& Kernel::getModules()
{
    return this->modules;
}


//-----------------------------------------------------------------------------
Kernel::Types& Kernel::getTypes()
{
    return this->types;
}


//-----------------------------------------------------------------------------
Type* Kernel::findType(const str_t* name)
{
    auto i = this->types.find(name);
    if (this->types.end() == i) return nullptr;
    return i->second;
}


//-----------------------------------------------------------------------------
Node* Kernel::getRoot()
{
    return this->root;
}

}
