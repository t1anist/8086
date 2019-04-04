#ifndef CPUS_H
#define CPUS_H
#include "hardwares.h"
#include "datatype.h"
#include <QDebug>
#include <QTimer>

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

    int address;
    unsigned short data;


public:
    //get the pointer to the pin
    Voltage* selectPin(MicroCom::Pins pin);
    //read the pin's voltage
    Voltage getPinVoltage(MicroCom::Pins pin);
    //set the pin's voltage
    bool setVoltage(MicroCom::Pins pin, Voltage pinVol);
    void setAddrPinsVoltage(int addr);

    //get the pointer to the register
    unsigned short* selectReg(MicroCom::Regs reg);
    //get the Register's value
    unsigned short getRegValue(MicroCom::Regs reg);
    unsigned short getDataValue(MicroCom::RegsLen len = MicroCom::dbyte);
    Voltage getRegValue(MicroCom::Regs reg, short pos);
    //set the Register's value
    void setRegValue(MicroCom::Regs reg, short value);
    void setRegValue(MicroCom::Regs reg, Voltage biValue, short pos);
    void setRegUnsignedValue(MicroCom::Regs reg, unsigned short value);

    //读总线周期
    unsigned short readBusCycle(int phyAddr);
    //写总线周期
    void writeBusCycle(int phyAddr, unsigned short value);

    void emitReset();//在每个类中添加一个触发器函数，用于发射信号。然后将所有的connect写入构造函数内！

signals:
    void pip();

public slots:
    //reset
    void resetCPU();
    void T1();
    void T2();
    void T3();
    void T4();

protected:
    void timeEvent(QTimerEvent *e);

};

#endif // CPUS_H
