#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include "CPUs.h"
#include "Latchs.h"
#include "Buffers245.h"
#include "PPIs.h"
#include "Decoders.h"
#include "LogicGate.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //寄存器寻址
    unsigned short regAddressing(CPUs *cp, MicroCom::Regs reg);
    void mov(CPUs *cp, MicroCom::Regs reg, unsigned short value);
    void mov(CPUs *cp, MicroCom::Regs regD, MicroCom::Regs regS, bool isIndirect=false);
    unsigned short regIndiAddressing(CPUs *cp, MicroCom::Regs reg);
    void regIndiAddressing(CPUs *cp, MicroCom::Regs reg, unsigned short value);
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
    Buffers245* bf1;
    Buffers245* bf2;
    Decoders* de1;
    PPIs* pp1;
    LogicGate* nand;
};

#endif // MAINWINDOW_H
