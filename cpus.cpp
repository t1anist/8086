#include "cpus.h"

CPUs::CPUs(QString cpuName){
    T=100;
    if(cpuName == nullptr){
        cpuName = "CPU_"+QString::number(c.howMany());
    }
    setHardwareName(cpuName);
    //init pin's voltage
    for(int i=0;i<CPU_PIN_NUM;i++){
        pins[i]=inf;
    }
}

/****************************************************
 - Function：获取寄存器的值
 - Calls：
 - Called By：
        + getRegValue(MicroCom::Regs reg, short pos)
 - Input：8086CPU内部寄存器号(reg)
 - Return：寄存器的值（类型：unsigned short）
*****************************************************/
unsigned short CPUs::getRegValue(MicroCom::Regs reg){
    if( reg >= MicroCom::ax && reg < MicroCom::al ){
        return innerReg[reg];
    }
    else{
        if(reg >=MicroCom::al && reg<=MicroCom::dl){
            return (innerReg[reg] & 0x00ff);
        }
        else{
            return (innerReg[reg] >> 8);
        }
    }
}

/****************************************************
 - Function：获取数据线的值
 - Calls：
 - Called By：
        + getRegValue(MicroCom::Regs reg,short pos)
 - Input：寄存器的长度（8位or16位）
 - Return：数据线表示的值（类型：unsigned short）
*****************************************************/
unsigned short CPUs::getDataValue(MicroCom::RegsLen len){
    short value[DATANUM] ={0};
    int numlen = static_cast<int>(len);
    for(int i=0;i<numlen;i++){
        (pins[i]==low)?value[i]=0:value[i]=1;
    }
    return toDenary(value);
}

/****************************************************
 - Function：get the register's value in a particular position
 - Description：pos limit(16-bit:0-15 8-bit:0-7)
 - Calls：
        + Voltage getRegValue(MicroCom::Regs reg)
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：register value with complement form
 - Return：Voltage value of the reg's selected pos
*****************************************************/
Voltage CPUs::getRegValue(MicroCom::Regs reg, short pos){
    unsigned short flag = 1;
    flag <<= pos;
    unsigned short rst = getRegValue(reg);
    if((rst & flag)>0){
        return high;
    }
    else{
        return low;
    }
}

/****************************************************
 - Function：set the register's value
 - Description：the value is a signed number
 - Calls：
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：
*****************************************************/
void CPUs::setRegValue(MicroCom::Regs reg, short value){
    if(reg>=MicroCom::ax && reg<=MicroCom::di){
        innerReg[reg] = toCompForm(value);
    }
    else{
        unsigned short cValue = toCompForm(value,MicroCom::byte);
        if( reg>=MicroCom::al && reg<=MicroCom::dl){
            innerReg[reg] &= 0xff00;
        }
        else{
            innerReg[reg] &= 0x00ff;
            cValue <<= 8;
        }
        innerReg[reg] |= cValue;
    }
}

/****************************************************
 - Function：set the register's value
 - Description：the value is a unsigned number
 - Calls：
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：
*****************************************************/
void CPUs::setRegUnsignedValue(MicroCom::Regs reg, unsigned short value){
    if( reg >= MicroCom::ax && reg < MicroCom::al ){
        innerReg[reg] = value;
    }
    else{
        if(reg>=MicroCom::al && reg<=MicroCom::dl){
            innerReg[reg] &= 0xff00;
        }
        else{
            innerReg[reg] &= 0x00ff;
            value <<= 8;
        }
        innerReg[reg] |= value;
    }
}

/****************************************************
 - Function：设置寄存器某一位的值
 - Description：位限制(16-bit:0-15 8-bit:0-7)
 - Calls：
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：
*****************************************************/
void CPUs::setRegValue(MicroCom::Regs reg, Voltage biValue, short pos){
    unsigned short flag = 0;
    unsigned short temp = 1;
    if(biValue==high){
        flag = 1;
    }
    //Registers excluding ah, bh, ch and dh
    if(reg>=MicroCom::ax && reg<MicroCom::ah){
        flag <<= pos;
        temp <<= pos;
    }
    //ah, bh, ch or dh
    else{
        flag <<= (pos+8);
        temp <<= (pos+8);
    }
    temp = ~temp;
    innerReg[reg] &= temp;
    innerReg[reg] |= flag;
}

/****************************************************
 - Function：设置地址线
 - Calls：
 - Called By：
 - Input：20位地址变量（addr）
 - Output：
 - Return：
*****************************************************/
void CPUs::setAddrPinsVoltage(int addr){
    short binary[ADDRNUM] = {0};
    toBinary(addr,binary);
    for(int i=0;i<ADDRNUM;i++){
        (binary[i])?pins[i]=high:pins[i]=low;
        emit pinVolChanged(static_cast<MicroCom::Pins>(i));
    }
}

