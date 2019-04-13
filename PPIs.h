#ifndef PPI8255A_H
#define PPI8255A_H
#include "Hardwares.h"

class PPIs : public Hardwares
{
private:
    Q_OBJECT
    const int PP_START = 120;
    Voltage pins[PPI_PIN_NUM];
    unsigned short controlReg;
    Counter<PPIs> c;
    int status;

public:
    PPIs(QString ppiName=nullptr);
    void setPinVoltage(MicroCom::Pins pin, Voltage value);
    void handlePinVolChanges(MicroCom::Pins pin, Voltage value);
    Voltage getPinVoltage(MicroCom::Pins pin);

    //set the Register's value
    void setControlRegValue(unsigned short value);
    //set the Register's value by pos
    void setControlRegValue(Voltage biValue, int pos);

    unsigned short getControlRegValue();
    int getControlRegValue(int pos);
    unsigned short getDataValue();

    void setPortPinVoltage(bool isRead, int offset, int len=8);

    void handleIoMode(bool isRead, int port);
    MicroCom::PPIWorkWay getWorkWay();

    //计数器
    static int howMany(){return Counter<PPIs>::howMany();}
};

#endif // PPI8255A_H


/**
 * @brief The PPIs(Programmable Perpherial Interface) class
 * @author csy
 * @date 2019/4/11
 */

//A口作为输入/输入端口时均具备锁存功能
//B口作为输入/输入端口时均具备锁存功能
//C口仅具备输出锁存功能，输入只保持缓冲器功能

//对于方式0而言，只具备输出锁存功能，不具备输入锁存功能
