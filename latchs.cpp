#include "latchs.h"

Latchs::Latchs(QString latchName)
{
    if(latchName == nullptr){
        latchName = "74LS373_"+QString::number(c.howMany());
    }
    setHardwareName(latchName);
    //初始化为高阻态
    for(int i=0;i<LATCH_PIN_NUM;i++){
        pins[i]=inf;
    }
}

void Latchs::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-40]=value;
    if(pin==MicroCom::LA_G || pin==MicroCom::LA_oe){
        if(pins[MicroCom::LA_G-40]==high && pins[MicroCom::LA_oe-40]==low){
            setOutputVoltage();
        }
    }
    emit pinVolChanged(pin);
}

Voltage Latchs::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-40];
}

void Latchs::setOutputVoltage(){
    for(int i=0;i<8;i++){
        pins[i+8]=pins[i];
        emit pinVolChanged(static_cast<MicroCom::Pins>(i+48));
    }
    qDebug()<<"=========Latch works========";
    qDebug()<<"DO0="<<getPinVoltage(MicroCom::LA_DO0);
    qDebug()<<"DO1="<<getPinVoltage(MicroCom::LA_DO1);
    qDebug()<<"DO2="<<getPinVoltage(MicroCom::LA_DO2);
    qDebug()<<"DO3="<<getPinVoltage(MicroCom::LA_DO3);
    qDebug()<<"DO4="<<getPinVoltage(MicroCom::LA_DO4);
    qDebug()<<"DO5="<<getPinVoltage(MicroCom::LA_DO5);
    qDebug()<<"DO6="<<getPinVoltage(MicroCom::LA_DO6);
    qDebug()<<"DO7="<<getPinVoltage(MicroCom::LA_DO7);
    qDebug()<<"=========Latch ends=========";
}
