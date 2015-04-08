#include "todcore/singletonmgr.h"
#include "todcore/singleton.h"

namespace tod
{

//-----------------------------------------------------------------------------
SingletonMgr::SingletonMgr()
{
}


//-----------------------------------------------------------------------------
SingletonMgr::~SingletonMgr()
{
    this->clear();
}


//-----------------------------------------------------------------------------
void SingletonMgr::clear()
{
    this->singletons.reverse();
    for (auto i = this->singletons.begin(); i != this->singletons.end();)
    {
        SingletonBase* s = *i;
        i = this->singletons.erase(i);
        delete s;
    }
    this->singletons.clear();
}


//-----------------------------------------------------------------------------
void SingletonMgr::add(SingletonBase* o)
{
    this->singletons.emplace_back(o);
}


//-----------------------------------------------------------------------------
void SingletonMgr::remove(SingletonBase* o)
{
    this->singletons.remove(o);
}


//-----------------------------------------------------------------------------
SingletonMgr* SingletonMgr::instance()
{    
    static SingletonMgr s_instance;
    return &s_instance;
}

}

