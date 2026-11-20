#ifndef SYSTICKHANDLER_HPP
#define SYSTICKHANDLER_HPP

class SysTickHandler {
public:
    //SysTickHandler();
    static SysTickHandler& GetInstance();
    void Handler();
    uint32_t GetMilliseconds() const;
    static void InterruptHandler();

private:
    SysTickHandler();
    SysTickHandler(const SysTickHandler&) = delete;
    SysTickHandler& operator=(const SysTickHandler&) = delete;

private:
    static SysTickHandler* instance;
    volatile uint32_t milliseconds;
};

#endif // SYSTICKHANDLER_HPP

