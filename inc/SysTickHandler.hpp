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

