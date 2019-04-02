#include "hardwares.h"

Hardwares::Hardwares(QWidget *parent) : QWidget(parent)
{

}

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
