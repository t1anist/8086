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

    /** mov指令 **/
    //mov 立即数寻址
    //immediate value to target Register
    void mov(MicroCom::Regs target, int imValue);
    //immediate value to memory
    void mov(int imValue, int tAddr);
    void mov(int imValue, MicroCom::Regs tBased, int tOffset, MicroCom::Regs tIndexed,  MicroCom::Regs tPrefixed=MicroCom::no);

    //mov 寄存器寻址
    void mov(MicroCom::Regs target, MicroCom::Regs source);
    void mov(MicroCom::Dir, int addr, MicroCom::Regs reg);

    //mov 寄存器间接/相对寻址
    void mov(MicroCom::Dir, MicroCom::Regs reg, MicroCom::Regs based, int offset, MicroCom::Regs indexed=MicroCom::no, MicroCom::Regs prefixed=MicroCom::no);

    /** in/out指令 **/
    void in(MicroCom::Regs reg, int addr=-1);
    void out(MicroCom::Regs reg, int addr=-1);

    /** 出入栈指令 **/
    //push
    void push(MicroCom::Regs source);
    void push(MicroCom::Regs sBased, int tOffset, MicroCom::Regs tIndexed, MicroCom::Regs tPrefixed=MicroCom::no);
    void push(int addr);
    //pop
    void pop(MicroCom::Regs target);
    void pop(MicroCom::Regs tBased, int tOffset, MicroCom::Regs tIndexed, MicroCom::Regs tPrefixed=MicroCom::no);
    void pop(int addr);

    /** XCHG交换指令 **/
    //CPU to Memory(MicroCom::Out) or Memory to CPU(MicroCom::Read)
    void xChg(MicroCom::Dir, MicroCom::Regs reg, MicroCom::Regs based, int offset, MicroCom::Regs indexed=MicroCom::no, MicroCom::Regs prefixed=MicroCom::no);
    void xChg(MicroCom::Dir, MicroCom::Regs reg, int addr);
    //CPU to CPU
    void xChg(MicroCom::Regs target, MicroCom::Regs source);

    /** LEA取地址有效指令 **/
    //lea要求源操作数只能是存储单元，并且目的操作数必须是一个寄存器  (变量怎么表示呢？)
    //void LoadEffectiveAdds();
    void lea(MicroCom::Regs target, MicroCom::Regs sBased, int sOffset, MicroCom::Regs sIndexed=MicroCom::no);
    void lea(MicroCom::Regs target, QString symbol);

    /** LDS将双字指针送到寄存器和DS指令(Load Pointer Using DS) **/
    void loadPointerUsingDS(MicroCom::Regs target, MicroCom::Regs sBased, int sOffset, MicroCom::Regs sIndexed=MicroCom::no);
    void loadPointerUsingDS(MicroCom::Regs target, int sAddr);
    void loadPointerUsingDS(MicroCom::Regs target, QString symbol);





    /** 寻址指令 **/
    int getPhyAddr(MicroCom::Regs based, int offset, MicroCom::Regs indexed= MicroCom::no, MicroCom::Regs prefixed=MicroCom::no);

    //连线函数，将两个引脚连接起来
    void link(Hardwares *sender, MicroCom::Pins pinS, Hardwares *receiver, MicroCom::Pins pinR);

    //Input and Output


private:
    Ui::MainWindow *ui;
    CPUs* cp;
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
