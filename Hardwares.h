#ifndef HARDWARES_H
#define HARDWARES_H

#include <QWidget>
#include <QTime>
#include <QDebug>
#include <QCoreApplication>
#include "DataType.h"

class Hardwares : public QWidget
{
    Q_OBJECT
private:
    QString hardwareName;
public:
    explicit Hardwares(QWidget *parent = nullptr);
    virtual void handlePinVolChanges(MicroCom::Pins pin, Voltage value)=0;
    virtual Voltage getPinVoltage(MicroCom::Pins pin)=0;
    //set hardware's name
    void setHardwareName(QString hdName);
    //get hardware's name
    QString getHardwareName();

    //True Form to Complement Form
    unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte);
    //Complement Form to True Form
    short toTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
    //非阻塞延时函数
    void delaymsec(int msec);

signals:
    void pinVolChanged(MicroCom::Pins pin);
};

#endif // HARDWARES_H
