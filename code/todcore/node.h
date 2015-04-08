#pragma once
#include <map>
#include "todcore/object.h"
#include "todcore/ref.h"
#include "todcore/string.h"
#include "todcore/type.h"
namespace tod
{ 
/**
    @class Node
    @ingroup TodCoreKernel
    @brief Named object
*/

class TODEXPORT Node : public Derive<Node, Object>
{
public:
    typedef Ref<Node> RefNode;
    typedef std::map<String, RefNode> Nodes;

public:
    Node();
    virtual~Node();

    void setName(const String& name);
    const String& getName();
    String getAbsolutePath();
    void addChild(Node* c);
    void removeChild(Node* c);
    void removeChildrenByName(const str_t* name);
    void removeFromParent();
    void removeAllChilren();
    Node* getParent();
    Node* findChildByName(const str_t* name);
    Node* relativeNode(const str_t* path);
    uint32 getNumChildren();
    Nodes& getChildren();

    static void bindMethod();
    static void bindProperty();

private:
    String name;
    Node* parent;
    Nodes children;
};


}
