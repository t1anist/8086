#ifndef BUFFERS245_H
#define BUFFERS245_H
#include "hardwares.h"


class Buffers245 : public Hardwares
{
private:
    Q_OBJECT
    Voltage pins[BUFFER_PIN_NUM];
    Counter<Buffers245> c;

public:
    Buffers245(QString bufferName=nullptr);
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    Voltage getPinVoltage(MicroCom::Pins pin);
    void setOutputVoltage();

    //计数器
    static int howMany(){return Counter<Buffers245>::howMany();}
};
#endif // BUFFERS245_H
