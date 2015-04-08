#pragma once
#include <list>
#include <mutex>
#include <thread>
#include "todcore/macro.h"
#include "todcore/singleton.h"
#include "todcore/object.h"
#include "todcore/method.h"

namespace tod
{ 

class TODEXPORT Task
{
public:

public:
    Object* object;
    Method* method;
    Params params;
};


class TODEXPORT Scheduler : public Singleton<Scheduler>
{
public:
    typedef std::lock_guard<std::mutex> LockGuard;

public:
    Scheduler()
    {
        this->startPump();
    }

    void addTask(Object* object, Method* method)
    {
        LockGuard lock(this->taskQueueMutex);

        Task* task = new Task();
        task->object = object;
        task->method = method;
        task->params = method->getParams();
        this->taskQueue.push_back(task);
    }

    void startPump()
    {
    }
    void stopPump()
    {
    }

private:
    void pump()
    {
        std::this_thread::sleep_for (std::chrono::milliseconds(0));
    }


private:
    typedef std::list<Task*> TaskQueue;

private:
    TaskQueue taskQueue;
    std::mutex taskQueueMutex;
    std::thread taskThread;
};

}
