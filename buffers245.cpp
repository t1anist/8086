#include "buffers245.h"

Buffers245::Buffers245(QString bufferName){
    if(bufferName == nullptr){
        bufferName = "74LS245_" + QString::number(c.howMany());
    }
    setHardwareName(bufferName);
    for(int i=0;i<BUFFER_PIN_NUM;i++){
        pins[i]=inf;
    }
}

void Buffers245::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-100]=value;
    if(pin==MicroCom::BF5_g && pins[pin-100]==low){
        setOutputVoltage();
    }
    emit pinVolChanged(pin);
}

Voltage Buffers245::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-100];
}

void Buffers245::setOutputVoltage(){
    if(pins[MicroCom::BF5_DIR-100]==high){
        for(int i=0;i<8;i++){
            pins[i]=pins[i+8];
            emit pinVolChanged(static_cast<MicroCom::Pins>(i+108));
        }
        qDebug()<<"========74LS245 A->B works========";
        qDebug()<<"B0="<<getPinVoltage(MicroCom::BF5_B0);
        qDebug()<<"B1="<<getPinVoltage(MicroCom::BF5_B1);
        qDebug()<<"B2="<<getPinVoltage(MicroCom::BF5_B2);
        qDebug()<<"B3="<<getPinVoltage(MicroCom::BF5_B3);
        qDebug()<<"B4="<<getPinVoltage(MicroCom::BF5_B4);
        qDebug()<<"B5="<<getPinVoltage(MicroCom::BF5_B5);
        qDebug()<<"B6="<<getPinVoltage(MicroCom::BF5_B6);
        qDebug()<<"B7="<<getPinVoltage(MicroCom::BF5_B7);
    }
    else{
        for(int i=0;i<8;i++){
            pins[i+8]=pins[i];
            emit pinVolChanged(static_cast<MicroCom::Pins>(i+100));
        }
        qDebug()<<"========74LS245 B->A works========";
        qDebug()<<"A0="<<getPinVoltage(MicroCom::BF5_A0);
        qDebug()<<"A1="<<getPinVoltage(MicroCom::BF5_A1);
        qDebug()<<"A2="<<getPinVoltage(MicroCom::BF5_A2);
        qDebug()<<"A3="<<getPinVoltage(MicroCom::BF5_A3);
        qDebug()<<"A4="<<getPinVoltage(MicroCom::BF5_A4);
        qDebug()<<"A5="<<getPinVoltage(MicroCom::BF5_A5);
        qDebug()<<"A6="<<getPinVoltage(MicroCom::BF5_A6);
        qDebug()<<"A7="<<getPinVoltage(MicroCom::BF5_A7);
    }
    //有没有必要还原输出引脚电平呢？
    /*
    for(int i=0;i<4;i++){
        pins[i+pos]=pins[i];
        emit pinVolChanged(static_cast<MicroCom::Pins>(i+pos+80));
    }*/
}
