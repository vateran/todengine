#pragma once
#include <map>
#include "todcore/macro.h"
#include "todcore/string.h"
#include "todcore/type.h"
namespace tod
{ 

class TODEXPORT Module
{
public:
    typedef std::map<String, Type*> Types;

public:
    Module(const str_t* name);
    virtual~Module() {}

    template <typename T>
    bool addType();
    Type* findType(const str_t* name);
    Object* createInstance(const str_t* name);
        
    const String& getName() const;

    Types& getTypes();
    uint32 getNumTypes();

private:
    String name;
    Types types;

};

template <typename T>
bool Module::addType()
{
    bool ret = false;
    Type* type = T::get_type();

    ret = this->findType(type->getName().u_str())==nullptr;
    if (!ret) { TOD_TRACE(); return false; }
    
    this->types.insert(Types::value_type(type->getName(), type));
    
    type->bindMethod();
    type->bindProperty();

    return true;
}

#define BEGIN_MODULE(module_name) do { tod::Module s_ ## module_name ## module(S(#module_name));
#define END_MODULE(module_name) tod::Kernel::instance()->addModule(&s_ ## module_name ## module); } while (false)
#define ADD_TYPE(module_name, type_name) do { s_ ## module_name ## module.addType<type_name>(); } while (false)

}
