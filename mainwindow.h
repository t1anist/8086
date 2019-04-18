#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include "CPUs.h"
#include "Latchs.h"
#include "PPIs.h"
#include "Decoders.h"
#include "LogicGate.h"
#include "Buffers.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //mov 立即数寻址
    //  ·送入寄存器
    void mov(CPUs *cp, MicroCom::Regs reg, int value, bool isAddressing);
    //  ·送入存储单元
    void mov(CPUs *cp, int addr, int imValue);

    //mov 直接寻址
    //  存储单元 -> 寄存器
    void mov(CPUs *cp, MicroCom::Regs regD, int addr);
    //  存储单元 ->

    //mov 寄存器直接寻址/间接寻址
    // memory -> reg
    void mov(CPUs *cp, MicroCom::Regs regD, MicroCom::Regs regS, bool isAddressing);
    // memory -> reg

    void mov(CPUs *cp, int addr, MicroCom::Regs regS, bool isAddressing=false);
   // void mov(CPUs *cp, MicroCom::Regs basedReg, MicroCom::Regs indexedReg, int count)
    //寄存器间接寻址（相对寻址）
    int readAddressing(CPUs *cp, MicroCom::Regs, MicroCom::Regs indexed =MicroCom::no, MicroCom::Regs prefix=MicroCom::no, int count=0);
    void writeAddressing(CPUs *cp, MicroCom::Regs, int value=0, MicroCom::Regs indexed=MicroCom::no, MicroCom::Regs prefixed=MicroCom::no, int count=0);
    //连线函数，将两个引脚连接起来
    void link(Hardwares *sender, MicroCom::Pins pinS, Hardwares *receiver, MicroCom::Pins pinR);
    bool isOdd(int i);

    //Input and Output
    void in(CPUs* cp, MicroCom::Regs reg, int addr=-1);
    void out(CPUs* cp, MicroCom::Regs reg, int addr=-1);

private:
    Ui::MainWindow *ui;
    CPUs* cp1;
    Latchs* la1;
    Latchs* la2;
    Latchs* la3;
    Buffers *bf1;
    Buffers *bf2;
    Decoders* de1;
    PPIs* pp1;
    LogicGate* nand;
};

#endif // MAINWINDOW_H
