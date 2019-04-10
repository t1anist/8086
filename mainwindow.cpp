#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cp1 = new CPUs();
    cp2 = new CPUs();
    qDebug()<<cp1->getHardwareName();
    qDebug()<<cp2->getHardwareName();
    la1 = new Latchs();
    qDebug()<<la1->getHardwareName();
    /** 将CPU的地址线与74LS373锁存器的输入端相连 **/
    link(cp1,MicroCom::CP_AD0,la1,MicroCom::LA_DI0);
    link(cp1,MicroCom::CP_AD1,la1,MicroCom::LA_DI1);
    link(cp1,MicroCom::CP_AD2,la1,MicroCom::LA_DI2);
    link(cp1,MicroCom::CP_AD3,la1,MicroCom::LA_DI3);
    link(cp1,MicroCom::CP_AD4,la1,MicroCom::LA_DI4);
    link(cp1,MicroCom::CP_AD5,la1,MicroCom::LA_DI5);
    link(cp1,MicroCom::CP_AD6,la1,MicroCom::LA_DI6);
    link(cp1,MicroCom::CP_AD7,la1,MicroCom::LA_DI7);
    link(cp1,MicroCom::CP_Mio,la1,MicroCom::LA_G);
    link(cp1,MicroCom::CP_den,la1,MicroCom::LA_oe);
    //cp1->readBusCycle(0x00ff);
}

MainWindow::~MainWindow()
{
    delete ui;
    ui=nullptr;
    delete cp1;
    cp1=nullptr;
    delete cp2;
    cp2=nullptr;
    delete la1;
    la1=nullptr;
}

//mov立即数寻址
void MainWindow::mov(CPUs *cp, MicroCom::Regs reg, unsigned short value){
    cp->setRegUnsignedValue(reg,value);
    return;
}

//mov寄存器寻址
void MainWindow::mov(CPUs *cp, MicroCom::Regs regD, MicroCom::Regs regS, bool isIndirect){
    unsigned short rst = 0;
    if(isIndirect==true){
        rst = regIndiAddressing(cp,regS);
    }
    else{
        rst = cp->getRegValue(regS);
    }
    cp->setRegUnsignedValue(regD,rst);
    return;
}


//寄存器间接寻址(read)
unsigned short MainWindow::regIndiAddressing(CPUs*cp, MicroCom::Regs reg){
    //寄存器间接寻址的寄存器可以是BX、BP、SI和DI
    if(reg!=MicroCom::bx && reg!=MicroCom::bp && reg!=MicroCom::si && reg!=MicroCom::di){
        qDebug("错误发生在寄存器间接寻址函数中。。。");
        return 1;
    }
    int addr=0;
    //在默认情况下，如果寄存器是BP，则默认段寄存器为DS，其他情况则默认为DS
    if(reg==MicroCom::bp){
        addr = cp->getRegValue(MicroCom::ss)*16 + cp->getRegValue(reg);
    }
    else{
        addr = cp->getRegValue(MicroCom::ds)*16 + cp->getRegValue(reg);
    }
    return cp->readBusCycle(addr);
}

//寄存器间接寻址(write)
void MainWindow::regIndiAddressing(CPUs *cp, MicroCom::Regs reg, unsigned short value){
    //寄存器间接寻址的寄存器可以是BX、BP、SI和DI
    if(reg!=MicroCom::bx && reg!=MicroCom::bp && reg!=MicroCom::si && reg!=MicroCom::di){
        qDebug("错误发生在寄存器间接寻址函数中。。。");
        return;
    }
    int addr=0;
    //在默认情况下，如果寄存器是BP，则默认段寄存器为DS，其他情况则默认为DS
    if(reg==MicroCom::bp){
        addr = cp->getRegValue(MicroCom::ss)*16 + cp->getRegValue(reg);
    }
    else{
        addr = cp->getRegValue(MicroCom::ds)*16 + cp->getRegValue(reg);
    }
    cp->writeBusCycle(addr,value);
    return;
}


//连线函数
void MainWindow::link(Hardwares* sender, MicroCom::Pins pinS, Hardwares* receiver, MicroCom::Pins pinR){
    connect(sender, &Hardwares::pinVolChanged, [=](MicroCom::Pins pinC){
        if(pinC==pinS){
            receiver->handlePinVolChanges(pinR,sender->getPinVoltage(pinS));
        }
    });
    return;
}

