#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    cp1 = new CPUs("8086CPU");
    la1 = new Latchs("74LS373_1");
    la2 = new Latchs("74LS373_2");
    la3 = new Latchs("74LS373_3");
    bf1 = new Buffers245("74LS245_1");
    bf2 = new Buffers245("74LS245_2");
    pp1 = new PPIs("8255A");
    de1 = new Decoders("74LS138");
    nand = new LogicGate(MicroCom::NOR,"Not-And-Gate");

    /** 将CPU的地址线与74LS373锁存器的输入端相连 **/

    //将A0~A7与锁存器la1的DI0~DI7相连
    link(cp1,MicroCom::CP_AD0,la1,MicroCom::LA_DI0);
    link(cp1,MicroCom::CP_AD1,la1,MicroCom::LA_DI1);
    link(cp1,MicroCom::CP_AD2,la1,MicroCom::LA_DI2);
    link(cp1,MicroCom::CP_AD3,la1,MicroCom::LA_DI3);
    link(cp1,MicroCom::CP_AD4,la1,MicroCom::LA_DI4);
    link(cp1,MicroCom::CP_AD5,la1,MicroCom::LA_DI5);
    link(cp1,MicroCom::CP_AD6,la1,MicroCom::LA_DI6);
    link(cp1,MicroCom::CP_AD7,la1,MicroCom::LA_DI7);
    link(cp1,MicroCom::CP_ALE,la1,MicroCom::LA_G);
    //将A8~A15与锁存器la2的DI0~DI7相连
    link(cp1,MicroCom::CP_AD8,la2,MicroCom::LA_DI0);
    link(cp1,MicroCom::CP_AD9,la2,MicroCom::LA_DI1);
    link(cp1,MicroCom::CP_AD10,la2,MicroCom::LA_DI2);
    link(cp1,MicroCom::CP_AD11,la2,MicroCom::LA_DI3);
    link(cp1,MicroCom::CP_AD12,la2,MicroCom::LA_DI4);
    link(cp1,MicroCom::CP_AD13,la2,MicroCom::LA_DI5);
    link(cp1,MicroCom::CP_AD14,la2,MicroCom::LA_DI6);
    link(cp1,MicroCom::CP_AD15,la2,MicroCom::LA_DI7);
    link(cp1,MicroCom::CP_ALE,la2,MicroCom::LA_G);
    //将A16~A20与锁存器la3的DI0~DI3相连
    link(cp1,MicroCom::CP_AS16,la3,MicroCom::LA_DI0);
    link(cp1,MicroCom::CP_AS17,la3,MicroCom::LA_DI1);
    link(cp1,MicroCom::CP_AS18,la3,MicroCom::LA_DI2);
    link(cp1,MicroCom::CP_AS19,la3,MicroCom::LA_DI3);
    link(cp1,MicroCom::CP_bhe,la3,MicroCom::LA_DI4);
    link(cp1,MicroCom::CP_ALE,la3,MicroCom::LA_G);


    /** 将CPU与缓存器相连 **/
    //将D0~D7与缓冲器bf1的A0~A7相连
    link(cp1,MicroCom::CP_AD0,bf1,MicroCom::BF5_A0);
    link(cp1,MicroCom::CP_AD1,bf1,MicroCom::BF5_A1);
    link(cp1,MicroCom::CP_AD2,bf1,MicroCom::BF5_A2);
    link(cp1,MicroCom::CP_AD3,bf1,MicroCom::BF5_A3);
    link(cp1,MicroCom::CP_AD4,bf1,MicroCom::BF5_A4);
    link(cp1,MicroCom::CP_AD5,bf1,MicroCom::BF5_A5);
    link(cp1,MicroCom::CP_AD6,bf1,MicroCom::BF5_A6);
    link(cp1,MicroCom::CP_AD7,bf1,MicroCom::BF5_A7);
    link(cp1,MicroCom::CP_den,bf1,MicroCom::BF5_g);
    link(cp1,MicroCom::CP_DTr,bf1,MicroCom::BF5_DIR);
    //将D8~D15与缓冲器bf2的A0~A7相连
    link(cp1,MicroCom::CP_AD8,bf2,MicroCom::BF5_A0);
    link(cp1,MicroCom::CP_AD9,bf2,MicroCom::BF5_A1);
    link(cp1,MicroCom::CP_AD10,bf2,MicroCom::BF5_A2);
    link(cp1,MicroCom::CP_AD11,bf2,MicroCom::BF5_A3);
    link(cp1,MicroCom::CP_AD12,bf2,MicroCom::BF5_A4);
    link(cp1,MicroCom::CP_AD13,bf2,MicroCom::BF5_A5);
    link(cp1,MicroCom::CP_AD14,bf2,MicroCom::BF5_A6);
    link(cp1,MicroCom::CP_AD15,bf2,MicroCom::BF5_A7);
    link(cp1,MicroCom::CP_den,bf2,MicroCom::BF5_g);
    link(cp1,MicroCom::CP_DTr,bf2,MicroCom::BF5_DIR);

    /** 将锁存器与译码器74LS138相连 **/
    link(la1,MicroCom::LA_DO0,de1,MicroCom::DE_A);
    link(la1,MicroCom::LA_DO1,pp1,MicroCom::PP_A0);
    link(la1,MicroCom::LA_DO2,pp1,MicroCom::PP_A1);
    link(la1,MicroCom::LA_DO3,de1,MicroCom::DE_G2b);
    link(la1,MicroCom::LA_DO4,de1,MicroCom::DE_B);
    link(la1,MicroCom::LA_DO5,de1,MicroCom::DE_C);
    link(la1,MicroCom::LA_DO6,de1,MicroCom::DE_G1);
    link(la1,MicroCom::LA_DO7,nand,MicroCom::LG_I1);
    link(cp1,MicroCom::CP_Mio,nand,MicroCom::LG_I2);
    link(nand,MicroCom::LG_O,de1,MicroCom::DE_G2a);

    /** 将译码器与8255A相连 **/
    link(de1,MicroCom::DE_y6,pp1,MicroCom::PP_cs);
    link(cp1,MicroCom::CP_wr,pp1,MicroCom::PP_wr);
    link(cp1,MicroCom::CP_rd,pp1,MicroCom::PP_rd);

    /** 将缓冲器与8255A相连 **/
    link(bf1,MicroCom::BF5_B0,pp1,MicroCom::PP_D0);
    link(bf1,MicroCom::BF5_B1,pp1,MicroCom::PP_D1);
    link(bf1,MicroCom::BF5_B2,pp1,MicroCom::PP_D2);
    link(bf1,MicroCom::BF5_B3,pp1,MicroCom::PP_D3);
    link(bf1,MicroCom::BF5_B4,pp1,MicroCom::PP_D4);
    link(bf1,MicroCom::BF5_B5,pp1,MicroCom::PP_D5);
    link(bf1,MicroCom::BF5_B6,pp1,MicroCom::PP_D6);
    link(bf1,MicroCom::BF5_B7,pp1,MicroCom::PP_D7);


    cp1->writeBusCycle(0x0076,0x000f);
    qDebug()<<pp1->getControlRegValue();
    //cp1->readBusCycle(0xff);
    //cp1->writeBusCycle(0x00ff,28);
 //   pp1 = new PPIs();

    /*
    for(int i=0;i<8;i++){
        pp1->setControlRegValue(high,i);
    }*/
  //  pp1->setControlRegValue(0xffff);
   // qDebug()<<"pp1's control register's value is:"<<pp1->toTrueForm(pp1->getControlRegValue());


}

MainWindow::~MainWindow()
{
    delete ui;
    ui=nullptr;
    delete cp1;
    cp1=nullptr;
    delete la1;
    la1=nullptr;
    delete la2;
    la2=nullptr;
    delete la3;
    la3=nullptr;
    delete bf1;
    bf1=nullptr;
    delete bf2;
    bf2=nullptr;
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

