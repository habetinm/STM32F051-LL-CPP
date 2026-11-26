#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "SysTickHandler.hpp"

class Button {
    typedef void (*button_cb)(void*, uint8_t state);

public:
    Button();
    void SetCB(void* obj, button_cb cb);
    virtual void Loop();
    uint8_t IsPressed();

protected:
    void* context;
    button_cb callback;
    uint8_t pressed;
};

class UserButton : public Button {
public:
    UserButton();
    void Loop() override;

private:
    uint8_t last_state;
    uint8_t button_state;
    uint8_t state;
    uint8_t current_state;
    uint32_t last_change_time;
    uint32_t milliseconds;
};

#endif // BUTTON_HPP_INCLUDED
