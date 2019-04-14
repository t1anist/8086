#include "Hardwares.h"

Hardwares::Hardwares(QWidget *parent) : QWidget(parent)
{

}

void Hardwares::setHardwareName(QString hdName){
    hardwareName = hdName;
}


/****************************************************
 - Function：get the hardware's name
 - Description：
 - Input：
 - Return：hardware's name(QString)
*****************************************************/
QString Hardwares::getHardwareName(){
    return hardwareName;
}

/****************************************************
 - Function：True Form to Complement Form
 - Description：The default length of the regs is 16-bit
 - Input：[value(true form), MicroCom::RegsLen]
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
 - Input：[value(complement form), MicroCom::RegsLen]
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
 - Function：delay or sleep
 - Description：非阻塞延时
 - Input：msec（毫秒）
 - Return：
*****************************************************/
void Hardwares::delaymsec(int msec){
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while( QTime::currentTime() < dieTime )
    QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}
