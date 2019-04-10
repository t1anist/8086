#ifndef BUFFERS_H
#define BUFFERS_H
#include "hardwares.h"

class Buffers244 : public Hardwares
{
private:
    Q_OBJECT
    Voltage pins[BUFFER_PIN_NUM];
    Counter<Buffers244> c;
    void setOutputVoltage(MicroCom::Pins);

public:
    Buffers244(QString bufferName=nullptr);
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    Voltage getPinVoltage(MicroCom::Pins pin);

    //计数器
    static int howMany(){return Counter<Buffers244>::howMany();}
};

#endif // BUFFERS_H
