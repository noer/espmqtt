#ifndef CTASK_H
#define CTASK_H

#define _TASK_MICRO_RES
#define _TASK_OO_CALLBACKS
#include <TaskSchedulerDeclarations.h>

class CTask : public Task {
private:
    std::function<void(void)> cb;

public:
    CTask(Scheduler* aScheduler, int aInterval, std::function<void(void)> callback)
       : Task(aInterval * TASK_MILLISECOND, TASK_FOREVER, aScheduler, false)
    {
        cb = callback;
    };

    CTask(Scheduler* aScheduler, int aInterval, std::function<void(void)> callback, bool enabled)
       : Task(aInterval * TASK_MILLISECOND, TASK_FOREVER, aScheduler, enabled)
    {
        cb = callback;
    };

    CTask(Scheduler* aScheduler, int aInterval, std::function<void(void)> callback, long aIterations, bool enabled)
       : Task(aInterval * TASK_MILLISECOND, aIterations, aScheduler, enabled)
    {
        cb = callback;
    };
    ~CTask() {};

    void enable() { Task::enable(); };
    void disable() { Task::disable(); };

    bool Callback() { cb(); return true; };
//    bool OnEnable();
//    void OnDisable();

};

#endif //CTASK_H