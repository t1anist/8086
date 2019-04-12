#ifndef BUFFERS245_H
#define BUFFERS245_H
#include "Hardwares.h"

class Buffers245 : public Hardwares
{
private:
    Q_OBJECT
    const int BF5_START = 100;
    Voltage pins[BUFFER_PIN_NUM];
    Counter<Buffers245> c;
    int status;

public:
    Buffers245(QString bufferName=nullptr);
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    void handlePinVolChanges(MicroCom::Pins pin, Voltage value);
    Voltage getPinVoltage(MicroCom::Pins pin);
    //计数器
    static int howMany(){return Counter<Buffers245>::howMany();}
};
#endif // BUFFERS245_H
