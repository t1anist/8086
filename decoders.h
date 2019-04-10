#ifndef DECODERS_H
#define DECODERS_H
#include "hardwares.h"

class Decoders : public Hardwares
{
private:
    Q_OBJECT
    Voltage pins[DECODER_PIN_NUM];
    Counter<Decoders> c;
    void setOutputVoltage();

public:
    Decoders(QString decoderName=nullptr);
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    Voltage getPinVoltage(MicroCom::Pins pin);
    static int howMany(){return Counter<Decoders>::howMany();}
};

#endif // DECODERS_H
