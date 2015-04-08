#include "todcore/module.h"
#include "todcore/object.h"

namespace tod
{

//-----------------------------------------------------------------------------
Module::Module(const str_t* name):
    name(name)
{
}


//-----------------------------------------------------------------------------
Type* Module::findType(const str_t* name)
{
    auto i = this->types.find(name);
    if (this->types.end()==i) return nullptr;
    return i->second;
}


//-----------------------------------------------------------------------------
Object* Module::createInstance(const str_t* name)
{
    Type* type = this->findType(name);
    if (nullptr==type) { TOD_TRACE(); return nullptr; }

    Object* new_obj = type->create();
    if (nullptr==new_obj) { TOD_TRACE(); return nullptr; }

    return new_obj;
}


//-----------------------------------------------------------------------------
const String& Module::getName() const
{
    return this->name;
}


//-----------------------------------------------------------------------------
Module::Types& Module::getTypes()
{
    return this->types;
}


//-----------------------------------------------------------------------------
uint32 Module::getNumTypes()
{
    return this->types.size();
}

}
