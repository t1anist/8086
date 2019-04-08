#include "cpus.h"

CPUs::CPUs()
{
    //一旦8086CPU的引脚值发生改变，就调用handleInnerVolChange槽函数执行相关操作
    connect(this,&CPUs::pinVolChanged,this,&CPUs::handleInnerVolChange);
    //clk_cpu = startTimer(500);//0.5秒一个脉冲
}

CPUs::CPUs(QString cpuName){
    setHardwareName(cpuName);
    connect(this,&CPUs::pinVolChanged,this,&CPUs::handleInnerVolChange);
}

CPUs::~CPUs(){
    delete this;
    //killTimer(clk_cpu);
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

//获取数据线上的数据，转化为unsigned short值
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
 - Function：set the register's value in a particular position
 - Description：pos limit(16-bit:0-15 8-bit:0-7)
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
 - Function：set the AD and AS pins' voltage
 - Description：是不是应该考虑给地址单独搞一个信号？
 - Calls：
 - Called By：
 - Input：address
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
    /** T1 **/
    qDebug()<<"T1 start";
    //【Mio】在整个总线周期中均有效，由于进行存储器操作，故Mio高电平
    setPinVoltage(MicroCom::Mio,high);
    //【bhe】T1期间有效，高电平表示数据线的高8位无效，低电平表示有效
    setPinVoltage(MicroCom::bhe,low);
    //【AD1~AD16】【AS17~AS20】T1期间输出地址
    qDebug()<<"now start to change address lins";
    setAddrPinsVoltage(address);
    //【ALE】在T1期间，地址锁存有效信号，是一个正脉冲，其余时间均为低电平

    setPinVoltage(MicroCom::ALE,high);
    //【DTr】在T1~T4内保持低电平，T4周期一半时变高电平
    setPinVoltage(MicroCom::DTr,low);
    //【den】初始为高电平
    setPinVoltage(MicroCom::den,high);
    delaymsec(500);

    //延时半周期后
    qDebug()<<"T1 half";
    setPinVoltage(MicroCom::ALE,low);
    delaymsec(500);
    qDebug()<<"T1 end";

    /** T2 **/
    qDebug()<<"T2 start";
    //【bhe】在T2~T4期间均为高电平
    setPinVoltage(MicroCom::bhe,high);
    //【AD1~AD16】T2开始时变为高阻
    for(int i=1;i<16;i++){
        pins[i]=himped;
    }
    //【rd】在T2开始时变成低电平
    setPinVoltage(MicroCom::rd,low);
    //【den】在T2~T4输出期间低电平，表示数据有效，用来实现数据的选通
    setPinVoltage(MicroCom::den,low);
    delaymsec(1000);
    qDebug()<<"T2 end";

    /** T3 **/
    qDebug()<<"T3 start";
    //【AD1~AD16】在T3开始时接受数据
    data = getDataValue();
    delaymsec(1000);
    qDebug()<<"T3 end";

    /** T4 **/
    qDebug()<<"T4 start";
    //【rd】在T3结束时变高电平
    setPinVoltage(MicroCom::rd,high);
    //【den】在T4开始时变高
    setPinVoltage(MicroCom::den,high);
    //【AD1~AD16】在T4开始时变为高阻态
    for(int i=0;i<16;i++){
        pins[i]=himped;
    }
    delaymsec(1000);
    qDebug()<<"T4 end";
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

Voltage CPUs::getPinVoltage(MicroCom::Pins pin){
    return pins[pin];
}

//8086CPU的复位函数
//高电平后呈高阻怎么表示
void CPUs::resetCPU(){
    qDebug()<<"====================";
    qDebug()<<"====RESET START!====";
    qDebug()<<"====================";
    //set registers' value
    innerReg[MicroCom::flags]=0;
    innerReg[MicroCom::cs]=0;
    innerReg[MicroCom::ip]=0;
    innerReg[MicroCom::ds]=0;
    innerReg[MicroCom::es]=0;
    innerReg[MicroCom::ss]=0;
    //set pins' voltage
    for(int i=0;i<ADDRNUM;i++){
        pins[i]=himped;
    }
    setPinVoltage(MicroCom::ALE,low);
    //inta 高电平后呈高阻
    //rd 高电平后呈高阻
    //wr 高电平后呈高阻
    //Mio 高电平后呈高阻
    //DTr 高电平后呈高阻
    //den 高电平后呈高阻
    pins[MicroCom::RESET]=low;
    qDebug()<<"====================";
    qDebug()<<"===RESET SUCCEES!===";
    qDebug()<<"====================";
    return;
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
void CPUs::handleInnerVolChange(MicroCom::Pins pin){
    if(pin==MicroCom::RESET && pins[pin]==high){
        resetCPU();
    }
}

void CPUs::timerEvent(QTimerEvent *e){
    sClock++;
    if(isOdd(sClock)==true){
        emit clockSignal(MicroCom::highPulse);
    }
    else{
        emit clockSignal(MicroCom::lowPulse);
    }
}

//判断是否为奇数
bool CPUs::isOdd(int i){
    return (i&1) == 1;
}

void CPUs::delaymsec(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < dieTime )

    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
