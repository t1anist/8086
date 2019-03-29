#include "cpus.h"
#include <QDebug>

CPUs::CPUs()
{
    bool judge = setVoltage(MicroCom::rd, low);
    qDebug()<<"isSuccess?"<<judge;
    short ax = readInnerReg(MicroCom::ax);
    qDebug()<<"ax="<<ax;
}

/****************************************************
 - Function: set the pin's voltage of 8086 CPU
 - Calls：
 - Called By：
 - Input：[MicroCom::Pins pin]、[Voltage pinVol(引脚电平)]
 - Output：
 - Return：if succeed, return true; else return false
*****************************************************/
bool CPUs::setVoltage(MicroCom::Pins pin, Voltage pinVol){
    if(pinVol!=high && pinVol!=low){
        return false;
    }
    switch(pin){
    case MicroCom::AD1:
        AD[0] = pinVol;
        break;
    case MicroCom::AD2:
        AD[1] = pinVol;
        break;
    case MicroCom::AD3:
        AD[2] = pinVol;
        break;
    case MicroCom::AD4:
        AD[3] = pinVol;
        break;
    case MicroCom::AD5:
        AD[4] = pinVol;
        break;
    case MicroCom::AD6:
        AD[5] = pinVol;
        break;
    case MicroCom::AD7:
        AD[6] = pinVol;
        break;
    case MicroCom::AD8:
        AD[7] = pinVol;
        break;
    case MicroCom::AD9:
        AD[8] = pinVol;
        break;
    case MicroCom::AD10:
        AD[9] = pinVol;
        break;
    case MicroCom::AD11:
        AD[10] = pinVol;
        break;
    case MicroCom::AD12:
        AD[11] = pinVol;
        break;
    case MicroCom::AD13:
        AD[12] = pinVol;
        break;
    case MicroCom::AD14:
        AD[13] = pinVol;
        break;
    case MicroCom::AD15:
        AD[14] = pinVol;
        break;
    case MicroCom::AD16:
        AD[15] = pinVol;
        break;
    case MicroCom::AS17:
        AS[0] = pinVol;
        break;
    case MicroCom::AS18:
        AS[1] = pinVol;
        break;
    case MicroCom::AS19:
        AS[2] = pinVol;
        break;
    case MicroCom::AS20:
        AS[3] = pinVol;
        break;
    case MicroCom::Mio:
        Mio = pinVol;
        break;
    case MicroCom::rd:
        rd = pinVol;
        break;
    case MicroCom::wr:
        wr = pinVol;
        break;
    case MicroCom::ALE:
        ALE = pinVol;
        break;
    case MicroCom::CLK:
        CLK = pinVol;
        break;
    case MicroCom::INTR:
        INTR = pinVol;
        break;
    case MicroCom::READY:
        READY = pinVol;
        break;
    case MicroCom::bhe:
        bhe = pinVol;
        break;
    case MicroCom::RESET:
        RESET = pinVol;
        break;
    case MicroCom::DTr:
        DTr = pinVol;
        break;
    case MicroCom::den:
        den = pinVol;
        break;
    default:
        break;
    }
    return true;
}

/****************************************************
 - Function：read the pin's voltage of 8086 CPU
 - Calls：
 - Called By：
 - Input：[MicroCom::Pins pin]
 - Output：
 - Return：pin's voltage(high or low)
*****************************************************/
Voltage CPUs::readVoltage(MicroCom::Pins pin){
    switch(pin){
    case MicroCom::AD1:
        return AD[0];
    case MicroCom::AD2:
        return AD[1];
    case MicroCom::AD3:
        return AD[2];
    case MicroCom::AD4:
        return AD[3];
    case MicroCom::AD5:
        return AD[4];
    case MicroCom::AD6:
        return AD[5];
    case MicroCom::AD7:
        return AD[6];
    case MicroCom::AD8:
        return AD[7];
    case MicroCom::AD9:
        return AD[8];
    case MicroCom::AD10:
        return AD[9];
    case MicroCom::AD11:
        return AD[10];
    case MicroCom::AD12:
        return AD[11];
    case MicroCom::AD13:
        return AD[12];
    case MicroCom::AD14:
        return AD[13];
    case MicroCom::AD15:
        return AD[14];
    case MicroCom::AD16:
        return AD[15];
    case MicroCom::AS17:
        return AS[0];
    case MicroCom::AS18:
        return AS[1];
    case MicroCom::AS19:
        return AS[2];
    case MicroCom::AS20:
        return AS[3];
    case MicroCom::Mio:
        return Mio;
    case MicroCom::rd:
        return rd;
    case MicroCom::wr:
        return wr;
    case MicroCom::ALE:
        return ALE;
    case MicroCom::CLK:
        return CLK;
    case MicroCom::INTR:
        return INTR;
    case MicroCom::READY:
        return READY;
    case MicroCom::bhe:
        return bhe;
    case MicroCom::RESET:
        return RESET;
    case MicroCom::DTr:
        return DTr;
    case MicroCom::den:
        return den;
    default:
        return himped;
    }
}


