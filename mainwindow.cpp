#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CPUs cp;
    cp.setRegValue(MicroCom::ax,127);
    qDebug()<<"ax="<<cp.getRegValue(MicroCom::ax);
    cp.setRegValue(MicroCom::ax,high,7);
    qDebug()<<"ax="<<cp.getRegValue(MicroCom::ax);
    cp.setRegValue(MicroCom::ax,-1);
    qDebug()<<"ax="<<cp.getRegValue(MicroCom::ax);
    cp.setRegValue(MicroCom::ah,-1);
    qDebug()<<"ah="<<cp.getRegValue(MicroCom::ah);
}

MainWindow::~MainWindow()
{
    delete ui;
}
