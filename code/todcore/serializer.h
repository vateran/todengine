#pragma once
#include "todcore/node.h"
#include "todcore/kernel.h"
#include "todcore/property.h"
#include "todcore/string.h"
namespace tod
{

class TODEXPORT Serializer
{
public:
    enum Parser
    {
        PARSER_JSONCPP,
        PARSER_RAPIDJSON,
        PARSER_MSGPACK,
    };

public:
    bool serialize(Node* node, Parser parser, OUT String& out);
    Node* deserialize(Parser parser, const String& in);
    bool serializeToFile(Node* node, Parser parser, const str_t* fname);
    Node* deserializeFromFile(Parser parser, const str_t* fname);
};

}
