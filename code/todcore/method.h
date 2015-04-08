#pragma once
#include <functional>
#include <vector>
#include "todcore/macro.h"
#include "todcore/string.h"
#include "todcore/params.h"
namespace tod
{ 

class Object;
class TODEXPORT Method
{
public:
    typedef std::function<void(Object*)> Callback;

public:
    Method(const str_t* prototype);
    virtual~Method();

    virtual void invoke(Object* self)=0;
    virtual void invokeAsync(Object* self, Callback callback)=0;

    const String& getName();
    Params& getParams();

private:
    void initialize(const str_t* prototype);
    void build_params(const str_t* p, INOUT Variables& v);

private:
    String name;
    Params params;
};

}
