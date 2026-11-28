#ifndef SCHEDULER_HPP_INCLUDED
#define SCHEDULER_HPP_INCLUDED

#include "stm32f0xx.h"


class Scheduler {
private:
    static constexpr uint8_t MAX_TASKS = 10;
    typedef void (*Task)(void*);
    struct TaskStruct
    {
        Task task;
        void* context;
        uint8_t priority;
        uint8_t used;
    };

public:
    static Scheduler& GetInstance();
    void Schedule();

    template<typename T, void (T::*Method)()>
    static void Callback(void* context)
    {
        T* object = static_cast<T*>(context);
        (object->*Method)();
    }

    template<typename T, void (T::*Method)()> void RegisterTask(T* object, uint8_t pri)
    {
        for (uint8_t i = 0; i < MAX_TASKS; i++)
        {
            if (!task_array[i].used)
            {
                task_array[i].context = object;
                task_array[i].task = &Callback<T, Method>;
                task_array[i].priority = pri;
                task_array[i].used = 1;
                return;
            }
        }
    }

private:
    Scheduler();
    Scheduler(const Scheduler&) = delete;
    Scheduler& operator=(const Scheduler&) = delete;



private:
    static Scheduler* instance;    
    TaskStruct task_array[MAX_TASKS];
};

#endif // SCHEDULER_HPP_INCLUDED