/****************************************************
 - Function：read the register's value
 - Calls：
 - Called By：readInnerReg(MicroCom::Regs reg,short pos)
 - Input：[MicroCom::Reg]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
unsigned short CPUs::readInnerReg(MicroCom::Regs reg){
    switch(reg){
    //16-bit register
    case MicroCom::ax:
        return ax;
    case MicroCom::bx:
        return bx;
    case MicroCom::cx:
        return cx;
    case MicroCom::dx:
        return dx;
    case MicroCom::cs:
        return cs;
    case MicroCom::ds:
        return ds;
    case MicroCom::es:
        return es;
    case MicroCom::ss:
        return ss;
    case MicroCom::bp:
        return bp;
    case MicroCom::sp:
        return sp;
    case MicroCom::si:
        return si;
    case MicroCom::di:
        return di;
    case MicroCom::ip:
        return ip;
    case MicroCom::flags:
        return flags;
    //8-bit register
    case MicroCom::ah:
        return (ax >> 8);
    case MicroCom::al:
        return (ax & 0x00ff);
    case MicroCom::bh:
        return (bx >> 8);
    case MicroCom::bl:
        return (bx & 0x00ff);
    case MicroCom::ch:
        return (cx >> 8);
    case MicroCom::cl:
        return (cx & 0x00ff);
    case MicroCom::dh:
        return (dx >> 8);
    case MicroCom::dl:
        return (dx & 0x00ff);
    default:
        return 0;
    }
}

/****************************************************
 - Function：read register's value in a particular position
 - Description：pos limit(16-bit:0-15 8-bit:0-7)
 - Calls：readInnerReg(MicroCom::Regs reg)
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：register value with complement form
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
Voltage CPUs::readInnerReg(MicroCom::Regs reg, short pos){
    unsigned short flag = 1;
    Voltage value = himped;
    flag = flag << pos;
    unsigned short rst = readInnerReg(reg);
    if((rst & flag)>0){
        return high;
    }
    else{
        return low;
    }
}

/****************************************************
 - Function：set register's value
 - Description：
 - Calls：
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
void CPUs::setInnerReg(MicroCom::Regs reg, short value){
    unsigned short cValue = 0;
    if(reg<15){
        //将value转换为unsigned形式的补码cValue，由于是16位寄存器，不必填寄存器长度参数
        //toCompForm(short value);
    }
    else{
        //将value转换为unsigned形式的补码cValue
        //toCompForm(short value, MicroCom::byte)
    }
    switch(reg){
    //16-bit register
    case MicroCom::ax:
        ax = cValue;
        break;
    case MicroCom::bx:
        bx = cValue;
        break;
    case MicroCom::cx:
        cx = cValue;
        break;
    case MicroCom::dx:
        dx = cValue;
        break;
    case MicroCom::cs:
        cs = cValue;
        break;
    case MicroCom::ds:
        ds = cValue;
        break;
    case MicroCom::es:
        es = cValue;
        break;
    case MicroCom::ss:
        ss = cValue;
        break;
    case MicroCom::bp:
        bp = cValue;
        break;
    case MicroCom::sp:
        sp = cValue;
        break;
    case MicroCom::si:
        si = cValue;
        break;
    case MicroCom::di:
        di = cValue;
        break;
    case MicroCom::ip:
        ip = cValue;
        break;
    case MicroCom::flags:
        flags = cValue;
        break;
    //8-bit register
    case MicroCom::ah:
        return (ax >> 8);
    case MicroCom::al:
        return (ax & 0x00ff);
    case MicroCom::bh:
        return (bx >> 8);
    case MicroCom::bl:
        return (bx & 0x00ff);
    case MicroCom::ch:
        return (cx >> 8);
    case MicroCom::cl:
        return (cx & 0x00ff);
    case MicroCom::dh:
        return (dx >> 8);
    case MicroCom::dl:
        return (dx & 0x00ff);
    default:
        return 0;
    }
};


/****************************************************
 - Function：set the register's value
 - Description：
 - Calls：
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
void setInnerReg(MicroCom::Regs reg, Voltage biValue, short pos);





/****************************************************
 - Function：True Form to Complement Form
 - Description：The default length of regs is double byte
 - Calls：
 - Called By：
 - Input：[value(true form), MicroCom::RegsLen]
 - Output：
 - Return：value(complement form)[unsignde short]
*****************************************************/
unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte){
    //16-bit register
    if(len==MicroCom::dbyte){
        if(value<0){
            return static_cast<int>(value);
        }
        else {
            return value;
        }
    }
    //8-bit register
    else{
        if(value<0){

        }
    }
}


/****************************************************
 - Function：Complement Form to True Form
 - Description：The default length of regs is double byte
 - Calls：
 - Called By：
 - Input：[value(complement form), MicroCom::RegsLen]
 - Output：
 - Return：内部寄存器号为inReg的寄存器的值(8或16位)
*****************************************************/



//Complement Form to True Form 默认长度为16位
short toTrueForm(unsigned short value, MicroCom::RegsLen len = MicroCom::dbyte);
