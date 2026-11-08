class SysTick
{
public:
    SysTick()
    void Handler();
    uint32_t GetMilliseconds() const;
    static void InterruptHandler();

private:
    static SysTick* instance;
    volatile uint32_t milliseconds;
};

