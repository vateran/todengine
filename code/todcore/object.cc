#include "todcore/object.h"
#include "todcore/autoreleasepool.h"
#include "todcore/simplepropertybinder.h"

namespace tod
{

//-----------------------------------------------------------------------------
Object::Object():refCount(0)
{
    this->id = Object::s_id++;
    this->autorelease();
}


//-----------------------------------------------------------------------------
Object::~Object()
{
}


//-----------------------------------------------------------------------------
void Object::autorelease()
{
    AutoReleasePool::instance()->add(this);
}


//-----------------------------------------------------------------------------
uint32 Object::retain()
{
    return ++this->refCount;
}


//-----------------------------------------------------------------------------
uint32 Object::release()
{
    if (--this->refCount == 0)
    {
        delete this;
        return 0;
    }
    else
    {
        return this->refCount;
    }
}


//-----------------------------------------------------------------------------
uint32 Object::getRefCount()
{
    return this->refCount;
}


//-----------------------------------------------------------------------------
uint32 Object::getId()
{
    return this->id;
}


//-----------------------------------------------------------------------------
void Object::bindMethod()
{
}


//-----------------------------------------------------------------------------
void Object::bindProperty()
{
    BIND_PROPERTY_READONLY(uint32, ref_count, getRefCount, { return 0; });
    BIND_PROPERTY_READONLY(uint32, obj_id, getId, { return 0; });
}


//-----------------------------------------------------------------------------
uint32 Object::s_id = 0;

}