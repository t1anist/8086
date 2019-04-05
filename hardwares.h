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

    virtual Voltage* selectPin(MicroCom::Pins pin)=0;
    virtual void handleOuterVolChange(MicroCom::Pins pinT, Voltage senderVol)=0;

    bool setVoltage(MicroCom::Pins pin, Voltage pinVol);
    Voltage getPinVoltage(MicroCom::Pins pin);

    void setValueByPos(unsigned short &value, short pos, MicroCom::Regs reg, Voltage biValue);

    //True Form(原码) to Complement Form(补码)
    unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte);
    //Complement Form to True Form 默认长度为16位
    short toTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
    void toBinary(int denary, short binary[]);
    unsigned short toDenary(short binary[]);

signals:
    void pinVolChanged(MicroCom::Pins);

public slots:
};

#endif // HARDWARES_H