//总线操作时序！怎么实现捏
unsigned short CPUs::readBusCycle(int phyAddr){
    address = phyAddr;
    qDebug()<<"============"<<getHardwareName()<<"===========";
    qDebug()<<"============T1 start=============";
    //【AD1~AD16】【AS17~AS20】T1期间输出地址
    qDebug()<<"now start to change address lins";
    setAddrPinsVoltage(address);
    //【ALE】在T1期间，地址锁存有效信号，是一个正脉冲，其余时间均为低电平
    setPinVoltage(MicroCom::CP_ALE,high);
    //【bhe】T1期间有效，高电平表示数据线的高8位无效，低电平表示有效
    setPinVoltage(MicroCom::CP_bhe,low);
    //【Mio】在整个总线周期中均有效，由于进行存储器操作，故Mio高电平
    setPinVoltage(MicroCom::CP_Mio,high);


    //【den】初始为高电平(den必须在DTr之前改变）
    setPinVoltage(MicroCom::CP_den,high);
    //【DTr】在T1~T4内保持低电平，T4周期一半时变高电平
    setPinVoltage(MicroCom::CP_DTr,low);


    //延时半周期后
    qDebug()<<"============T1 half=============";
    setPinVoltage(MicroCom::CP_ALE,low);
    //delaymsec(500);
    qDebug()<<"=============T1 end=============";

    /** T2 **/
    qDebug()<<"============T2 start=============";
    //【AD1~AD16】T2开始时变为高阻
    for(int i=1;i<16;i++){
        pins[i]=inf;
    }
    //【bhe】在T2~T4期间均为高电平
    setPinVoltage(MicroCom::CP_bhe,high);
    //【rd】在T2开始时变成低电平
    setPinVoltage(MicroCom::CP_rd,low);
    //【den】在T2~T4输出期间低电平，表示数据有效，用来实现数据的选通
    setPinVoltage(MicroCom::CP_den,low);
    //delaymsec(1000);
    qDebug()<<"============T2 end=============";

    /** T3 **/
    qDebug()<<"============T3 start============";
    delaymsec(T);
    //【AD1~AD16】在T3开始时接受数据
    data = getDataValue();
   // delaymsec(1000);
    qDebug()<<"============T3 end=============";

    /** T4 **/
    qDebug()<<"============T4 start============";
    //【AD1~AD16】在T4开始时变为高阻态
    for(int i=0;i<16;i++){
        pins[i]=inf;
    }
    //【rd】在T3结束时变高电平
    setPinVoltage(MicroCom::CP_rd,high);
    //【den】在T4开始时变高
    setPinVoltage(MicroCom::CP_den,high);
    //delaymsec(1000);
    qDebug()<<"============T4 end=============";
    return data;
}

void CPUs::writeBusCycle(int phyAddr, unsigned short value){
    address = phyAddr;
    /** 写总线周期 **/
    //QTimer::singleShot(1*SEC,this,&CPUs::T1);
    //QTimer::singleShot(2*SEC,this,&CPUs::T2);
    //QTimer::singleShot(3*SEC,this,&CPUs::T3);
    //QTimer::singleShot(4*SEC,this,&CPUs::T4);
    /** 将数据写入存储单元 **/

    return;
}

void CPUs::setPinVoltage(MicroCom::Pins pin, Voltage value){
    pins[pin]=value;
    emit pinVolChanged(pin);
}

void CPUs::handlePinVolChanges(MicroCom::Pins pin, Voltage value){
    pins[pin]=value;
    if(pin==MicroCom::CP_RESET && value==high){
        resetCPU();
    }
}

Voltage CPUs::getPinVoltage(MicroCom::Pins pin){
    return pins[pin];
}

/****************************************************
 - Function：8086CPU复位
 - Calls：
    + void CPUs::setPinVoltage(MicroCom::Pins pin, Voltage value)
 - Called By：
 - Input：
 - return：
*****************************************************/
void CPUs::resetCPU(){
    qDebug()<<"====================";
    qDebug()<<"====RESET START!====";
    qDebug()<<"====================";
    /** set registers' value **/
    innerReg[MicroCom::flags]=0;
    innerReg[MicroCom::cs]=0;
    innerReg[MicroCom::ip]=0;
    innerReg[MicroCom::ds]=0;
    innerReg[MicroCom::es]=0;
    innerReg[MicroCom::ss]=0;
    /** set pins' value **/
    for(int i=0;i<ADDRNUM;i++){
        pins[i]=inf;
    }
    setPinVoltage(MicroCom::CP_ALE,low);
    //inta 高电平后呈高阻
    setPinVoltage(MicroCom::CP_inta,high);
    setPinVoltage(MicroCom::CP_inta,inf);
    //rd 高电平后呈高阻
    setPinVoltage(MicroCom::CP_rd,high);
    setPinVoltage(MicroCom::CP_rd,inf);
    //wr 高电平后呈高阻
    setPinVoltage(MicroCom::CP_wr,high);
    setPinVoltage(MicroCom::CP_wr,inf);
    //Mio 高电平后呈高阻
    setPinVoltage(MicroCom::CP_Mio,high);
    setPinVoltage(MicroCom::CP_Mio,inf);
    //DTr 高电平后呈高阻
    setPinVoltage(MicroCom::CP_DTr,high);
    setPinVoltage(MicroCom::CP_DTr,inf);
    //den 高电平后呈高阻
    setPinVoltage(MicroCom::CP_den,high);
    setPinVoltage(MicroCom::CP_den,inf);
    //RESET引脚复位
    pins[MicroCom::CP_RESET]=low;
    qDebug()<<"====================";
    qDebug()<<"===RESET SUCCEES!===";
    qDebug()<<"====================";
    return;
}

//判断是否为奇数
bool CPUs::isOdd(int i){
    return (i&1) == 1;
}


