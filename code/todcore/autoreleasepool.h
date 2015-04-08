#pragma once
#include <list>
#include "todcore/macro.h"
#include "todcore/singleton.h"
#include "todcore/ref.h"
namespace tod
{ 

class Object;
class TODEXPORT AutoReleasePool : public Singleton<AutoReleasePool>
{
public:
    virtual~AutoReleasePool();

    void add(Object* o);
    void remove(Object* o);

    void pump();

private:
    typedef std::list<Ref<Object>> Pool;

private:
    Pool pool;
};

}
