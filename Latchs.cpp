#include "latchs.h"

Latchs::Latchs(QString latchName)
{
    status=0;
    if(latchName == nullptr){
        latchName = "74LS373_"+QString::number(c.howMany());
    }
    setHardwareName(latchName);
    //初始化为高阻态
    for(int i=0;i<LATCH_PIN_NUM;i++){
        pins[i]=inf;
    }
    pins[MicroCom::LA_oe-LA_START]=low;
}

void Latchs::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-LA_START]=value;
    emit pinVolChanged(pin);
}

void Latchs::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin-LA_START]=value;
    if(pin==MicroCom::LA_G || pin==MicroCom::LA_oe){
        if(Latchs::getPinVoltage(MicroCom::LA_G)==high && Latchs::getPinVoltage(MicroCom::LA_oe)==low){
            status=1;
            //将DI(40~47,pins[0~7])端口数据传送到DO(48~55,pins[8~15])端口，并锁存之
            for(int i=0;i<8;i++){
                setPinVoltage(static_cast<MicroCom::Pins>(i+8+LA_START),pins[i]);
            }
            qDebug()<<"========="<<getHardwareName()<<"WORK=========";
            qDebug()<<"DO0="<<Latchs::getPinVoltage(MicroCom::LA_DO0);
            qDebug()<<"DO1="<<Latchs::getPinVoltage(MicroCom::LA_DO1);
            qDebug()<<"DO2="<<Latchs::getPinVoltage(MicroCom::LA_DO2);
            qDebug()<<"DO3="<<Latchs::getPinVoltage(MicroCom::LA_DO3);
            qDebug()<<"DO4="<<Latchs::getPinVoltage(MicroCom::LA_DO4);
            qDebug()<<"DO5="<<Latchs::getPinVoltage(MicroCom::LA_DO5);
            qDebug()<<"DO6="<<Latchs::getPinVoltage(MicroCom::LA_DO6);
            qDebug()<<"DO7="<<Latchs::getPinVoltage(MicroCom::LA_DO7);
            qDebug()<<"========="<<getHardwareName()<<"END=========";
        }
        else if(Latchs::getPinVoltage(MicroCom::LA_oe)==high){
            if(status == 0){
                return;
            }
            status=0;
            for(int i=0;i<8;i++){
                setPinVoltage(static_cast<MicroCom::Pins>(i+8+LA_START),inf);
            }
            qDebug()<<"========"<<getHardwareName()<<"使能端无效========";
            qDebug()<<"===========所有引脚已被置为高阻============";
        }
    }
}

//获取引脚电平
Voltage Latchs::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-LA_START];
}
