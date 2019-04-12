#ifndef HARDWARES_H
#define HARDWARES_H

#include <QWidget>
#include <QTime>
#include <QDebug>
#include <QCoreApplication>
#include "datatype.h"

class Hardwares : public QWidget
{
    Q_OBJECT
private:
    QString hardwareName;
public:
    explicit Hardwares(QWidget *parent = nullptr);
    virtual void handlePinVolChanges(MicroCom::Pins pin, Voltage value)=0;
    virtual Voltage getPinVoltage(MicroCom::Pins pin)=0;
    void setHardwareName(QString hdName);
    QString getHardwareName();

    //True Form(原码) to Complement Form(补码)
    unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte);
    //Complement Form to True Form 默认长度为16位
    short toTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
    void toBinary(int denary, int binary[]);
    unsigned short toDenary(int binary[]);
    //非阻塞延时函数
    void delaymsec(int msec);

signals:
    void pinVolChanged(MicroCom::Pins pin);
};

#endif // HARDWARES_H
