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
    Voltage readVoltage(MicroCom::Pins pin);

    //set Pins voltage
    bool setVoltage(MicroCom::Pins pin, Voltage pinVol);

    //read Registers value
    unsigned short readInnerReg(MicroCom::Regs reg);
    Voltage readInnerReg(MicroCom::Regs reg, short pos);

    //set Registers value
    void setInnerReg(MicroCom::Regs reg, short value);
    void setInnerReg(MicroCom::Regs reg, short biValue, short pos);

    //True Form(原码) to Complement Form(补码)
    unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte);

    //Complement Form to True Form 默认长度为16位
    short toTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
};

#endif // CPUS_H
