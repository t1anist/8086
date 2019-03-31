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
