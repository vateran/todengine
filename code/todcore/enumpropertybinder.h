#pragma once
#include <vector>
#include "todcore/enumproperty.h"
namespace tod
{ 

template <typename TYPE, typename PROPERTY_TYPE>
class TODEXPORT EnumPropertyBinder : public EnumProperty<PROPERTY_TYPE>
{
public:
    typedef void (TYPE::*Setter)(PROPERTY_TYPE);
    typedef PROPERTY_TYPE (TYPE::*Getter)();
    struct DefaultValueGetter { virtual PROPERTY_TYPE get() const=0; };
    typedef const EnumList& (TYPE::*EnumListGetter)();

public:
    EnumPropertyBinder(const str_t* name):EnumProperty<PROPERTY_TYPE>(name), setter(0), getter(0), defaultValueGetter(0)
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

    void setEnumListGetter(EnumListGetter getter)
    {
        this->enumListGetter = getter;
    }

    OVERRIDE const EnumList& getEnumList(Object* object)
    {
        TYPE* self = static_cast<TYPE*>(object);
        return (self->*enumListGetter)();
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

    OVERRIDE bool isEnumable()
    {
        return true;
    }

private:
    Setter setter;
    Getter getter;
    DefaultValueGetter* defaultValueGetter;
    EnumListGetter enumListGetter;
};

#define BIND_ENUM_PROPERTY(type, name, enum_list_getter, setter, getter, default_value_getter) \
    do { static EnumPropertyBinder<SelfType, type> s_##name##_property(# name);\
        do {\
        struct DefaultValueGetter : public EnumPropertyBinder<SelfType, type>::DefaultValueGetter { type get() const default_value_getter };\
        static DefaultValueGetter s_default_value_getter;\
        s_##name##_property.setDefaultValueGetter(&s_default_value_getter); } while (false);\
    s_##name##_property.bind(&SelfType::setter, &SelfType::getter);\
    s_##name##_property.setEnumListGetter(&SelfType::enum_list_getter);\
    SelfType::get_type()->addProperty(&s_##name##_property); } while (false)

}
