#pragma once
#include <string>
#include <stdarg.h>
#include "todcore/macro.h"
namespace tod
{ 

#ifdef TOD_USING_UNICODE
#define S(s) L ## s
typedef wchar_t str_t;
#else
#define S(s) s
typedef char str_t;
#endif




#ifdef TOD_USING_UNICODE
class TODEXPORT String : public std::wstring
#else
class TODEXPORT String : public std::string
#endif
{
public:
    String()
    {
    }
    String(const str_t* s)
    {
        this->assign(s);
    }
    const String& format(const str_t* format, ...)
    {
        va_list ap;
        str_t buf[4096];
    
        va_start(ap, format);    
        TOD_VSNPRINTF(buf, sizeof(buf), format, ap);    
        va_end(ap);

        this->assign(buf);

        return *this;
    }
    #ifdef TOD_USING_UNICODE
    String(const std::wstring& s):std::wstring(s)
    #else
    String(const std::string& s):std::string(s)
    #endif
    {
        this->assign(s.c_str());
    }
    const str_t* u_str() const
    {
        return &(*this)[0];
    }
};

}
