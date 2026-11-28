#include <cstdint>
#include <string.h>
#include "Scheduler.hpp"


Scheduler* Scheduler::instance = nullptr;

Scheduler::Scheduler() {
    memset((void*)&task_array[0], 0, sizeof(task_array));
}

void Scheduler::Schedule() {
    for (uint8_t i = 0; i < MAX_TASKS; i++) {
        if (!task_array[i].used) {
            task_array[i].task(task_array[i].context);
        }
    }
}

Scheduler& Scheduler::GetInstance()
{
    static Scheduler instance;
    return instance;
}

