#ifndef LED_HPP_INCLUDED
#define LED_HPP_INCLUDED

class Led {
public:
    Led(Timer* timer);
    virtual void Toggle() = 0; // has to be virtual because of the calling in Led::Callback
    virtual void ChangePeriod() = 0;
    static void Callback(void* context);

private:
    Timer* timer;
};

class Led3 : public Led {
public:
    Led3(Timer* timer);
    void Toggle() override;
    void ChangePeriod() override;
};

class Led4 : public Led {
public:
    Led4(Timer* timer);
    void Toggle() override;
    void ChangePeriod() override;
};

#endif // LED_HPP_INCLUDED
