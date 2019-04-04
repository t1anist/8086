#include "cpus.h"


CPUs::CPUs()
{
    int a =1;
    qDebug()<<"a="<<a;
    connect(this,&CPUs::pip,this,&CPUs::resetCPU);
    //信号和槽的参数必须一致，否则编译不通过
    qDebug()<<"after connect";
}

/****************************************************
 - Function: select the pin of 8086 CPU
 - Calls：
 - Called By：
        + bool setVoltage(MicroCom::Pins,Voltage);
        + Voltage getPinVoltage(MicroCom::pins);
 - Input：[MicroCom::Pins]
 - Output：
 - Return：the pointer to the pin
*****************************************************/
Voltage* CPUs::selectPin(MicroCom::Pins pin){
    switch(pin){
    case MicroCom::AD1:
        return &AD[0];
    case MicroCom::AD2:
        return &AD[1];
    case MicroCom::AD3:
        return &AD[2];
    case MicroCom::AD4:
        return &AD[3];
    case MicroCom::AD5:
        return &AD[4];
    case MicroCom::AD6:
        return &AD[5];
    case MicroCom::AD7:
        return &AD[6];
    case MicroCom::AD8:
        return &AD[7];
    case MicroCom::AD9:
        return &AD[8];
    case MicroCom::AD10:
        return &AD[9];
    case MicroCom::AD11:
        return &AD[10];
    case MicroCom::AD12:
        return &AD[11];
    case MicroCom::AD13:
        return &AD[12];
    case MicroCom::AD14:
        return &AD[13];
    case MicroCom::AD15:
        return &AD[14];
    case MicroCom::AD16:
        return &AD[15];
    case MicroCom::AS17:
        return &AS[0];
    case MicroCom::AS18:
        return &AS[1];
    case MicroCom::AS19:
        return &AS[2];
    case MicroCom::AS20:
        return &AS[3];
    case MicroCom::Mio:
        return &Mio;
    case MicroCom::rd:
        return &rd;
    case MicroCom::wr:
        return &wr;
    case MicroCom::ALE:
        return &ALE;
    case MicroCom::CLK:
        return &CLK;
    case MicroCom::INTR:
        return &INTR;
    case MicroCom::READY:
        return &READY;
    case MicroCom::bhe:
        return &bhe;
    case MicroCom::RESET:
        return &RESET;
    case MicroCom::DTr:
        return &DTr;
    case MicroCom::den:
        return &den;
    default:
        return nullptr;
    }
}

/****************************************************
 - Function: set the pin's voltage of 8086 CPU
 - Calls：
        + unsigned short* selectPin(MicroCom::Pins pin)
 - Called By：
 - Input：[MicroCom::Pins]、[Voltage pinVol(引脚电平)]
 - Output：
 - Return：if succeed, return true; else return false
*****************************************************/
bool CPUs::setVoltage(MicroCom::Pins pin, Voltage pinVol){
    if(pinVol!=high && pinVol!=low){
        return false;
    }
    Voltage* p = selectPin(pin);
    *p = pinVol;
    return true;
}

/****************************************************
 - Function：get the pin's voltage of 8086 CPU
 - Calls：selectPin(MicroCom::Pins pin)
 - Called By：
 - Input：[MicroCom::Pins pin]
 - Output：
 - Return：pin's voltage(high or low)
*****************************************************/
Voltage CPUs::getPinVoltage(MicroCom::Pins pin){
    return *selectPin(pin);
}

/****************************************************
 - Function: select the register of 8086 CPU
 - Calls：
 - Called By：
        + void setRegValue(MicroCom::Regs reg, short value)
        + void setRegValue(MicroCom::Regs reg, Voltage biValue, short pos)
        + Voltage getRegValue(MicroCom::Regs reg, short pos)
        + unsigned short getRegValue(MicroCom::Regs reg)
 - Input：[MicroCom::Regs reg]
 - Output：
 - Return：the pointer to the register
*****************************************************/
unsigned short* CPUs::selectReg(MicroCom::Regs reg){
    switch(reg){
    case MicroCom::ax:
    case MicroCom::ah:
    case MicroCom::al:
        return &ax;
    case MicroCom::bx:
    case MicroCom::bh:
    case MicroCom::bl:
        return &bx;
    case MicroCom::cx:
    case MicroCom::ch:
    case MicroCom::cl:
        return &cx;
    case MicroCom::dx:
    case MicroCom::dh:
    case MicroCom::dl:
        return &dx;
    case MicroCom::cs:
        return &cs;
    case MicroCom::ds:
        return &ds;
    case MicroCom::es:
        return &es;
    case MicroCom::ss:
        return &ss;
    case MicroCom::bp:
        return &bp;
    case MicroCom::sp:
        return &sp;
    case MicroCom::si:
        return &si;
    case MicroCom::di:
        return &di;
    case MicroCom::ip:
        return &ip;
    case MicroCom::flags:
        return &flags;
    default:
        return nullptr;
    }
}

/****************************************************
 - Function：get the register's value
 - Calls：
 - Called By：
        + getRegValue(MicroCom::Regs reg,short pos)
 - Input：[MicroCom::Regs]
 - Output：
 - Return：16-bit value of the reg
*****************************************************/
unsigned short CPUs::getRegValue(MicroCom::Regs reg){
    unsigned short* rst = selectReg(reg);
    if( reg >= MicroCom::ax && reg < MicroCom::al ){
        return *rst;
    }
    else{
        if(reg >=MicroCom::al && reg<=MicroCom::dl){
            return (*rst & 0x00ff);
        }
        else{
            return (*rst >> 8);
        }
    }
}

