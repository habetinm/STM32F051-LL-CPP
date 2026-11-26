#ifndef LED_HPP_INCLUDED
#define LED_HPP_INCLUDED

class Led {
public:
    Led();
    virtual void Toggle() = 0; // has to be virtual because of the calling in Led::Callback
    static void Callback(void* context);
};

class Led3 : public Led {
public:
    Led3();
    void Toggle() override;
};

class Led4 : public Led {
public:
    Led4();
    void Toggle() override;
};

#endif // LED_HPP_INCLUDED
