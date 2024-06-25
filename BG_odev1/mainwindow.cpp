#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mod1.h"
#include "mod2.h"
#include "mod3.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    mod1 *_mod1 = new mod1();
    _mod1->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    mod2 *_mod2 = new mod2();
    _mod2->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    mod3 *_mod3 = new mod3();
    _mod3->show();
}
