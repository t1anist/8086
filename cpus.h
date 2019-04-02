#ifndef CPUS_H
#define CPUS_H
#include "hardwares.h"
#include "datatype.h"


class CPUs : public Hardwares
{
public:
    CPUs();
private:
    Q_OBJECT
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
    //get the pointer to the pin
    Voltage* selectPin(MicroCom::Pins pin);
    //read the pin's voltage
    Voltage getPinVoltage(MicroCom::Pins pin);
    //set the pin's voltage
    bool setVoltage(MicroCom::Pins pin, Voltage pinVol);

    //get the pointer to the register
    unsigned short* selectReg(MicroCom::Regs reg);
    //get the Register's value
    unsigned short getRegValue(MicroCom::Regs reg);
    Voltage getRegValue(MicroCom::Regs reg, short pos);
    //set the Register's value
    void setRegValue(MicroCom::Regs reg, short value);
    void setRegValue(MicroCom::Regs reg, Voltage biValue, short pos);
    void setRegUnsignedValue(MicroCom::Regs reg, unsigned short value);


    void emitReset();//在每个类中添加一个触发器函数，用于发射信号。然后将所有的connect写入构造函数内！

signals:
    void pip();

public slots:
    //reset
    void resetCPU();
};

#endif // CPUS_H
