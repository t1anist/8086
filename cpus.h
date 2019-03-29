#ifndef CPUS_H
#define CPUS_H
#include "hardwares.h"
#include "datatype.h"


class CPUs : public Hardwares
{
public:
    CPUs();
private:
    short ax;
    short bx;
    short cx;
    short dx;
    short cs;
    short ds;
    short es;
    short ss;
    short bp;
    short sp;
    short si;
    short di;
    short ip;
    short flags;
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
    Voltage readVoltage(MicroCom::Pins pin);

    //set Pins voltage
    bool setVoltage(MicroCom::Pins pin, Voltage pinVol);

    //read Registers value
    short readInnerReg(MicroCom::Regs reg);
    short readInnerReg(MicroCom::Regs reg, short pos);

    //set Registers value
    void setInnerReg(MicroCom::Regs reg, short value);
    void setInnerReg(MicroCom::Regs reg, short biValue, short pos);

    //True Form(原码) to Complement Form(补码)
    unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte);

    //Complement Form to True Form 默认长度为16位
    short toTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
};

#endif // CPUS_H
