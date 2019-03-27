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
    Voltage readVoltage(MicroCom::Pins pin);
    bool setVoltage(MicroCom::Pins pin, Voltage pinVol);
    short readInnerReg(MicroCom::Regs inReg);
    short readInnerReg(MicroCom::Regs inReg, short pos);
    void setInnerReg(MicroCom::Regs inReg, short value);
    void setInnerReg(MicroCom::Regs inReg, short biValue, short pos);

};

#endif // CPUS_H
