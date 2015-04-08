#pragma once
#include "todcore/typeobject.h"
namespace tod
{ 

class Type;
template <typename TYPE, typename BASE>
class TODEXPORT Derive : public BASE
{
public:
    typedef TypeObject<TYPE> ObjectType;
    typedef TYPE SelfType;
    typedef BASE BaseType;
    static Type* get_type()
    {
        static ObjectType s_type(BASE::get_type());
        return &s_type;
    }
    virtual Type* getType()
    {
        return TYPE::get_type();
    }
};








template <typename TYPE, typename BASE>
class TODEXPORT AbstractDerive : public BASE
{
public:
    typedef AbstractTypeObject<TYPE> ObjectType;
    typedef TYPE SelfType;
    typedef BASE BaseType;
    static Type* get_type()
    {
        static ObjectType s_type(BASE::get_type());
        s_type.setAbstract(true);
        return &s_type;
    }
    virtual Type* getType()
    {
        return TYPE::get_type();
    }
};







//'Obejct' type speicialization
template <>
class TODEXPORT Derive<Object, void>
{
public:
    typedef TypeObject<Object> ObjectType;
    typedef Object SelfType;
    static Type* get_type()
    {
        static ObjectType s_type(0);
        return &s_type;
    }
    OVERRIDE Type* getType()
    {
        return Derive<Object, void>::get_type();
    }
};

}
