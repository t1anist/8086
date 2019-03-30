#ifndef CPUS_H
#define CPUS_H
#include "hardwares.h"
#include "datatype.h"


class CPUs : public Hardwares
{
public:
    CPUs();
private:
    unsigned short ax;
    unsigned short bx;
    unsigned short cx;
    unsigned short dx;
    unsigned short cs;
    unsigned short ds;
    unsigned short es;
    unsigned short ss;
    unsigned short bp;
    unsigned short sp;
    unsigned short si;
    unsigned short di;
    unsigned short ip;
    unsigned short flags;
    Voltage AD[16];
    Voltage AS[4];
    Voltage Mio;
    Voltage wr;
    Voltage rd;
    Voltage den;
    Voltage bhe;
    Voltage DTr;
    Voltage ALE;
    Voltage READY;
    Voltage RESET;
    Voltage NMI;
    Voltage inta;
    Voltage INTR;
    Voltage test;
    Voltage CLK;

public:
    //read Pins voltage
    Voltage getPinVoltage(MicroCom::Pins pin);

    //set Pins voltage
    bool setVoltage(MicroCom::Pins pin, Voltage pinVol);

    //get the Register's value
    unsigned short getRegValue(MicroCom::Regs reg);

    //get the Register's bit-value in a particular pos
    Voltage getRegValue(MicroCom::Regs reg, short pos);

    //set Register's value
    void setRegValue(MicroCom::Regs reg, short value);
    void setRegValue(MicroCom::Regs reg, Voltage biValue, short pos);

    //True Form(原码) to Complement Form(补码)
    unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte);

    //Complement Form to True Form 默认长度为16位
    unsigned short toUnsignedTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
    short toSignedTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
};

#endif // CPUS_H
