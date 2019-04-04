#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cp = new CPUs();
    cp->readBusCycle(0x1234);
   // t1 = startTimer(1000);
    //unsigned short temp = 0x1234;
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
    /*
    mov(cp,MicroCom::ax,0xffff);
    qDebug()<<"before mov ax,bx";
    qDebug()<<"ax="<<cp->getRegValue(MicroCom::ax);
    qDebug()<<"bx="<<cp->getRegValue(MicroCom::bx);
    mov(cp,MicroCom::bx,MicroCom::ax);
    qDebug()<<"after mov ax,bx";
    qDebug()<<"ax="<<cp->getRegValue(MicroCom::ax);
    qDebug()<<"bx="<<cp->getRegValue(MicroCom::bx);
    mov(cp,MicroCom::bx,0x00ff);
    mov(cp,MicroCom::ds,0x0000);
    regIndiAddressing(cp,MicroCom::bx);
    for(int i=1;i<21;i++){
        qDebug()<<"A["<<i<<"]="<<cp->getPinVoltage(static_cast<MicroCom::Pins>(i));
    }*/
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
    unsigned short rst = 0;
    //首先获取物理地址，在8086CPU内部完成
    int addr=0;
    //在默认情况下，如果寄存器是BP，则默认段寄存器为DS，其他情况则默认为DS
    if(reg==MicroCom::bp){
        addr = cp->getRegValue(MicroCom::ss)*16 + cp->getRegValue(reg);
    }
    else{
        addr = cp->getRegValue(MicroCom::ds)*16 + cp->getRegValue(reg);
    }
    //其次，进行读总线周期

    startTimer(1000);
    return 0;
}

/*
void MainWindow::timerEvent(QTimerEvent *event){
    if(event->timerId()==t1){
        static int sec = 0;
        sec++;
        switch(sec){
        case 1:
            //第一周期：地址线修改
            qDebug()<<"T1";
            //cp->setAddrPinsVoltage(0xffff);
            break;
        case 2:
            qDebug()<<"T2";
            break;
        case 3:
            qDebug()<<"T3";
            break;
        case 4:
            qDebug()<<"T4";
            break;
        default:
            qDebug()<<"now kill the timer";
            killTimer(t1);
            break;
        }

            //第二周期
        }
    }*/

