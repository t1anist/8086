#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cp1 = new CPUs();
    cp1->readBusCycle(0x1234);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//mov立即数寻址
void MainWindow::mov(CPUs *cp, MicroCom::Regs reg, unsigned short value){
    cp->setRegUnsignedValue(reg,value);
    return;
}

//mov寄存器寻址
void MainWindow::mov(CPUs *cp, MicroCom::Regs regD, MicroCom::Regs regS){
    cp->setRegUnsignedValue(regD,cp->getRegValue(regS));
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


void MainWindow::link(Hardwares* sender, Voltage volS, Hardwares* target, MicroCom::Pins pinT){
    connect(sender, &Hardwares::pinVolChanged, [=](){target->handleOuterVolChange(pinT,volS);});
    return;
}
