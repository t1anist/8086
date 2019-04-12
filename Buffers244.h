#ifndef BUFFERS_H
#define BUFFERS_H
#include "hardwares.h"

class Buffers244 : public Hardwares
{
private:
    Q_OBJECT
    const int BF4_START = 80;
    Voltage pins[BUFFER_PIN_NUM];
    Counter<Buffers244> c;
    int status;

public:
    Buffers244(QString bufferName=nullptr);
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    void handlePinVolChanges(MicroCom::Pins pin, Voltage);
    Voltage getPinVoltage(MicroCom::Pins pin);
    //计数器
    static int howMany(){return Counter<Buffers244>::howMany();}
};

#endif // BUFFERS_H
