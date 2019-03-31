#include "cpus.h"
#include <QDebug>

CPUs::CPUs()
{

}

/****************************************************
 - Function: select the pin of 8086 CPU
 - Calls：
 - Called By：
        + setVoltage(MicroCom::Pins,Voltage);
        + getPinVoltage(MicroCom::pins);
 - Input：[MicroCom::Pins pin]、[Voltage pinVol(引脚电平)]
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
 - Calls：selectPin(MicroCom::Pins pin)
 - Called By：
 - Input：[MicroCom::Pins pin]、[Voltage pinVol(引脚电平)]
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
unsigned short* CPUs::selectRegister(MicroCom::Regs reg){
    switch(reg){
    //16-bit register
    case MicroCom::ax:
        return &ax;
    case MicroCom::bx:
        return &bx;
    case MicroCom::cx:
        return &cx;
    case MicroCom::dx:
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
    //8-bit register
    case MicroCom::ah:
        return &ax;
    case MicroCom::al:
        return &ax;
    case MicroCom::bh:
        return &bx;
    case MicroCom::bl:
        return &bx;
    case MicroCom::ch:
        return &cx;
    case MicroCom::cl:
        return &cx;
    case MicroCom::dh:
        return &dx;
    case MicroCom::dl:
        return &dx;
    default:
        return nullptr;
    }
}

/****************************************************
 - Function：get the register's value
 - Calls：
 - Called By：getRegValue(MicroCom::Regs reg,short pos)
 - Input：[MicroCom::Reg]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
unsigned short CPUs::getRegValue(MicroCom::Regs reg){
    unsigned short* rst = selectRegister(reg);
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


/****************************************************
 - Function：get the register's value in a particular position
 - Description：pos limit(16-bit:0-15 8-bit:0-7)
 - Calls：getRegValue(MicroCom::Regs reg)
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：register value with complement form
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
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
 - Description：
 - Calls：
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
void CPUs::setRegValue(MicroCom::Regs reg, short value){
    unsigned short cValue = 0;
    unsigned short* rst = selectRegister(reg);
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
};

/****************************************************
 - Function：set the register's value in a particular position
 - Description：pos limit(16-bit:0-15 8-bit:0-7)
 - Calls：
        + Hardwars::setValueByPos(unsigned short& value, short pos, MicroCom::Regs reg, Voltage biValue)
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
void CPUs::setRegValue(MicroCom::Regs reg, Voltage biValue, short pos){
    unsigned short* rst = selectRegister(reg);
    setValueByPos(*rst,pos,reg,biValue);
}


/****************************************************
 - Function：True Form to Complement Form
 - Description：The default length of the regs is 16-bit
 - Calls：
 - Called By：
 - Input：[value(true form), MicroCom::RegsLen]
 - Output：
 - Return：value(complement form)[16-bit unsigned short]
*****************************************************/
unsigned short CPUs::toCompForm(short value, MicroCom::RegsLen len){
    unsigned char temp = 0;
    //16-bit register
    if(len==MicroCom::dbyte){
        return static_cast<unsigned short>(value);
    }
    //8-bit register
    else{
        temp = static_cast<unsigned char>(value);
    }
    return static_cast<unsigned short>(temp);
}

/****************************************************
 - Function：complement form to unsigned true form
 - Description：The default length of the regs is 16-bit
 - Calls：
 - Called By：
 - Input：[value(complement form), MicroCom::RegsLen]
 - Output：
 - Return：a unsigned short number
*****************************************************/
unsigned short CPUs::toUnsignedTrueForm(unsigned short value, MicroCom::RegsLen len){
    //8-bit
    if(len==MicroCom::byte){
        value &= 0x00ff;
    }
    return value;
}

/****************************************************
 - Function：complement form to signed true form
 - Description：The default length of the regs is 16-bit
 - Calls：
 - Called By：
 - Input：[value(complement form), MicroCom::RegsLen]
 - Output：
 - Return：a signed short number
*****************************************************/
short CPUs::toSignedTrueForm(unsigned short value, MicroCom::RegsLen len){
    unsigned char temp = 0;
    short rst=0;
    //16-bit
    if(len==MicroCom::dbyte){
        rst = static_cast<short>(value);
    }
    else{
        value &= 0x00ff;
        temp = static_cast<unsigned char>(value);
        rst = static_cast<char>(temp);
        rst = static_cast<short>(rst);
    }
    return rst;
}


