#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "SysTickHandler.hpp"

class Button {
    typedef void (*button_cb)(void*, uint8_t state);

public:
    Button(SysTickHandler* systck);
    void SetCB(void* obj, button_cb cb);
    virtual void Loop() = 0;
    virtual uint8_t IsPressed() = 0;

protected:
    button_cb callback;
    void* context;
    SysTickHandler* systick;
};

class UserButton : public Button {
public:
    UserButton(SysTickHandler* systck);
    void Loop() override;
    uint8_t IsPressed();

private:
    uint8_t last_state;
    uint8_t button_state;
    uint8_t state;
    uint8_t current_state;
    uint8_t pressed;
    uint32_t last_change_time;
    uint32_t milliseconds;
};

#endif // BUTTON_HPP_INCLUDED
