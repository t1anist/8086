#include "buffers244.h"

Buffers244::Buffers244(QString bufferName){
    if(bufferName == nullptr){
        bufferName = "74LS244_" + QString::number(c.howMany());
    }
    setHardwareName(bufferName);
    for(int i=0;i<BUFFER_PIN_NUM;i++){
        pins[i]=inf;
    }
}

void Buffers244::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-80]=value;
    if(pin==MicroCom::BF4_Ga && pins[MicroCom::BF4_Ga-80]==low){
        setOutputVoltage(pin);
    }
    if(pin==MicroCom::BF4_Gb && pins[MicroCom::BF4_Gb-80]==low){
        setOutputVoltage(pin);
    }
    emit pinVolChanged(pin);
}

Voltage Buffers244::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-80];
}

void Buffers244::setOutputVoltage(MicroCom::Pins pin){
    int pos = 0;
    if(pin==MicroCom::BF4_Ga){
        pos=4;
    }
    else{
        pos=8;
    }
    for(int i=0;i<4;i++){
        pins[i+pos]=pins[i];
        emit pinVolChanged(static_cast<MicroCom::Pins>(i+pos+80));
    }
    if(pos==4){
        qDebug()<<"========74LS244_a works========";
        qDebug()<<"1A1="<<getPinVoltage(MicroCom::BF4_1O1);
        qDebug()<<"1A2="<<getPinVoltage(MicroCom::BF4_1O2);
        qDebug()<<"1A3="<<getPinVoltage(MicroCom::BF4_1O3);
        qDebug()<<"1A4="<<getPinVoltage(MicroCom::BF4_1O4);
    }
    else{
        qDebug()<<"========74LS244_a works========";
        qDebug()<<"2A1="<<getPinVoltage(MicroCom::BF4_2O1);
        qDebug()<<"2A2="<<getPinVoltage(MicroCom::BF4_2O2);
        qDebug()<<"2A3="<<getPinVoltage(MicroCom::BF4_2O3);
        qDebug()<<"2A4="<<getPinVoltage(MicroCom::BF4_2O4);
    }
    //有没有必要还原输出引脚电平呢？
    /*
    for(int i=0;i<4;i++){
        pins[i+pos]=pins[i];
        emit pinVolChanged(static_cast<MicroCom::Pins>(i+pos+80));
    }*/
}
