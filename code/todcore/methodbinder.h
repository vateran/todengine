#pragma once
#include <functional>
#include <thread>
#include "todcore/method.h"
#include "todcore/scheduler.h"
namespace tod
{ 

template <typename T>
class TODEXPORT MethodBinder : public Method
{
public:
    typedef std::function<void(T*,Params&)> BindFunc;

public:
    MethodBinder(const str_t* prototype):Method(prototype) {}

    OVERRIDE void invoke(Object* self)
    {
        this->bindFunc(dynamic_cast<T*>(self), this->getParams());
    }
    OVERRIDE void invokeAsync(Object* self, Callback callback)
    {
        Scheduler::instance()->addTask(self, this);
    }

    void setFunction(const BindFunc& f)
    {
        this->bindFunc = f;
    }

private:
    BindFunc bindFunc;

};

#define BIND_METHOD(method_name, func_body) \
    do {\
    static MethodBinder<SelfType> s_##method_name##_method(#method_name);\
    s_##method_name##_method.setFunction([] (SelfType* self, Params& params) func_body);\
    SelfType::get_type()->addMethod(&s_##method_name##_method); } while (false)

}
