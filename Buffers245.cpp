#include "buffers245.h"

Buffers245::Buffers245(QString bufferName){
    status = 0;
    if(bufferName == nullptr){
        bufferName = "74LS245_" + QString::number(c.howMany());
    }
    setHardwareName(bufferName);
    for(int i=0;i<BUFFER_PIN_NUM;i++){
        pins[i]=inf;
    }
}

void Buffers245::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-BF5_START]=value;
    emit pinVolChanged(pin);
}

Voltage Buffers245::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-BF5_START];
}

void Buffers245::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin-BF5_START]=value;
    if(pin==MicroCom::BF5_g){
        //如果使能端为低电平（有效）
        if(value==low){
            status=1;
            //如果DIR为高电平，则数据从A(100~107,pins[0~7])->B(108~115,pins[8~15])
            if(Buffers245::getPinVoltage(MicroCom::BF5_DIR)==high){
                for(int i=0;i<8;i++){
                    setPinVoltage(static_cast<MicroCom::Pins>(i+8+BF5_START),pins[i]);
                }
                qDebug()<<"========"<<getHardwareName()<<"A->B works========";
                qDebug()<<"B0="<<Buffers245::getPinVoltage(MicroCom::BF5_B0);
                qDebug()<<"B1="<<Buffers245::getPinVoltage(MicroCom::BF5_B1);
                qDebug()<<"B2="<<Buffers245::getPinVoltage(MicroCom::BF5_B2);
                qDebug()<<"B3="<<Buffers245::getPinVoltage(MicroCom::BF5_B3);
                qDebug()<<"B4="<<Buffers245::getPinVoltage(MicroCom::BF5_B4);
                qDebug()<<"B5="<<Buffers245::getPinVoltage(MicroCom::BF5_B5);
                qDebug()<<"B6="<<Buffers245::getPinVoltage(MicroCom::BF5_B6);
                qDebug()<<"B7="<<Buffers245::getPinVoltage(MicroCom::BF5_B7);
            }
            //如果DIR为低电平，则数据从B(108~115,pins[8~15])端口->A(100~107,pins[0~7])端口
            else{
                for(int i=0;i<8;i++){
                    setPinVoltage(static_cast<MicroCom::Pins>(i+BF5_START),pins[i+8]);
                }
                qDebug()<<"========"<<getHardwareName()<<"B->A works========";
                qDebug()<<"A0="<<Buffers245::getPinVoltage(MicroCom::BF5_A0);
                qDebug()<<"A1="<<Buffers245::getPinVoltage(MicroCom::BF5_A1);
                qDebug()<<"A2="<<Buffers245::getPinVoltage(MicroCom::BF5_A2);
                qDebug()<<"A3="<<Buffers245::getPinVoltage(MicroCom::BF5_A3);
                qDebug()<<"A4="<<Buffers245::getPinVoltage(MicroCom::BF5_A4);
                qDebug()<<"A5="<<Buffers245::getPinVoltage(MicroCom::BF5_A5);
                qDebug()<<"A6="<<Buffers245::getPinVoltage(MicroCom::BF5_A6);
                qDebug()<<"A7="<<Buffers245::getPinVoltage(MicroCom::BF5_A7);
            }
        }
        //如果不是低电平（非有效）
        else{
            if(status==0){
                return;
            }
            status=0;
            for(int i=0;i<16;i++){
                setPinVoltage(static_cast<MicroCom::Pins>(i+BF5_START),inf);
            }
            qDebug()<<"========"<<getHardwareName()<<"使能端无效========";
            qDebug()<<"=======所有引脚已被置为高阻=======";
        }
    }
}
