#ifndef HARDWARES_H
#define HARDWARES_H

#include <QWidget>
#include "datatype.h"

class Hardwares : public QWidget
{
    Q_OBJECT
private:
    Voltage VCC;
    Voltage gnd;
public:
    explicit Hardwares(QWidget *parent = nullptr);
    virtual bool setVoltage(MicroCom::Pins pin, Voltage pinVol)=0;
    void setValueByPos(unsigned short &value, short pos, MicroCom::Regs reg, Voltage biValue);

    //True Form(原码) to Complement Form(补码)
    unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte);
    //Complement Form to True Form 默认长度为16位
    short toTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
signals:

public slots:
};

#endif // HARDWARES_H
