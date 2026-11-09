#ifndef SYSTICKHANDLER_HPP
#define SYSTICKHANDLER_HPP

class SysTickHandler
{
public:
    SysTickHandler();
    void Handler();
    uint32_t GetMilliseconds() const;
    static void InterruptHandler();

private:
    static SysTickHandler* instance;
    volatile uint32_t milliseconds;
};

#endif // SYSTICKHANDLER_HPP
