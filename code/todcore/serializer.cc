#include "todcore/serializer.h"
#include "todcore/jsoncppserializer.h"
#include "todcore/rapidjsonserializer.h"
#include "todcore/msgpackserializer.h"

namespace tod
{

//-----------------------------------------------------------------------------
bool Serializer::serialize(Node* node, Parser parser, OUT String& out)
{
    switch (parser)
    {
    case PARSER_JSONCPP:
        {
            JsonCppSerializer s;
            return s.serialize(node, out);
        }
    case PARSER_RAPIDJSON:
        {
            //not implement
            //RapidJsonSerializer s;
            //return s.serialize(node, out);
            return false;
        }
    case PARSER_MSGPACK:
        {
            MsgPackSerializer s;
            return s.serialize(node, out);
        }
    };

    return false;
}


//-----------------------------------------------------------------------------
Node* Serializer::deserialize(Parser parser, const String& in)
{
    switch (parser)
    {
    case PARSER_JSONCPP:
        {
            JsonCppSerializer s;
            return s.deserialize(in);
        }
    case PARSER_RAPIDJSON:
        {
            RapidJsonSerializer s;
            return s.deserialize(in);
        }
    case PARSER_MSGPACK:
        {
        }
    }

    return nullptr;
}


//-----------------------------------------------------------------------------
bool Serializer::serializeToFile(Node* node, Parser parser, const str_t* fname)
{
    String out;
    if (!this->serialize(node, parser, out)) return false;
    FILE* fp = fopen(fname, "wb");
    fwrite(out.c_str(), out.size(), 1, fp);
    fclose(fp);
    return true;
}


//-----------------------------------------------------------------------------
Node* Serializer::deserializeFromFile(Parser parser, const str_t* fname)
{
    String in;
    FILE* fp = fopen(fname, "rb");
    if (nullptr==fp) return nullptr;
    fseek(fp, 0, SEEK_END);
    size_t fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    in.resize(fsize);
    fread(&in[0], fsize, 1, fp);
    fclose(fp);

    return this->deserialize(parser, in);
}

}

