#include "cpus.h"
#include <QDebug>

CPUs::CPUs()
{
    bool judge = setVoltage(MicroCom::rd, low);
    qDebug()<<"isSuccess?"<<judge;
    unsigned short ax = getRegValue(MicroCom::ax);
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
 - Function：get the pin's voltage of 8086 CPU
 - Calls：
 - Called By：
 - Input：[MicroCom::Pins pin]
 - Output：
 - Return：pin's voltage(high or low)
*****************************************************/
Voltage CPUs::getPinVoltage(MicroCom::Pins pin){
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
 - Function：get the register's value
 - Calls：
 - Called By：getRegValue(MicroCom::Regs reg,short pos)
 - Input：[MicroCom::Reg]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
unsigned short CPUs::getRegValue(MicroCom::Regs reg){
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
 - Function：set register's value
 - Description：
 - Calls：
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
void CPUs::setRegValue(MicroCom::Regs reg, short value){
    unsigned short cValue = 0;
    if(reg>0 && reg<15){
        cValue = toCompForm(value);
    }
    else{
        cValue = toCompForm(value,MicroCom::byte);
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
        ax = ax & 0x00ff;
        cValue <<= 8;
        ax = ax | cValue;
        break;
    case MicroCom::al:
        ax = ax & 0xff00;
        ax = ax | cValue;
        break;
    case MicroCom::bh:
        bx = bx & 0x00ff;
        cValue <<= 8;
        bx = bx | cValue;
        break;
    case MicroCom::bl:
        bx = bx & 0xff00;
        bx = bx | cValue;
        break;
    case MicroCom::ch:
        cx = cx & 0x00ff;
        cValue <<= 8;
        cx = cx | cValue;
        break;
    case MicroCom::cl:
        cx = cx & 0xff00;
        cx = cx | cValue;
        break;
    case MicroCom::dh:
        dx = dx & 0x00ff;
        cValue <<= 8;
        dx = dx | cValue;
        break;
    case MicroCom::dl:
        dx = dx & 0xff00;
        dx = dx | cValue;
        break;;
    default:
        break;
    }
};

/****************************************************
 - Function：set the register's value in a particular position
 - Description：pos limit(16-bit:0-15 8-bit:0-7)
 - Calls：
 - Called By：
 - Input：[MicroCom::Regs]
 - Output：
 - Return：内部寄存器号为reg的寄存器的值(8或16位)
*****************************************************/
void CPUs::setRegValue(MicroCom::Regs reg, Voltage biValue, short pos){
    unsigned short flag = 0;
    unsigned short temp = 1;
    if(biValue==high){
        flag = 1;
    }
    flag <<= pos;
    temp <<= pos;
    temp = ~temp;
    switch(reg){
    //16-bit register
    case MicroCom::ax:
        ax &= temp;
        ax |= flag;
        break;
    case MicroCom::bx:
        bx &= temp;
        bx |= flag;
        break;
    case MicroCom::cx:
        cx &= temp;
        cx |= flag;
        break;
    case MicroCom::dx:
        dx &= temp;
        dx |= flag;
        break;
    case MicroCom::cs:
        cs &= temp;
        cs |= flag;
        break;
    case MicroCom::ds:
        ds &= temp;
        ds |= flag;
        break;
    case MicroCom::es:
        es &= temp;
        es |= flag;
        break;
    case MicroCom::ss:
        ss &= temp;
        ss |= flag;
        break;
    case MicroCom::bp:
        bp &= temp;
        bp |= flag;
        break;
    case MicroCom::sp:
        sp &= temp;
        sp |= flag;
        break;
    case MicroCom::si:
        si &= temp;
        si |= flag;
        break;
    case MicroCom::di:
        di &= temp;
        di |= flag;
        break;
    case MicroCom::ip:
        ip &= temp;
        ip |= flag;
        break;
    case MicroCom::flags:
        flags &= temp;
        flags |= flag;
        break;
    //8-bit register
    case MicroCom::ah:
        flag <<= 8;
        temp = 1;
        temp <<= (pos+8);
        temp = ~temp;
        ax &= temp;
        ax |= flag;
        break;
    case MicroCom::al:
        ax &= temp;
        ax |= flag;
        break;
    case MicroCom::bh:
        flag <<= 8;
        temp = 1;
        temp <<= (pos+8);
        temp = ~temp;
        bx &= temp;
        bx |= flag;
        break;
    case MicroCom::bl:
        bx &= temp;
        bx |= flag;
        break;
    case MicroCom::ch:
        flag <<= 8;
        temp = 1;
        temp <<= (pos+8);
        temp = ~temp;
        cx &= temp;
        cx |= flag;
        break;
    case MicroCom::cl:
        cx &= temp;
        cx |= flag;
        break;
    case MicroCom::dh:
        flag <<= 8;
        temp = 1;
        temp <<= (pos+8);
        temp = ~temp;
        dx &= temp;
        dx |= flag;
        break;
    case MicroCom::dl:
        dx &= temp;
        dx |= flag;
        break;
    default:
        break;
    }
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
unsigned short toCompForm(short value, MicroCom::RegsLen len = MicroCom::dbyte){
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
