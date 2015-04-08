#pragma once
#include "todcore/macro.h"
#include "todcore/string.h"
namespace tod
{ 

typedef unsigned char byte;
typedef short int16;
typedef unsigned short uint16;
typedef long int32;
typedef unsigned long uint32;
typedef const char* type_id;

struct Color
{
    Color():color(0) {} 
    Color(byte r, byte g, byte b, byte a):r(r), g(g), b(b), a(a) {}
    union
    {
        struct
        {
            byte r;
            byte g;
            byte b;
            byte a;
        };
        byte array[4];
        uint32 color;
    };
    void fromString(const str_t* value);
    void toString(OUT String& s) const;
    bool operator == (const Color& rhs) const
    {
        return this->color == rhs.color;
    }
};

#ifdef TODENGINE_PLATFORM_WIN32
typedef __int64 int64;
typedef unsigned __int64 uint64;
#else
typedef long long int64;
typedef unsigned long long uint64;
#endif


}
