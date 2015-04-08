#pragma once
#include "todcore/macro.h"
#include "todcore/basetype.h"
namespace tod
{ 

template <typename T>
class TODEXPORT Ref
{
public:
    typedef Ref<T> RefType;

public:
    Ref():obj(nullptr)
    {
    }
    Ref(T* o):obj(o)
    {
        this->obj->retain();
    }
    Ref(const RefType& o):obj(o.obj)
    {
        this->obj->retain();
    }
    Ref(RefType&& o):obj(nullptr)
    {
        this->obj = o.obj;
        o.obj = nullptr;
    }
    ~Ref()
    {
        SAFE_RELEASE(this->obj);
    }

    bool valid()
    {
        return (this->obj != nullptr);
    }

    bool invalid()
    {
        return (this->obj == nullptr);
    }

    uint32 release()
    {
        if (this->obj == nullptr) return 0;
        uint32 r = this->obj->release();
        this->obj = nullptr;
        return r;
    }

    T* get()
    {
        return dynamic_cast<T*>(this->obj);
    }
    T* get() const
    {
        return dynamic_cast<T*>(this->obj);
    }
    operator T ()
    {
        return dynamic_cast<T*>(this->obj);
    }
    operator T () const
    {
        return dynamic_cast<T*>(this->obj);
    }

    operator T* ()
    {
        return this->obj;
    }

    T* operator -> ()
    {
        return this->obj;
    }

    const T* operator -> () const
    {
        return this->obj;
    }

    T* operator = (T* o)
    {
        SAFE_RELEASE(this->obj);
        this->obj = o;
        this->obj->retain();
        return this->obj;
    }
        
    bool operator == (T* r) const
    {
        return this->obj == r;
    }

    bool operator == (const T* r) const
    {
        return this->obj == r;
    }

    bool operator == (RefType& r)
    {
        return this->obj == r.obj;
    }

    bool operator == (const RefType& r) const
    {
        return this->obj == r.obj;
    }

    bool operator != (T* r) const
    {
        return this->obj != r;
    }

    bool operator != (const RefType& r) const
    {
        return this->obj != r.obj;
    }

    bool operator < (const RefType& r) const
    {
        return this->obj < r.obj;
    }

private:
    T* obj;
};

}

