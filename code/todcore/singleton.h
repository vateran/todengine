#pragma once
#include <stack>
#include "todcore/macro.h"
#include "todcore/singletonmgr.h"
namespace tod
{ 

class TODEXPORT SingletonBase
{
public:
    SingletonBase()
    {
        SingletonMgr::instance()->add(this);
    }
    virtual~SingletonBase()
    {
        SingletonMgr::instance()->remove(this);
    }
};



template <typename T>
class TODEXPORT Singleton : public SingletonBase
{
public:
    static T* instance()
    {
        if (nullptr == Singleton::s_instance)
        {
            Singleton::s_instance = new T();
        }
        return Singleton::s_instance;
    }

private:
    static T* s_instance;

};

template <typename T>
T* Singleton<T>::s_instance = nullptr;

}

