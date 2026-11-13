class Led {
public:
    Led();
    virtual void Toggle() = 0;
    static void Callback(void* context);
};

class Led3 : public Led {
public:
    Led3();
    void Toggle();
};

class Led4 : public Led {
public:
    Led4();
    void Toggle();
};
