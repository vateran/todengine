#pragma once
#include "todcore/simpleproperty.h"
namespace tod
{
  
template <typename PROPERTY_TYPE>
class EnumProperty : public SimpleProperty<PROPERTY_TYPE>
{
public:
    typedef std::vector<String> EnumList;

public:
    EnumProperty(const str_t* name):SimpleProperty<PROPERTY_TYPE>(name) { }

    virtual const EnumList& getEnumList(Object* object)=0;
};

}



