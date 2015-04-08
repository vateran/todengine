#pragma once
#include "todcore/property.h"
#include "todcore/typeid.h"
namespace tod
{
  
template <typename PROPERTY_TYPE>
class SimpleProperty : public Property
{
public:
    SimpleProperty(const str_t* name):Property(name) { this->typeId = TypeId<PROPERTY_TYPE>::id(); }
    
    virtual void set(Object* object, PROPERTY_TYPE value)=0;
    virtual PROPERTY_TYPE get(Object* object) const=0;
    virtual PROPERTY_TYPE getDefaultValue() const=0;

    OVERRIDE type_id getType() const
    {
        return this->typeId;
    }

    OVERRIDE bool isEqualDefaultValue(Object* self) const
    {
        return SimpleProperty<PROPERTY_TYPE>::isEqual(this->getDefaultValue(), this->get(self));
        return true;
    }

private:
    static bool isEqual(PROPERTY_TYPE l, PROPERTY_TYPE r) { return l == r; }

protected:
    type_id typeId;
};

template <>
bool SimpleProperty<const char*>::isEqual(const char* l, const char* r) { return TOD_STRCMP(l, r)==0; }

}



