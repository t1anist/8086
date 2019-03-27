#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CPUs* mainCPU = new CPUs();

}

MainWindow::~MainWindow()
{
    delete ui;
}
