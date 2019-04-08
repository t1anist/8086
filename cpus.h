#ifndef CPUS_H
#define CPUS_H
#include "hardwares.h"
#include "datatype.h"
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QCoreApplication>

class CPUs : public Hardwares
{
public:
    CPUs();
    CPUs(QString cpuName);
private:
    Q_OBJECT
    unsigned short innerReg[14];
    Voltage pins[34];
    int clk_cpu;
    int address;
    unsigned short data;
    ~CPUs();
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
    //非阻塞延时函数
    void delaymsec(int msec);

signals:
    //仿真时钟信号
    void clockSignal(MicroCom::ClockType);

public slots:
    //对本原件引脚电平变化做出反应的函数
    void handleInnerVolChange(MicroCom::Pins pin);
    void resetCPU();

protected:
    void timerEvent(QTimerEvent *e);
};

#endif // CPUS_H
