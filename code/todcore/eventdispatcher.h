#pragma once
#include <list>
#include <map>
#include <functional>
namespace tod
{

template <typename T>
class EventDispatcher : public T
{
public:
    typedef std::function<void(void*)> EventCallback;

public:
    void addEventListener(const char* event_name, void* listener, const EventCallback& e)
    {
        auto i = this->listeners.find(event_name);
        if (i == this->listeners.end())
        {
            auto j = this->listeners.insert(Listeners::value_type(event_name, EventCallbacks()));
            i = j.first;
        }
        i->second.insert(EventCallbacks::value_type(listener, e));
    }
    void removeEventListener(const char* event_name, void* listener)
    {
        auto i = this->listeners.find(event_name);
        if (i == this->listeners.end()) return;
        i->second.erase(listener);
        if (i->second.empty()) this->listeners.erase(event_name);
    }
    void dispatchEvent(const char* event_name, void* arg=0)
    {
        auto i = this->listeners.find(event_name);
        if (i == this->listeners.end()) return;
        EventCallbacks clone = i->second;
        for (auto j : clone)
        {
            j.second(arg);
        }
    }

private:
    typedef std::map<void*, EventCallback> EventCallbacks;
    typedef std::map<const char*, EventCallbacks> Listeners;
    Listeners listeners;

};

}



