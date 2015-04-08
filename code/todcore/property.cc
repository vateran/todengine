#include "todcore/property.h"
#include "todcore/typeid.h"
namespace tod
{

//-----------------------------------------------------------------------------
Property::Property(const str_t* name):
name(name)
{
}


//-----------------------------------------------------------------------------
const String& Property::getName() const
{
    return this->name;
}


//-----------------------------------------------------------------------------
bool Property::isEnumable()
{
    return false;
}


//-----------------------------------------------------------------------------
type_id Property::getType() const
{
    return TypeId<void>::id();
}

}
