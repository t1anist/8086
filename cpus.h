#ifndef CPUS_H
#define CPUS_H
#include "hardwares.h"
#include "datatype.h"
#include <QDebug>
#include <QTimer>

class CPUs : public Hardwares
{
public:
    CPUs(QString cpuName = nullptr);
private:
    Q_OBJECT
    unsigned short innerReg[CPU_REG_NUM];
    Voltage pins[CPU_PIN_NUM];
    int clk_cpu;
    int address;
    unsigned short data;
    Counter<CPUs> c;
public:
    //set the pin's voltage
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    //get the pin's voltage
    Voltage getPinVoltage(MicroCom::Pins pin);
    //set the ADDRESS BUS by addr
    void setAddrPinsVoltage(int addr);

    //get the Register's value
    unsigned short getRegValue(MicroCom::Regs reg);
    //get the Register's value by pos
    Voltage getRegValue(MicroCom::Regs reg, short pos);
    //get the DATA BUS value
    unsigned short getDataValue(MicroCom::RegsLen len = MicroCom::dbyte);

    //set the Register's value
    void setRegValue(MicroCom::Regs reg, short value);
    void setRegUnsignedValue(MicroCom::Regs reg, unsigned short value);
    //set the Register's value by pos
    void setRegValue(MicroCom::Regs reg, Voltage biValue, short pos);

    //read bus cycle
    unsigned short readBusCycle(int phyAddr);
    //write bus cycle
    void writeBusCycle(int phyAddr, unsigned short value);

    //判断是否为奇数
    bool isOdd(int i);
    void resetCPU();
    static int howMany(){return Counter<CPUs>::howMany();}

signals:
    void resetSignal();
};

#endif // CPUS_H
