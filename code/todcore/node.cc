#include "todcore/node.h"
#include <stack>
#include "todcore/tokenizer.h"
#include "todcore/methodbinder.h"
#include "todcore/simplepropertybinder.h"

namespace tod
{

//-----------------------------------------------------------------------------
Node::Node():parent(nullptr)
{
}


//-----------------------------------------------------------------------------
Node::~Node()
{
}


//-----------------------------------------------------------------------------
void Node::setName(const String& name)
{
    this->name.assign(name);
}


//-----------------------------------------------------------------------------
const String& Node::getName()
{
    return this->name;
}


//-----------------------------------------------------------------------------
String Node::getAbsolutePath()
{
    std::stack<Node*> s;
    Node* cur = this;
    while (cur)
    {
        if (cur->parent) s.push(cur);
        cur = cur->parent;
    }

    String path;
    while (!s.empty())
    {
        path += S("/");
        path += s.top()->getName();
        s.pop();
    }

    return path;
}


//-----------------------------------------------------------------------------
void Node::addChild(Node* c)
{   
    this->children.insert(Nodes::value_type(c->getName(), c));
    c->parent = this;
}


//-----------------------------------------------------------------------------
void Node::removeChild(Node* c)
{
    c->parent = nullptr;
    this->children.erase(c->getName());
}


//-----------------------------------------------------------------------------
void Node::removeChildrenByName(const str_t* name)
{
    for (auto i=this->children.begin(); i!=this->children.end();)
    {
        if (i->second->getName() == name) TOD_ERASE_LIST_ELEM(this->children, i);
        else ++i;
    }
}


//-----------------------------------------------------------------------------
void Node::removeFromParent()
{
    if (this->parent) this->parent->removeChild(this);
}


//-----------------------------------------------------------------------------
void Node::removeAllChilren()
{
    this->children.clear();
}


//-----------------------------------------------------------------------------
Node* Node::getParent()
{
    return this->parent;
}


//-----------------------------------------------------------------------------
Node* Node::findChildByName(const str_t* name)
{
    for (auto c : this->children)
    {
        if (c.second->getName() == name) return c.second;
    }
    return nullptr;
}


//-----------------------------------------------------------------------------
Node* Node::relativeNode(const str_t* path)
{
    if (TOD_STRCMP(path, S("."))==0) return this;
    else if (TOD_STRCMP(path, S(".."))==0) return this->getParent();
    else
    {
        Node* cur = this;
        Tokenizer tok(path, S('/'));
        for (auto i=tok.begin();i!=tok.end();++i)
        {
            Node* next = nullptr;
            if (*i==S(".")) continue;
            else if (*i==S("..")) next = cur->getParent();
            else next = cur->findChildByName(i->u_str());
            if (nullptr == next) return nullptr;
            cur = next;
        }
        return cur;
    }
}


//-----------------------------------------------------------------------------
uint32 Node::getNumChildren()
{
    return this->children.size();
}


//-----------------------------------------------------------------------------
Node::Nodes& Node::getChildren()
{
    return this->children;
}


//-----------------------------------------------------------------------------
void Node::bindMethod()
{
    BIND_METHOD(v_addChild_n, { self->addChild(params.in().get<Node*>(0)); });
    BIND_METHOD(v_removeChild_n, { self->removeChild(params.in().get<Node*>(0)); });
    BIND_METHOD(v_removeChildrenByName_s, { self->removeChildrenByName(params.in().get<String>(0).u_str()); });
    BIND_METHOD(v_removeFromParent_v, { self->removeChildrenByName(params.in().get<String>(0).u_str()); });
    BIND_METHOD(v_removeAllChilren_v, { self->removeAllChilren(); });
    BIND_METHOD(n_getParent_v, { params.out().set<Node*>(0, self->getParent()); });
    BIND_METHOD(n_findChildByName_s, { params.out().set<Node*>(0, self->findChildByName(params.in().get<String>(0).u_str())); });
    BIND_METHOD(n_relativeNode_s, { params.out().set<Node*>(0, self->relativeNode(params.in().get<String>(0).u_str())); });
    BIND_METHOD(s_getAbsolutePath_v, { params.out().set<String>(0, self->getAbsolutePath()); });
}


//-----------------------------------------------------------------------------
void Node::bindProperty()
{
    BIND_PROPERTY(const String&, name, setName, getName, { static String d; return d; });
    BIND_PROPERTY_READONLY(uint32, num_children, getNumChildren, { return 0; });
}

}
