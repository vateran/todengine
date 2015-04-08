#pragma once
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "todcore/serializer.h"
namespace tod
{

class TODEXPORT RapidJsonSerializer : public Serializer
{
public:
    OVERRIDE bool serialize(Node* node, OUT String& out);
    OVERRIDE Node* deserialize(const String& in);

private:
    bool write_to_json(Node* node, rapidjson::Value& out, rapidjson::Document& doc);
    bool write_to_prop(Node* node, rapidjson::Value& out, rapidjson::Document& doc);
    Node* read_from_json(const rapidjson::Value& jval);
    bool read_prop_from_json(Object* object, const rapidjson::Value& jval);
};

}

