#include "buffers244.h"

Buffers244::Buffers244(QString bufferName){
    //初始化命名
    if(bufferName == nullptr){
        bufferName = "74LS244_" + QString::number(c.howMany());
    }
    setHardwareName(bufferName);
    //初始化引脚
    for(int i=0;i<BUFFER_PIN_NUM;i++){
        pins[i]=inf;
    }
}

void Buffers244::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-BF4_START]=value;
    emit pinVolChanged(pin);
}

//获取引脚电平函数
Voltage Buffers244::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-BF4_START];
}

//处理外部引脚电平改变函数，无需发送信号
void Buffers244::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin-BF4_START]=value;
    if(pin==MicroCom::BF4_Ga || pin==MicroCom::BF4_Gb){
        setOutputVoltage(pin,Buffers244::getPinVoltage(pin));
    }
}


void Buffers244::setOutputVoltage(MicroCom::Pins pin, Voltage value){
    //如果使能端Ga有效，则数据从1I(80~83,pins[0~3])端口->1O(84~87,pins[4~7])端口
    if(pin==MicroCom::BF4_Ga){
        for(int i=0;i<4;i++){
            if(value == low){
                setPinVoltage(static_cast<MicroCom::Pins>(i+4+BF4_START),pins[i]);
            }
            //对于Buffer来说，一旦使能端无效，输出端变为高阻(inf)状态
            else{
                setPinVoltage(static_cast<MicroCom::Pins>(i+4+BF4_START),inf);
            }
        }
        qDebug()<<"========74LS244_a works========";
        qDebug()<<"1A1="<<Buffers244::getPinVoltage(MicroCom::BF4_1O1);
        qDebug()<<"1A2="<<Buffers244::getPinVoltage(MicroCom::BF4_1O2);
        qDebug()<<"1A3="<<Buffers244::getPinVoltage(MicroCom::BF4_1O3);
        qDebug()<<"1A4="<<Buffers244::getPinVoltage(MicroCom::BF4_1O4);
    }
    //如果使能端Gb有效，则数据从2I(88~91,pins[8~11])端口->21O(92~95,pins[12~15])端口
    else{
        for(int i=0;i<4;i++){
            if(value == low){
                setPinVoltage(static_cast<MicroCom::Pins>(i+12+BF4_START),pins[i]);
            }
            //对于Buffer来说，一旦使能端无效，输出端变为高阻(inf)状态
            else{
                setPinVoltage(static_cast<MicroCom::Pins>(i+12+BF4_START),inf);
            }
        }
        qDebug()<<"========74LS244_b works========";
        qDebug()<<"2A1="<<Buffers244::getPinVoltage(MicroCom::BF4_2O1);
        qDebug()<<"2A2="<<Buffers244::getPinVoltage(MicroCom::BF4_2O2);
        qDebug()<<"2A3="<<Buffers244::getPinVoltage(MicroCom::BF4_2O3);
        qDebug()<<"2A4="<<Buffers244::getPinVoltage(MicroCom::BF4_2O4);
    }
}
