#ifndef TIMER_HPP_INCLUDED
#define TIMER_HPP_INCLUDED

#include "SysTickHandler.hpp"

#define TIMER_0     0
#define TIMER_1     1
#define TIMER_2     2
#define TIMER_3     3
#define TIMER_4     4
#define TIMER_5     5
#define TIMER_6     6
#define TIMER_7     7
#define TIMER_8     8
#define TIMER_9     9
#define MAX_TIMERS 10

class Timers; // forward declaration

class Timer {
    friend class Timers; // timers member has to be accessible from Timers class

    typedef void (*timer_cb)(void*);

public:
    Timer();
    Timer(Timers* timers); 
    void Init();
    void Set(uint32_t interval_ms, void* obj, timer_cb cb);
    void Start();
    void Pause();
    void Resume();
    void Loop();
    //void SetCallback(void (*func)());
    uint8_t Started();
    uint8_t Paused();

public:
    timer_cb callback;

private:
    Timers* timers;
    void* context;
    uint8_t running;
    uint8_t used;
    uint32_t interval;
    uint32_t time;
};

class Timers {
public:
    static Timers& GetInstance();
    //Timers(SysTickHandler* systck);
    //~Timers();
    Timer* Get();
    void Loop();

private:
    Timers();
    Timers(const SysTickHandler&);
    Timers& operator=(const SysTickHandler&) = delete;

public:
    const SysTickHandler* systick;

private:
    static Timers* instance;
    Timer timer_array[MAX_TIMERS];
};

#endif // TIMER_HPP_INCLUDED
