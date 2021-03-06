#pragma once
//#include "msgpack/msgpack.hpp"
#include "todcore/serializer.h"
namespace tod
{




class MsgPackSerializer : public Serializer
{
public:
    virtual bool serialize(Node* node, OUT String& out)
    {
        std::pair<std::string, int> val1 = std::make_pair("test", rand());
        //msgpack::sbuffer sbuf;
        //msgpack::pack(sbuf, val1);
        //msgpack::zone z;
        //msgpack::object obj;
        //msgpack::unpack_return ret =
        //msgpack::unpack(sbuf.data(), sbuf.size(), NULL, &z, &obj);

        /*Json::Value jval;
        if(!this->write_to_json(node, jval))
        {
            TOD_TRACE();
            return false;
        }

        Json::FastWriter writer;
        out = writer.write(jval);*/

        return true;
    }
    virtual Node* deserialize(const String& in)
    {
        /*Json::Value jval;
        Json::Reader reader;
        if(!reader.parse(in, jval))
        {
            TOD_TRACE();
            return nullptr;
        }

        return read_from_json(jval);*/
        return 0;
    }

private:
    /*bool write_to_json(Node* node, Json::Value& out)
    {
        out["type"] = node->getType()->getName().c_str();
                
        if(!this->write_to_prop(node, out))
        {
            TOD_TRACE();
            return false;
        }

        if(node->getNumChildren())
        {
            unsigned int count = 0;
            Json::Value& children = out["child"];
            for(auto i=node->firstChild();i!=node->lastChild();++i, ++count)
            {   
                Json::Value& child = children[count];
                if(!write_to_json(i->second, child))
                {
                    TOD_TRACE();
                    return false;
                }
            }
        }

        return true;
    }
    
    bool write_to_prop(Node* node, Json::Value& out)
    {
        Type* type = node->getType();
        while(type)
        {
            for(auto i : type->getProperties())
            {
                if(i.second->isReadOnly()) continue;
                if(i.second->isEqualDefaultValue(node)) continue;

                String s;
                i.second->toString(node, s);
                out["prop"][i.first.c_str()] = s;
            }
            type = type->getBaseType();
        }

        return true;
    }

    Node* read_from_json(const Json::Value& jval)
    {
        Type* type = Kernel::instance()->findType(jval["type"].asCString());
        if(type == nullptr) return nullptr;

        Node* node = static_cast<Node*>(type->create());
        if(node == nullptr) return nullptr;

        if(!this->read_prop_from_json(node, jval["prop"]))
        {
            TOD_TRACE();
            return nullptr;
        }

        const Json::Value& children = jval["child"];
        if(children != Json::nullValue)
        {
            for(auto i : children)
            {
                Node* child_node = this->read_from_json(i);
                node->addChild(child_node);
            }
        }

        return node;
    }

    bool read_prop_from_json(Object* object, const Json::Value& jval)
    {
        if(jval == Json::nullValue) return true;

        Type* type = object->getType();
        while(type)
        {
            for(auto i=jval.begin();i!=jval.end();++i)
            {
                Property* prop = type->findProperty(i.key().asCString());
                if(prop == 0) continue;
                prop->fromString(object, (*i).asCString());
            }
            type = type->getBaseType();
        }
        //object->onLoad();

        return true;
    }*/
};




}


