#include "todcore/type.h"
#include "todcore/method.h"
#include "todcore/property.h"
namespace tod
{

//-----------------------------------------------------------------------------
Type::Type():
base(0),
is_abstract(false)
{
}


//-----------------------------------------------------------------------------
Type::~Type()
{
}


//-----------------------------------------------------------------------------
bool Type::addMethod(Method* method)
{
    bool ret = false;

    ret = this->findMethod(method->getName().u_str())==nullptr;
    if (!ret) { TOD_TRACE(); return false; }

    this->methods.insert(Methods::value_type(method->getName(), method));
    
    return true;
}


//-----------------------------------------------------------------------------
Method* Type::findMethod(const str_t* name)
{
    const Type* type = this;
    while (type)
    {
        auto find_iter =  type->methods.find(name);
        if (type->methods.end() == find_iter)
        {
            type = type->base;
            continue;
        }
        return find_iter->second;
    }
    return nullptr;
}


//-----------------------------------------------------------------------------
bool Type::addProperty(Property* property)
{
    bool ret = false;

    ret = this->findProperty(property->getName().u_str())==nullptr;
    if (!ret) { TOD_TRACE(); return false; }

    this->properties.insert(Properties::value_type(property->getName(), property));

    return true;
}


//-----------------------------------------------------------------------------
Property* Type::findProperty(const str_t* name)
{
    const Type* type = this;
    while (type)
    {
        auto i = type->properties.find(name);
        if (type->properties.end() == i)
        {
            type = type->base;
            continue;
        }
        else
        {
            return i->second;
        }
    }
    return 0;
}


//-----------------------------------------------------------------------------
Type::Properties& Type::getProperties()
{
    return this->properties;
}


//-----------------------------------------------------------------------------
void Type::setAbstract(bool value)
{
    this->is_abstract = value;
}


//-----------------------------------------------------------------------------
bool Type::isAbstract()
{
    return this->is_abstract;
}


//-----------------------------------------------------------------------------
Type* Type::getBaseType()
{
    return this->base;
}


//-----------------------------------------------------------------------------
Type::Types Type::getDerivedTypes()
{
    Types result;
    Type* cur = this;
    while (cur)
    {
        result.insert(Types::value_type(cur->getName(), cur));
        cur = cur->base;
    }
    return result;
}


//-----------------------------------------------------------------------------
const String& Type::getName()
{
    return this->name;
}


//-----------------------------------------------------------------------------
void Type::set_base(Type* base)
{
    this->base = base;
}


//-----------------------------------------------------------------------------
void Type::set_type_name(const char* name)
{
    this->name.assign(name);
    size_t f = this->name.rfind(S(":"));
    if (f!=-1) this->name = this->name.substr(f+1, -1);
    f = this->name.rfind(S(" "));
    if (f!=-1) this->name = this->name.substr(f+1, -1);
}

}
