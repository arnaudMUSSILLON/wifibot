#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setFocus();
    this->ui->upArrowBtn->setArrowType(Qt::UpArrow);
    this->ui->downArrowBtn->setArrowType(Qt::DownArrow);
    this->ui->rightArrowBtn->setArrowType(Qt::RightArrow);
    this->ui->leftArrowBtn->setArrowType(Qt::LeftArrow);
    this->c= new Controler();
    this->cameraControler = new QNetworkAccessManager();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::on_connectBtn_clicked
 * Gestion de la connexion au clic du bouton
 */
void MainWindow::on_connectBtn_clicked()
{
    if(this->ui->tfAddress->text() == "" || this->ui->tfPort->text() == ""){
        QMessageBox::warning(this, "Connexion","Veuillez remplir les champs Adresse et Port",QMessageBox::Ok);
    }
    else{
        //appel de la méthode connect
        QString ip = this->ui->tfAddress->text();
        int port = this->ui->tfPort->text().toInt();
        c->askConnection(ip,port);
        QString source = "http://"+ui->tfAddress->text()+":8080/javascript_simple.html";
        ui->videoFrame->load(QUrl(source));
        ui->videoFrame->setZoomFactor(1.4);
        ui->videoFrame->setStyleSheet("background-color:#ffffff;");
        ui->videoFrame->show();
    }
}

/**
 * @brief MainWindow::on_disconnectBtn_clicked
 * Gestion de la déconnexion au clic du bouton
 */
void MainWindow::on_disconnectBtn_clicked()
{
    c->disconnect();
    ui->videoFrame->stop();
}


void MainWindow::updateMove(){
    int vitesse = 100;
    if(isPressedZ && !isPressedQ && !isPressedS && !isPressedD){
        c->move(vitesse, vitesse, 1);
        qDebug() << "z";
    }
    else{
        c->move(0,0,1);
    }
}


void::MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Z:
        ui->zBtn->animateClick();
        ui->zBtn->click();
        isPressedZ = true;
        break;

    case Qt::Key_S:
        ui->sBtn->animateClick();
        ui->sBtn->click();
        break;

    case Qt::Key_D:
        ui->dBtn->animateClick();
        ui->dBtn->click();
        break;

    case Qt::Key_Q:
        ui->qBtn->animateClick();
        ui->qBtn->click();
        break;

    case Qt::Key_Up:
        ui->upArrowBtn->animateClick();
        ui->upArrowBtn->click();
        break;

    case Qt::Key_Down:
        ui->downArrowBtn->animateClick();
        ui->downArrowBtn->click();
        ui->qBtn->click();
        break;

    case Qt::Key_Left:
        ui->leftArrowBtn->animateClick();
        ui->leftArrowBtn->click();
        ui->qBtn->click();
        break;

    case Qt::Key_Right:
        ui->rightArrowBtn->animateClick();
        ui->rightArrowBtn->click();
        break;
    }
    updateMove();
}

void MainWindow::on_upArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_UP);
    cameraControler->get(QNetworkRequest(url));

}

void MainWindow::on_downArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_DOWN);
    cameraControler->get(QNetworkRequest(url));
}

void MainWindow::on_leftArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_LEFT);
    cameraControler->get(QNetworkRequest(url));
}

void MainWindow::on_rightArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_RIGHT);
    cameraControler->get(QNetworkRequest(url));
}
