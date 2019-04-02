#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
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
    void mov(CPUs *cp, MicroCom::Regs regD, MicroCom::Regs regS);


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
