#include "SysTickHandler.hpp"

class Button {
    typedef void (*button_cb)(void*, uint8_t state);

public:
    Button();
    void SetCB(void* obj, button_cb cb);
    void Loop();
    uint8_t IsPressed();

public:
    button_cb callback;

private:
    uint8_t pressed;
    void* context;
    SysTickHandler systick;
};
