#pragma once
#include <list>
#include "todcore/macro.h"
namespace tod
{ 
/**
    @class SingletonMgr
    @ingroup TodEngineUtility
    @brief TodEngine상에 존재하는 모든 Singleton객체의 생성/파괴를 관리한다.
*/
class SingletonBase;
class TODEXPORT SingletonMgr
{
public:
    SingletonMgr();
    ~SingletonMgr();

    void clear();
    void add(SingletonBase* o);
    void remove(SingletonBase* o);

public:
    ///singleton access
    static SingletonMgr* instance();
    static void dispose();

private:    
    typedef std::list<SingletonBase*> Singletons;
    Singletons singletons;
};

}
