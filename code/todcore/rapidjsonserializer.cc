#include "todcore/rapidjsonserializer.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
namespace tod
{

//-----------------------------------------------------------------------------
bool RapidJsonSerializer::serialize(Node* node, OUT String& out)
{
    rapidjson::Document doc;
    doc.SetArray();
    if (!this->write_to_json(node, doc, doc))
    {
        TOD_TRACE();
        return false;
    }

    rapidjson::GenericStringBuffer<rapidjson::UTF8<char>> buffer;
    rapidjson::PrettyWriter<rapidjson::GenericStringBuffer<rapidjson::UTF8<char>>> writer(buffer);
    doc.Accept(writer);
        
    out = buffer.GetString();

    return true;
}


//-----------------------------------------------------------------------------
Node* RapidJsonSerializer::deserialize(const String& in)
{
    rapidjson::Document doc;
    if (doc.ParseInsitu<rapidjson::kParseInsituFlag>(const_cast<char*>(in.u_str())).HasParseError())
    {
        TOD_TRACE();
        return nullptr;
    }

    return this->read_from_json(doc);
}


//-----------------------------------------------------------------------------
bool RapidJsonSerializer::write_to_json(Node* node, rapidjson::Value& out, rapidjson::Document& doc)
{
    rapidjson::Value jval(rapidjson::kObjectType);
    jval.AddMember("type", node->getType()->getName().c_str(), doc.GetAllocator());
                
    if (!this->write_to_prop(node, jval, doc))
    {
        TOD_TRACE();
        return false;
    }

    if (node->getNumChildren())
    {
        unsigned int count = 0;
        rapidjson::Value children;
        children.SetArray();
        for (auto i=node->getChildren().begin();i!=node->getChildren().end();++i, ++count)
        {
            if (!write_to_json(i->second, children, doc))
            {
                TOD_TRACE();
                return false;
            }
        }

        jval.AddMember("child", children, doc.GetAllocator());
    }

    out.PushBack(jval, doc.GetAllocator());
    return true;
}
    

//-----------------------------------------------------------------------------
bool RapidJsonSerializer::write_to_prop(Node* node, rapidjson::Value& out, rapidjson::Document& doc)
{
    rapidjson::Value& jprop = out.AddMember("prop", rapidjson::kObjectType, doc.GetAllocator());

    Type* type = node->getType();
    while (type)
    {
        for (auto i : type->getProperties())
        {
            if (i.second->isReadOnly()) continue;
            if (i.second->isEqualDefaultValue(node)) continue;

            String s;
            i.second->toString(node, s);
            jprop.AddMember(i.first.c_str(), s.c_str(), doc.GetAllocator());
        }
        type = type->getBaseType();
    }
        
    return true;
}


//-----------------------------------------------------------------------------
Node* RapidJsonSerializer::read_from_json(const rapidjson::Value& jval)
{
    Type* type = Kernel::instance()->findType(jval["type"].GetString());
    if (type == nullptr) return nullptr;

    Node* node = static_cast<Node*>(type->create());
    if (node == nullptr) return nullptr;

    if (!this->read_prop_from_json(node, jval["prop"]))
    {
        TOD_TRACE();
        return nullptr;
    }

    const rapidjson::Value& children = jval["child"];
    if (!children.IsNull())
    {
        for (auto i=children.Begin();i!=children.End();++i)
        {
            Node* child_node = this->read_from_json(*i);
            node->addChild(child_node);
        }
    }

    return node;
}


//-----------------------------------------------------------------------------
bool RapidJsonSerializer::read_prop_from_json(Object* object, const rapidjson::Value& jval)
{
    if (jval.IsNull()) return true;

    Type* type = object->getType();
    while (type)
    {
        for (auto i=jval.MemberBegin();i!=jval.MemberEnd();++i)
        {
            Property* prop = type->findProperty(i->name.GetString());
            if (prop == 0) continue;
            prop->fromString(object, i->value.GetString());
        }
        type = type->getBaseType();
    }
    //object->onLoad();

    return true;
}

}
