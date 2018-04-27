#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->ui->upArrowBtn->setArrowType(Qt::UpArrow);
    this->ui->downArrowBtn->setArrowType(Qt::DownArrow);
    this->ui->rightArrowBtn->setArrowType(Qt::RightArrow);
    this->ui->leftArrowBtn->setArrowType(Qt::LeftArrow);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_connectBtn_clicked
 * Connection button handling
 */
void MainWindow::on_connectBtn_clicked()
{
    if(this->ui->tfAddress->text() == "" && this->ui->tfPort->text() == ""){
        QMessageBox msgBox;
        msgBox.setText("Veuillez remplir les champs Adresse et Port");
        msgBox.exec();
    }
    if(this->ui->tfAddress->text() == "" && this->ui->tfPort->text() != ""){
        QMessageBox msgBox;
        msgBox.setText("Veuillez remplir le champ Adresse");
        msgBox.exec();
    }
    if(this->ui->tfPort->text() == "" && this->ui->tfAddress->text() != ""){
        QMessageBox msgBox;
        msgBox.setText("Veuillez remplir le champ Port");
        msgBox.exec();
    }
}
