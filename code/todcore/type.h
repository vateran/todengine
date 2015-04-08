#pragma once
#include <bitset>
#include <map>
#include <typeinfo>
#include "todcore/basetype.h"
#include "todcore/macro.h"
#include "todcore/string.h"
namespace tod
{     

class Object;
class Method;
class Property;
class TODEXPORT Type
{
public:
    typedef std::map<String, Method*> Methods;
    typedef std::map<String, Property*> Properties;
    typedef std::map<String, Type*> Types;

public:
    Type();
    virtual~Type();

    virtual Object* create()=0;
    
    virtual void bindMethod()=0;
    bool addMethod(Method* method);
    Method* findMethod(const str_t* name);

    bool hasProperty() const;
    virtual void bindProperty()=0;
    bool addProperty(Property* property);
    Property* findProperty(const str_t* name);
    Properties& getProperties();

    void setAbstract(bool value);
    bool isAbstract();
    Type* getBaseType();
    Types getDerivedTypes();
    const String& getName();

protected:
    void set_base(Type* base);
    void set_type_name(const char* name);
    
private:
    Type* base;
    String name;
    Methods methods;
    Properties properties;
    bool is_abstract;
};

}
