#include "hardwares.h"

Hardwares::Hardwares(QWidget *parent) : QWidget(parent)
{

}

void Hardwares::setHardwareName(QString hdName){
    hardwareName = hdName;
}

QString Hardwares::getHardwareName(){
    return hardwareName;
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

