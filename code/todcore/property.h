#pragma once
#include <stdio.h>
#include <typeinfo>
#include "todcore/basetype.h"
#include "todcore/macro.h"
#include "todcore/string.h"
#include "todcore/stringconv.h"
namespace tod
{ 

class Object;
class TODEXPORT Property
{
public:
    Property(const str_t* name);
    const String& getName() const;

    virtual void fromString(Object* self, const str_t* value)=0;
    virtual void toString(Object* self, OUT String& s)=0;
    virtual bool isReadOnly() const=0;
    virtual bool isEqualDefaultValue(Object* self) const=0;
    virtual bool isEnumable();
    virtual type_id getType() const;

private:
    String name;
};

}
