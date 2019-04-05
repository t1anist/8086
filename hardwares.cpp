#include "hardwares.h"
#include "cpus.h"

Hardwares::Hardwares(QWidget *parent) : QWidget(parent)
{

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
bool Hardwares::setVoltage(MicroCom::Pins pin, Voltage pinVol){
    Voltage* p = selectPin(pin);
    *p = pinVol;
    emit pinVolChanged(pin);
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
Voltage Hardwares::getPinVoltage(MicroCom::Pins pin){
    return *selectPin(pin);
}


/****************************************************
 - Function：改变8或16位寄存器某一位的值
 - Calls：
 - Called By：
 - Input：
 - Output：
 - Return：
*****************************************************/
void Hardwares::setValueByPos(unsigned short &value, short pos, MicroCom::Regs reg, Voltage biValue){
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
    value &= temp;
    value |= flag;
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
unsigned short Hardwares::toCompForm(short value, MicroCom::RegsLen len){
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
 - Function：complement form to signed true form
 - Description：The default length of the regs is 16-bit
 - Calls：
 - Called By：
 - Input：[value(complement form), MicroCom::RegsLen]
 - Output：
 - Return：a signed short number in true form
*****************************************************/
short Hardwares::toTrueForm(unsigned short value, MicroCom::RegsLen len){
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

/****************************************************
 - Function：complement form to signed true form
 - Description：The default length of the regs is 16-bit
 - Calls：
 - Called By：
 - Input：[value(complement form), MicroCom::RegsLen]
 - Output：
 - Return：a signed short number in true form
*****************************************************/
void Hardwares::toBinary(int denary, short binary[]){
    int j=0;
    while(denary)
    {
        binary[j]=denary%2;
        denary/=2;
        j++;
    }
    if(j<ADDRNUM){
        for(int i=j;i<ADDRNUM;i++){
            binary[i]=0;
        }
    }
    return;
}

/****************************************************
 - Function：complement form to signed true form
 - Description：The default length of the regs is 16-bit
 - Calls：
 - Called By：
 - Input：[value(complement form), MicroCom::RegsLen]
 - Output：
 - Return：a signed short number in true form
*****************************************************/
unsigned short Hardwares::toDenary(short binary[]){
    unsigned short rst = 0;
    for(int i=0;i<DATANUM;i++){
        if(binary[i]==1){
            rst += 2^i;
        }
    }
    return rst;
}

