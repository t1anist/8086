#include "decoders.h"

Decoders::Decoders(QString decoderName){
    if(decoderName == nullptr){
        decoderName = "74LS138_" + QString::number(c.howMany());
    }
    setHardwareName(decoderName);
    for(int i=0;i<6;i++){
        pins[i]=inf;
    }
    for(int i=6;i<DECODER_PIN_NUM;i++){
        pins[i]=high;
    }
}

void Decoders::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-60]=value;
    if(pin==MicroCom::DE_G1 || pin==MicroCom::DE_G2a || pin==MicroCom::DE_G2b){
        if(pins[MicroCom::DE_G1-60]==high && pins[MicroCom::DE_G2a-60]==low && pins[MicroCom::DE_G2b-60]==low){
            setOutputVoltage();
        }
    }
    emit pinVolChanged(pin);
}

Voltage Decoders::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-60];
}

void Decoders::setOutputVoltage(){
    int rst = 0;
    for(int i=0;i<3;i++){
        if(pins[i+3]==high){
            rst += 2^i;
        }
    }
    pins[rst+6]=low;
    emit pinVolChanged(static_cast<MicroCom::Pins>(rst+66));

    qDebug()<<"=========Latch works========";
    qDebug()<<"y0="<<getPinVoltage(MicroCom::DE_y0);
    qDebug()<<"y1="<<getPinVoltage(MicroCom::DE_y1);
    qDebug()<<"y2="<<getPinVoltage(MicroCom::DE_y2);
    qDebug()<<"y3="<<getPinVoltage(MicroCom::DE_y3);
    qDebug()<<"y4="<<getPinVoltage(MicroCom::DE_y4);
    qDebug()<<"y5="<<getPinVoltage(MicroCom::DE_y5);
    qDebug()<<"y6="<<getPinVoltage(MicroCom::DE_y6);
    qDebug()<<"y7="<<getPinVoltage(MicroCom::DE_y7);
    qDebug()<<"=========Latch ends=========";

    pins[rst+6]=high;
    emit pinVolChanged(static_cast<MicroCom::Pins>(rst+66));

}
