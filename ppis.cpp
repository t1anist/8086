#include "ppis.h"

PPIs::PPIs(QString ppiName){
    controlReg = 0;
    if(ppiName==nullptr){
        ppiName = "8255A_" + QString::number(c.howMany());
    }
    setHardwareName(ppiName);
    for(int i=0;i<PPI_PIN_NUM;i++){
        pins[i]=inf;
    }
}

void PPIs::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin-PP_START]=value;
    emit pinVolChanged(pin);
}

Voltage PPIs::getPinVoltage(MicroCom::Pins pin){
    return pins[pin-PP_START];
}

unsigned short PPIs::getDataValue(){
    unsigned short data = 0;
    qDebug()<<"=============="<<getHardwareName()<<"START GET DATA===============";
    for(int i=0;i<8;i++){
        if(pins[PP_START+24+i]==high){
            data += 2^i;
        }
    }
    qDebug()<<"DATA IS"<<data;
    qDebug()<<"=============="<<getHardwareName()<<"END GET DATA===============";
    return data;
}

//A口可以工作于三种方式中的任一种。
void PPIs::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin-PP_START]=value;
    if( pin==MicroCom::PP_rd || pin==MicroCom::PP_wr ){
        //如果使能端有效
        if(PPIs::getPinVoltage(MicroCom::PP_cs)==low){
            //如果wr有效，说明向8255A写入数据
            if(PPIs::getPinVoltage(MicroCom::PP_wr)==low){
                unsigned short data = getDataValue();
                setControlRegValue(data);
                //如果控制字寄存器的标志位为0，则表示要执行置位/复位操作
                if(getControlRegValue(7)==0){
                    Voltage value = inf;
                    int pos = 0;
                    if(getControlRegValue(0)==1){
                        value = high;
                    }
                    else{
                        value = low;
                    }
                    for(int i=0;i<3;i++){
                        if(getControlRegValue(i+1)==1){
                            pos += 2^i;
                        }
                    }
                    setPinVoltage(static_cast<MicroCom::Pins>(pos+PP_START+16),value);
                }
            }
            //如果wr有效，说明从8255A读取数据
            else if(PPIs::getPinVoltage(MicroCom::PP_rd)==low){
                int flag = -1;
                //首先判断A口工作方式
                flag = getControlRegValue(6);
                if(flag==1){
                    qDebug()<<"A口方式为方式2";
                }
                else{
                    flag = getControlRegValue(5);
                    if(flag==1){
                        qDebug()<<"A口工作在方式1";
                    }
                    else{
                        qDebug()<<"A口工作在方式0";
                    }
                }

                flag = getControlRegValue(7);
            }
            //如果标志位为0，表示设置控制字寄存器
            else{

            }
        }
        //如果使能端无效
        else{
            return;
        }
    }
    return;
}

//set the Register's value
void PPIs::setControlRegValue(unsigned short value){
    controlReg &= 0;
    controlReg |= value;
}

//set the Register's value by pos
void PPIs::setControlRegValue(Voltage biValue, int pos){
    unsigned short flag = 0;
    unsigned short temp = 1;
    if(biValue==high){
        flag = 1;
    }
    flag <<= pos;
    temp <<= pos;
    temp = ~temp;
    controlReg &= temp;
    controlReg |= flag;
}

unsigned short PPIs::getControlRegValue(){
    return controlReg;
}

int PPIs::getControlRegValue(int pos){
    if(pos<0||pos>7){
        qDebug()<<"pos wrong!";
        return -1;
    }
    unsigned short flag=1;
    flag <<= pos;
    if(( pos&controlReg )>0){
        return 1;
    }
    else{
        return 0;
    }
}

