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
signals:

public slots:
};

#endif // HARDWARES_H
