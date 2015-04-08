#pragma once
#include "json/json.h"
#include "todcore/serializer.h"
namespace tod
{

class TODEXPORT JsonCppSerializer : public Serializer
{
public:
    OVERRIDE bool serialize(Node* node, OUT String& out);
    OVERRIDE Node* deserialize(const String& in);

private:
    bool write_to_json(Node* node, Json::Value& out);
    bool write_to_prop(Node* node, Json::Value& out);
    Node* read_from_json(const Json::Value& jval);
    bool read_prop_from_json(Object* object, const Json::Value& jval);
};

}


