#pragma once
#include "todcore/type.h"
namespace tod
{ 


template <typename T>
class TODEXPORT TypeObject : public Type
{
public:
    TypeObject(Type* base)
    {
        this->set_base(base);
        this->set_type_name(typeid(T).name());
    }    
    OVERRIDE Object* create()
    {
        return new T();
    }
    OVERRIDE void bindMethod()
    {
        T::bindMethod();
    }
    OVERRIDE void bindProperty()
    {
        T::bindProperty();
    }
};










template <typename T>
class TODEXPORT AbstractTypeObject : public Type
{
public:
    AbstractTypeObject(Type* base)
    {
        this->set_base(base);
        this->set_type_name(typeid(T).name());
    }    
    OVERRIDE Object* create()
    {
        return 0;
    }
    OVERRIDE void bindMethod()
    {
        T::bindMethod();
    }
    OVERRIDE void bindProperty()
    {
        T::bindProperty();
    }
};


}
