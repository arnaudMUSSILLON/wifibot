#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbClose_clicked()
{
    //fermeture de la fenêtre
    this->close();
}

void MainWindow::on_pbConnect_clicked()
{
    //création socket + connexion au robot
    //connect();
}
