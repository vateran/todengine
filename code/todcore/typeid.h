#pragma once
#include "todcore/basetype.h"
namespace tod
{

template <typename T>
class TypeId
{
public:
    typedef TypeId<T> type;

public:
    static type_id id()
    {
        return typeid(T).name();
    }
    static bool check(type_id id)
    {
        return TypeId::id() == id;
    }
    static bool check(const type& rhs)
    {
        return TypeId::check(rhs.id());
    }
};

}





