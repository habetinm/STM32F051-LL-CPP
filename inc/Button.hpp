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
    uint8_t pressed;
};
