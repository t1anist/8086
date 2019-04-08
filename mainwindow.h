#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include "cpus.h"

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

private:
    Ui::MainWindow *ui;
    CPUs* cp1;
    CPUs* cp2;
    CPUs* cp3;
};

#endif // MAINWINDOW_H
