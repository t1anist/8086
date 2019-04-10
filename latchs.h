#ifndef LATCHS_H
#define LATCHS_H
#include "hardwares.h"

class Latchs : public Hardwares
{
private:
    Q_OBJECT
    Voltage pins[LATCH_PIN_NUM];
    Counter<Latchs> c;
    void setOutputVoltage();

public:
    Latchs(QString latchName=nullptr);
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    Voltage getPinVoltage(MicroCom::Pins pin);    
    static int howMany(){return Counter<Latchs>::howMany();}
};

#endif // LATCHS_H
