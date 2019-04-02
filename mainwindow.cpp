#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //unsigned short temp = 0x1234;
    CPUs *cp = new CPUs();
//    cp.setRegValue(MicroCom::ax,127);
//    qDebug()<<"ax="<<cp.getRegValue(MicroCom::ax);
//    cp.setRegValue(MicroCom::ax,high,7);
//    qDebug()<<"ax="<<cp.getRegValue(MicroCom::ax);
//    cp.setRegValue(MicroCom::ax,-1);
//    qDebug()<<"ax="<<cp.getRegValue(MicroCom::ax);
//    cp.setRegValue(MicroCom::ah,-1);
//    qDebug()<<"ah="<<cp.getRegValue(MicroCom::ah);
//  cp.emitReset();
//   qDebug()<<"cs="<<cp.getRegValue(MicroCom::cs);
    mov(cp,MicroCom::ax,0xffff);
    qDebug()<<"before mov ax,bx";
    qDebug()<<"ax="<<cp->getRegValue(MicroCom::ax);
    qDebug()<<"bx="<<cp->getRegValue(MicroCom::bx);
    mov(cp,MicroCom::bx,MicroCom::ax);
    qDebug()<<"after mov ax,bx";
    qDebug()<<"ax="<<cp->getRegValue(MicroCom::ax);
    qDebug()<<"bx="<<cp->getRegValue(MicroCom::bx);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//mov立即数寻址
void MainWindow::mov(CPUs *cp, MicroCom::Regs reg, unsigned short value){
    //在mov立即寻址中，目的操作数不能是cs、ds、es、ss、ip和flags
    if(reg>=MicroCom::cs && reg<=MicroCom::flags){
        return;
    }
    cp->setRegUnsignedValue(reg,value);
    return;
}

//mov寄存器寻址
void MainWindow::mov(CPUs *cp, MicroCom::Regs regD, MicroCom::Regs regS){
    //目的操作数不能是cs和flags
    if(regD==MicroCom::cs || regD==MicroCom::flags){
        return;
    }
    //目的操作数和源操作数的长度必须相同
    else if( (regD>=MicroCom::ax && regD<=MicroCom::ss) && (regS>=MicroCom::al && regS<=MicroCom::dh)){
        return;
    }
    else if((regD>=MicroCom::ax && regD<=MicroCom::ss) && (regS>=MicroCom::al && regS<=MicroCom::dh)){
        return;
    }
    else{
        cp->setRegUnsignedValue(regD,cp->getRegValue(regS));
    }
    return;
}

