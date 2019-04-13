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

void PPIs::setOutputPinVoltage(int offset, int len){
    for(int i=0;i<len;i++){
        setPinVoltage(static_cast<MicroCom::Pins>(i+offset+PP_START),pins[i+24]);
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

//要给方式1、方式2留出实现的接口（√）
void PPIs::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin-PP_START]=value;
    //如果要进行读写
    if( pin==MicroCom::PP_rd || pin==MicroCom::PP_wr ){
        //如果使能端有效
        if(PPIs::getPinVoltage(MicroCom::PP_cs)==low){
            switch (getWorkWay()) {
            case MicroCom::PPI_A2B1C0:
                //A(方式2) B(方式1) C(方式0)
                break;
            case MicroCom::PPI_A2B0C0:
                //A(方式2) B(方式0) C(方式0)
                break;
            case MicroCom::PPI_A1B1C0:
                //A(方式1) B(方式1) C(方式0)
                break;
            case MicroCom::PPI_A1B0C0:
                //A(方式1) B(方式0) C(方式0)
                break;
            case MicroCom::PPI_A0B1C0:
                //A(方式0) B(方式1) C(方式0)
                break;
            default:
                if(PPIs::getPinVoltage(MicroCom::PP_cs)==low){
                    writeMode();
                }
                else if(PPIs::getPinVoltage(MicroCom::PP_rd)==low){
                    readMode();
                }
                break;
            }
        }
    }
    return;
}


void PPIs::readMode(){
    int port = 0;
    Voltage A0 = PPIs::getPinVoltage(MicroCom::PP_A0);
    Voltage A1 = PPIs::getPinVoltage(MicroCom::PP_A1);
    if(A0==high)  port += 1;
    if(A1==high)  port += 2;
    qDebug()<<"=========="<<getHardwareName()<<"START =============";
    qDebug()<<"================ READ MODE ================";
    switch(port){
    case 0: //port A
        if(getControlRegValue(4)==0){
            qDebug()<<"======= START READ FROM PORT A =========";
            setOutputPinVoltage(0);
            qDebug()<<"======= READ FROM PORT A SUCCESS =========";
        }
        else{
            qDebug()<<"ERROR: PORT A IN WRONG WORK WAY";
        }
        break;

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


/** 向8255A写入数据 **/
void PPIs::writeMode(){
    int port = 0;
    Voltage A0 = PPIs::getPinVoltage(MicroCom::PP_A0);
    Voltage A1 = PPIs::getPinVoltage(MicroCom::PP_A1);
    if(A0==high)  port += 1;
    if(A1==high)  port += 2;
    qDebug()<<"=========="<<getHardwareName()<<"START =============";
    qDebug()<<"================ WRITE MODE ================";
    switch(port){
    case 0: //port A
        qDebug()<<"======= START WRITE INTO PORT A =========";
        if(getControlRegValue(4)==0){
            setOutputPinVoltage(0);
        }
        else{
            qDebug()<<"ERROR: PORT A IN WRONG WORK WAY";
        }
        break;
    case 1: //port B
        qDebug()<<"======= START WRITE INTO PORT B =========";
        if(getControlRegValue(1)==0){
            setOutputPinVoltage(8);
        }
        else{
            qDebug()<<"ERROR: PORT B IN WRONG WORK WAY";
        }
        break;
    case 2: //port C
        qDebug()<<"======= START WRITE INTO PORT C =========";
        if(getControlRegValue(0)==0){   //CL
            setOutputPinVoltage(16,4);
        }
        if(getControlRegValue(3)==0){    //CH
            setOutputPinVoltage(20,4);
        }
        break;
    default:    //port control
        setControlRegValue(getDataValue());
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
        break;
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



MicroCom::PPIWorkWay PPIs::getWorkWay(){
    int portAway_1 = getControlRegValue(6);
    int portAway_2 = getControlRegValue(5);
    int portBway = getControlRegValue(2);
    if(portAway_1==1){
        if(portBway == 0){  //A2B0
            return MicroCom::PPI_A2B0C0;
        }
        else{   //A2B1
            return MicroCom::PPI_A2B1C0;
        }
    }
    else{
        if(portAway_2==1){
            if(portBway == 0){  //A1B0
                return MicroCom::PPI_A1B0C0;
            }
            else{   //A1B1
                return MicroCom::PPI_A1B1C0;
            }
        }
        else{
            if(portBway == 0){  //A0B0
                return MicroCom::PPI_A0B0C0;
            }
            else{   //A0B1
                return MicroCom::PPI_A0B1C0;
            }
        }
    }
}