unsigned short CPUs::getDataValue(MicroCom::RegsLen len){
    short value[DATANUM] ={0};
    int numlen = static_cast<int>(len);
    for(int i=0;i<numlen;i++){
        (AD[i]==low)?value[i]=0:value[i]=1;
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
    unsigned short cValue = 0;
    unsigned short* rst = selectReg(reg);
    if(reg>0 && reg<15){
        cValue = toCompForm(value);
    }
    else{
        cValue = toCompForm(value,MicroCom::byte);
    }
    if( reg >= MicroCom::ax && reg < MicroCom::al ){
        *rst = cValue;
    }
    else{
        if(reg >=MicroCom::al && reg<=MicroCom::dl){
            *rst &= 0xff00;
        }
        else{
            *rst &= 0x00ff;
            cValue <<= 8;
        }
        *rst |= cValue;
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
    unsigned short* rst = selectReg(reg);
    if( reg >= MicroCom::ax && reg < MicroCom::al ){
        *rst = value;
    }
    else{
        if(reg >=MicroCom::al && reg<=MicroCom::dl){
            *rst &= 0xff00;
        }
        else{
            *rst &= 0x00ff;
            value <<= 8;
        }
        *rst |= value;
    }
}

/****************************************************
 - Function：set the register's value in a particular position
 - Description：pos limit(16-bit:0-15 8-bit:0-7)
 - Calls：
        + Hardwars::setValueByPos(unsigned short& value, short pos, MicroCom::Regs reg, Voltage biValue)
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：
*****************************************************/
void CPUs::setRegValue(MicroCom::Regs reg, Voltage biValue, short pos){
    unsigned short* rst = selectReg(reg);
    setValueByPos(*rst,pos,reg,biValue);
}

/****************************************************
 - Function：set the AD and AS pins' voltage
 - Description：
 - Calls：
 - Called By：
 - Input：address
 - Output：
 - Return：
*****************************************************/
void CPUs::setAddrPinsVoltage(int addr){
    short binary[ADDRNUM] = {0};
    toBinary(addr,binary);
    for(int i=0;i<DATANUM;i++){
        if(binary[i]==1){
            AD[i]=high;
        }
        else{
            AD[i]=low;
        }
    }
    for(int i=0;i<4;i++){
        if(binary[i+DATANUM]==1){
            AS[i]=high;
        }
        else{
            AS[i]=low;
        }
    }
}

void CPUs::T1(){

    //【Mio】在整个总线周期中均有效，由于进行存储器操作，故Mio高电平
    Mio = high;
    //【bhe】T1期间有效，高电平表示数据线的高8位无效，低电平表示有效
    bhe = low;
    //【AD1~AD16】【AS17~AS20】T1期间输出地址
    setAddrPinsVoltage(address);
    //【ALE】在T1期间，地址锁存有效信号，是一个正脉冲，其余时间均为低电平
    ALE = high;
        //延时半周期后
    ALE = low;
    //【DTr】在T1~T4内保持低电平，T4周期一半时变高电平
    DTr = low;
    //【den】初始为高电平
    den = high;
    qDebug()<<"this is T1";
}

void CPUs::T2(){
    /** T2 **/
    //【AS17~AS20】T2~T4期间输出的是状态线S6~S3

    //【bhe】在T2~T4期间均为高电平
    bhe = high;
    //【AD1~AD16】T2开始时变为高阻
    for(int i=1;i<16;i++){
        AD[i]=himped;
    }
    //【rd】在T2开始时变成低电平
    rd = low;
    //【den】在T2~T4输出期间低电平，表示数据有效，用来实现数据的选通
    den = low;
    qDebug()<<"this is T2";
}

void CPUs::T3(){
    /** T3 **/
    //【AD1~AD16】在T3开始时接受数据
    data = getDataValue();
    //【rd】在T3结束时变高电平
    rd = high;
    qDebug()<<"this is T3";
}

void CPUs::T4(){
    /** T4 **/
    //【den】在T4开始时变高
    den = high;
    //【AD1~AD16】在T4开始时变为高阻态
    for(int i=1;i<16;i++){
        AD[i] = himped;
    }
    qDebug()<<"this is T4";
}

unsigned short CPUs::readBusCycle(int phyAddr){
    address = phyAddr;
    //QTimer *timer1 = new QTimer(this);
    QTimer::singleShot(1000,this,&CPUs::T1);
    QTimer::singleShot(2000,this,&CPUs::T2);
    QTimer::singleShot(3000,this,&CPUs::T3);
    QTimer::singleShot(4000,this,&CPUs::T4);
    return data;
}




void CPUs::emitReset(){
    emit pip();
}

//8086CPU的复位函数
//高电平后呈高阻怎么表示
void CPUs::resetCPU(){
    //set registers' value
    flags=0;
    cs=0xffff;
    ip=0;
    ds=0;
    es=0;
    ss=0;
    //set pins' voltage
    for(int i=0;i<16;i++){
        AD[i]=himped;
    }
    for(int i=0;i<4;i++){
        AS[i]=himped;
    }
    ALE = low;
    //inta 高电平后呈高阻
    //rd 高电平后呈高阻
    //wr 高电平后呈高阻
    //Mio 高电平后呈高阻
    //DTr 高电平后呈高阻
    //den 高电平后呈高阻
    return;
}
