#include "Decoders.h"

Decoders::Decoders(QString decoderName){
    status=8;
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

//设置引脚电平，并发送输出引脚电平改变信号
void Decoders::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-DE_START]=value;
    emit pinVolChanged(pin);
}

//获取引脚电平函数
Voltage Decoders::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-DE_START];
}

//处理上游引脚电平改变
void Decoders::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin-DE_START]=value;
    //首先只有触发使能端才会有效
    if(pin==MicroCom::DE_G1 || pin==MicroCom::DE_G2a || pin==MicroCom::DE_G2b){
        //只有使能端均有效时才会触发译码功能
        if(Decoders::getPinVoltage(MicroCom::DE_G1)==high
                && Decoders::getPinVoltage(MicroCom::DE_G2a)==low
                && Decoders::getPinVoltage(MicroCom::DE_G2b)==low){
            int rst = 0;
            //ABC（0~7）->相应的"y_"变为低电平
            for(int i=0;i<3;i++){
                //C:pins[5],B:pins[4],A:pins[3]
                if(pins[i+3]==high){
                    rst += 1<<i;
                }
            }
            for(int i=0;i<8;i++){
                setPinVoltage(static_cast<MicroCom::Pins>(i+6+DE_START),high);
            }
            //译码器正在执行译码功能
            setPinVoltage(static_cast<MicroCom::Pins>(rst+6+DE_START),low);
            status = rst;//status的范围为0~7,表示译码器正在工作
            qDebug()<<"========="<<getHardwareName()<<"WORK========";
            qDebug()<<"y0="<<Decoders::getPinVoltage(MicroCom::DE_y0);
            qDebug()<<"y1="<<Decoders::getPinVoltage(MicroCom::DE_y1);
            qDebug()<<"y2="<<Decoders::getPinVoltage(MicroCom::DE_y2);
            qDebug()<<"y3="<<Decoders::getPinVoltage(MicroCom::DE_y3);
            qDebug()<<"y4="<<Decoders::getPinVoltage(MicroCom::DE_y4);
            qDebug()<<"y5="<<Decoders::getPinVoltage(MicroCom::DE_y5);
            qDebug()<<"y6="<<Decoders::getPinVoltage(MicroCom::DE_y6);
            qDebug()<<"y7="<<Decoders::getPinVoltage(MicroCom::DE_y7);
            qDebug()<<"========="<<getHardwareName()<<"END=========";
        }
        //使能端非有效电平时
        else{
            //如果译码器处于初始化或者未工作状态，则不重复执行还原操作
            if(status==8){
                return;
            }
            qDebug()<<"========="<<getHardwareName()<<"输出端全置1=========";
            setPinVoltage(static_cast<MicroCom::Pins>(status+6+DE_START),high);
            //还原译码器输出端口，将译码器的工作状态置为未工作。
            status = 8;
        }
    }
}


