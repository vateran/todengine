#include "todcore/autoreleasepool.h"
#include "todcore/object.h"

namespace tod
{

//-----------------------------------------------------------------------------
AutoReleasePool::~AutoReleasePool()
{
    this->pump();
}


//-----------------------------------------------------------------------------
void AutoReleasePool::add(Object* o)
{
    this->pool.emplace_back(o);
}


//-----------------------------------------------------------------------------
void AutoReleasePool::remove(Object* o)
{
    this->pool.remove(o);
}


//-----------------------------------------------------------------------------
void AutoReleasePool::pump()
{
    this->pool.clear();
}

}
