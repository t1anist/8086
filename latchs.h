#ifndef LATCHS_H
#define LATCHS_H
#include "hardwares.h"

class Latchs : public Hardwares
{
private:
    Q_OBJECT
    const int LA_START = 40;
    Voltage pins[LATCH_PIN_NUM];
    Counter<Latchs> c;

public:
    Latchs(QString latchName=nullptr);
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    Voltage getPinVoltage(MicroCom::Pins pin);
    void handlePinVolChanges(MicroCom::Pins pin, Voltage value);
    static int howMany(){return Counter<Latchs>::howMany();}
};

#endif // LATCHS_H
