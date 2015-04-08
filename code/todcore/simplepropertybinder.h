#pragma once
#include "todcore/simpleproperty.h"
namespace tod
{ 

template <typename TYPE, typename PROPERTY_TYPE>
class TODEXPORT SimplePropertyBinder : public SimpleProperty<PROPERTY_TYPE>
{
public:
    typedef void (TYPE::*Setter)(PROPERTY_TYPE);
    typedef PROPERTY_TYPE (TYPE::*Getter)();
    struct DefaultValueGetter { virtual PROPERTY_TYPE get() const=0; };

public:
    SimplePropertyBinder(const str_t* name):SimpleProperty<PROPERTY_TYPE>(name), setter(0), getter(0), defaultValueGetter(0)
    {
    }
    
    OVERRIDE void set(Object* object, PROPERTY_TYPE value)
    {
        TYPE* self = static_cast<TYPE*>(object);
        (self->*setter)(value);
    }

    OVERRIDE PROPERTY_TYPE get(Object* object) const
    {
        TYPE* self = static_cast<TYPE*>(object);
        return (self->*getter)();
    }

    OVERRIDE PROPERTY_TYPE getDefaultValue() const
    {
        return this->defaultValueGetter->get();
    }

    void setDefaultValueGetter(DefaultValueGetter* getter)
    {
        this->defaultValueGetter = getter;
    }
    
    void bind(Setter setter, Getter getter)
    {
        this->setter = setter;
        this->getter = getter;
    }

    OVERRIDE void fromString(Object* self, const str_t* value)
    {
        if (nullptr == this->setter) return;
        typedef StringConv<PROPERTY_TYPE> SC;
        this->set(static_cast<TYPE*>(self), SC::fromString(value));
    }

    OVERRIDE void toString(Object* self, OUT String& s)
    {
        if (nullptr == this->getter) return;
        typedef StringConv<PROPERTY_TYPE> SC;
        SC::toString(this->get(static_cast<TYPE*>(self)), s);
    }

    OVERRIDE bool isReadOnly() const
    {
        return (nullptr == this->setter);
    }

protected:    
    Setter setter;
    Getter getter;
    DefaultValueGetter* defaultValueGetter;

};
    
#define _BEGIN_BIND_PROPERTY(type, name) do { static SimplePropertyBinder<SelfType, type> s_##name##_property(# name);
#define _END_BIND_PROPERTY(type, name) SelfType::get_type()->addProperty(&s_##name##_property); } while (false)
#define _SET_DEFAULT_VALUE_GETTER(type, name, default_value_getter) do {\
    struct DefaultValueGetter : public SimplePropertyBinder<SelfType, type>::DefaultValueGetter { type get() const default_value_getter };\
    static DefaultValueGetter s_default_value_getter;\
    s_##name##_property.setDefaultValueGetter(&s_default_value_getter); } while (false)

#define BIND_PROPERTY(type, name, setter, getter, default_value_getter) \
    _BEGIN_BIND_PROPERTY(type, name)\
    _SET_DEFAULT_VALUE_GETTER(type, name, default_value_getter);\
    s_##name##_property.bind(&SelfType::setter, &SelfType::getter);\
    _END_BIND_PROPERTY(type, name)

#define BIND_PROPERTY_READONLY(type, name, getter, default_value_getter) \
    _BEGIN_BIND_PROPERTY(type, name)\
    _SET_DEFAULT_VALUE_GETTER(type, name, default_value_getter);\
    s_##name##_property.bind(0, &SelfType::getter);\
    _END_BIND_PROPERTY(type, name)

}
