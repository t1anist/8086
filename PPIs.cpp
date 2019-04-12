#include "PPIs.h"

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
        if(pins[i+24]==high){
            data += 1<<i;
        }
    }
    qDebug()<<"DATA IS"<<data;
    qDebug()<<"=============="<<getHardwareName()<<"END GET DATA===============";
    return data;
}

void PPIs::setOutputPinVoltage(MicroCom::PPIWorkWay wk, unsigned short value){
    int binary[8]={0};
    int num=8;
    int offset=0;
    switch (wk) {
    case MicroCom::PP_CLO:
        num=4;
        offset=16;
        break;
    case MicroCom::PP_CHO:
        num=4;
        offset=20;
        break;
    case MicroCom::PP_CO:
        offset=16;
        break;
    case MicroCom::PP_AO:
        offset=0;
        break;
    case MicroCom::PP_BO:
        offset=8;
        break;
    default:
        return;
    }
    toBinary(value,binary);

    for(int i=0;i<num;i++){
        if(binary[i]==1){
            setPinVoltage(static_cast<MicroCom::Pins>(i+PP_START+offset),high);
        }
        else{
            setPinVoltage(static_cast<MicroCom::Pins>(i+PP_START+offset),low);
        }
    }
}


void PPIs::setInputPinVoltage(int offset){
    int num=8;
    if(offset==16 || offset==20){
        num=4;
    }
    for(int i=0;i<num;i++){
        setPinVoltage(static_cast<MicroCom::Pins>(i+PP_START+24),pins[offset]);
    }
}


/** 8255A的模型需要好好思考一下 **/
//要给方式1、方式2留出实现的接口

//常用方式
/********************************************************
 *  controlReg(B)   controlReg(D)        Mode           *
 *  7 6 5 4 3 2 1                                       *
 *  1 0 0 0 0 0 0       128         A0O+CHO+B0O+CLO     *
 *  1 0 0 0 0 0 1       129         A0O+CHO+B0O+CLI     *
 *  1 0 0 0 0 1 0       130         A0O+CHO+B0I+CLO     *
 *       ...            ...                             *
 *                                                      *
 ********************************************************/

//A口可以工作于三种方式中的任一种。
//B口只能工作于方式0和方式1
//C口只能工作于方式0
//读取控制字寄存器无意义
void PPIs::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin-PP_START]=value;
    //如果要进行读写
    if( pin==MicroCom::PP_rd || pin==MicroCom::PP_wr ){
        //如果使能端有效
        if(PPIs::getPinVoltage(MicroCom::PP_cs)==low){
            //如果A口工作于方式2
            /*if(getControlRegValue(6)==1){
                if(getControlRegValue(2)==1){}   //如果B口工作于方式2
                else if(getControlRegValue(2)==0{}  //如果B口工作于方式0
              }
              else if(getControlRegValue(6)==0 && getControlRegValue(5)==1){ //如果A口工作于方式1
                if(getControlRegValue(2)==1){}   //如果B口工作于方式1
                else if(getControlRegValue(2)==0{}  //如果B口工作于方式0
              }
              else if(getControlRegValue(5)==0){    //如果A口工作于方式0
                if(getControlRegValue(2)==1){}   //如果B口工作于方式1
                else if(getControlRegValue(2)==0{}  //如果B口工作于方式0
              }
              else{
                如果A、B、C口均工作于方式0
              }

            */

            //读取数据总线上的数据
            unsigned short data = getDataValue();
            Voltage A0 = PPIs::getPinVoltage(MicroCom::PP_A0);
            Voltage A1 = PPIs::getPinVoltage(MicroCom::PP_A1);

            /** 向8255A写入数据 **/
            if(PPIs::getPinVoltage(MicroCom::PP_wr)==low){
                qDebug()<<"=========="<<getHardwareName()<<"START =============";
                qDebug()<<"================ WRITE MODE ================";
                if(A0==low){
                    //选择A口
                    if(A1==low){
                        qDebug()<<"======== WRITE INTO PORT A ===========";
                        if(getControlRegValue(4)==0){
                           setOutputPinVoltage(MicroCom::PP_AO,data);
                        }
                        else{
                            qDebug()<<"ERROR: PORT A IN WRONG WORK WAY";
                        }

                    }
                    //选择C口
                    else if(A1==high){
                        qDebug()<<"======== WRITE INTO PORT C ===========";
                        if(getControlRegValue(3)==0){
                            if(getControlRegValue(0)==0){
                                setOutputPinVoltage(MicroCom::PP_CO,data);
                            }
                            else if(getControlRegValue(0)==1){
                                setOutputPinVoltage(MicroCom::PP_CHO,data);
                            }
                        }
                        else if(getControlRegValue(0)==0){
                            setOutputPinVoltage(MicroCom::PP_CLI,data);
                        }
                        else{
                            qDebug()<<"ERROR: PORT C IN WRONG WORK WAY";
                        }
                    }
                }
                else if(A0==high){
                    //选择B口
                    if(A1==low){
                        qDebug()<<"======== WRITE INTO PORT B ===========";
                        if(getControlRegValue(1)==0){
                           setOutputPinVoltage(MicroCom::PP_BO,data);
                        }
                        else{
                            qDebug()<<"ERROR: PORT B IN WRONG WORK WAY";
                        }
                    }
                    //选择控制字寄存器口
                    else if(A1==high){
                        qDebug()<<"======== WRITE INTO PORT CONTROL ===========";
                        //将数据写入控制字寄存器
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
                                    pos += 1<<i;
                                }
                            }
                            setPinVoltage(static_cast<MicroCom::Pins>(pos+PP_START+16),value);
                        }
                    }
                    qDebug()<<"=========="<<getHardwareName()<<"END =============";
                }
                else{
                    return;
                }
            }

            /** 从8255A读取数据 **/
            else if(PPIs::getPinVoltage(MicroCom::PP_rd)==low){
                qDebug()<<"============ READ MODE ==============";
                if(A0==low){
                    //从A端口读取数据
                    if(A1==low){
                        qDebug()<<"======== READ FROM PORT A ===========";
                        setInputPinVoltage(0);
                    }
                    //从C端口读取数据
                    else if(A1==high){
                        qDebug()<<"======== READ FROM PORT C ===========";
                        setInputPinVoltage(16);
                    }
                }
                else if(A0==high){
                    //从B端口读取数据
                    if(A1==low){
                        qDebug()<<"======== READ FROM PORT B ===========";
                        setInputPinVoltage(8);
                    }
                }
                else{
                    return;
                }
            }

            //如果wr和rd均无效
            else{
                return;
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

int PPIs::getWorkWay(){
    int A = 0;
    int B = 0;
    A = getControlRegValue(6);

}

