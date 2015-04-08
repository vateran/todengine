#pragma once
#include <stdlib.h>
#include "todcore/basetype.h"
#include "todcore/string.h"
namespace tod
{ 

template <typename TYPE>
class StringConv
{
};






template <>
class StringConv<bool>
{
public:
    static bool fromString(const str_t* value)
    {
        return (value[0] == 't' || value[0] == 'T');
    }
    static void toString(bool value, OUT String& s)
    {
        if (value) s.assign(S("true"));
        else s.assign(S("false"));
    }
};






template <>
class StringConv<int>
{
public:
    static int fromString(const str_t* value)
    {
        return atoi(value);
    }
    static void toString(int value, OUT String& s)
    {
        str_t buf[16];
        TOD_SNPRINTF(buf, 16, S("%d"), value);
        s.assign(buf);
    }
};







template <>
class StringConv<uint32>
{
public:
    static uint32 fromString(const str_t* value)
    {
        return atoi(value);
    }
    static void toString(uint32 value, OUT String& s)
    {
        str_t buf[16];
        TOD_SNPRINTF(buf, 16, S("%lu"), value);
        s.assign(buf);
    }
};







template <>
class StringConv<float>
{
public:
    static float fromString(const str_t* value)
    {
        return static_cast<float>(atof(value));
    }
    static void toString(float value, OUT String& s)
    {
        str_t buf[32];
        TOD_SNPRINTF(buf, 32, S("%f"), value);
        s.assign(buf);
    }
};







template <>
class StringConv<String>
{
public:
    static const str_t* fromString(const str_t* value)
    {
        return value;
    }
    static void toString(const String& value, OUT String& s)
    {
        s = value;
    }
};







template <>
class StringConv<const String&>
{
public:
    static const str_t* fromString(const str_t* value)
    {
        return value;
    }
    static void toString(const String& value, OUT String& s)
    {
        s = value;
    }
};






template <>
class StringConv<const char*>
{
public:
    static const char* fromString(const char* value)
    {
        return value;
    }
    static void toString(const char* value, String& s)
    {
        s = value;
    }
};







template <>
class StringConv<const Color&>
{
public:
    static Color fromString(const str_t* value)
    {
        Color c;
        c.fromString(value);
        return c;
    }
    static void toString(const Color& value, OUT String& s)
    {
        value.toString(s);
    }
};




}
