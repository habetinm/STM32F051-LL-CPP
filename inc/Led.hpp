class Led {
public:
    Led(Timer* timer);
    virtual void Toggle() {};
    virtual void ChangePeriod() {};
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
