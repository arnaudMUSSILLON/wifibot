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

    connect(this->ui->speedSlider,SIGNAL(valueChanged(int)),SLOT(setLbValue(int)));
    QString t = c->getBatterie();
    this->ui->label->text() = t;

}

MainWindow::~MainWindow()
{
    delete ui;
}

/* ***********************************
    Gestion des boutons
*************************************/

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
        ui->videoFrame->setVisible(true);
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
    ui->videoFrame->setVisible(false);
}

/**
 * @brief MainWindow::on_captureBtn_clicked
 * Gestion du bouton de capture d'écran
 */
void MainWindow::on_captureBtn_clicked()
{
    screenshot();
}

/**
 * @brief MainWindow::on_upArrowBtn_pressed
 * Gestion du contrôle de la caméra lors de l'appui sur la flèche haut
 */
void MainWindow::on_upArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_UP);
    cameraControler->get(QNetworkRequest(url));

<<<<<<< HEAD
=======
void MainWindow::updateMove(){
    int vitesse = 240;
    if(isPressedZ && !isPressedQ && !isPressedS && !isPressedD){
        c->move(vitesse, vitesse, 1);
        qDebug() << "z";
    }
    else{
        c->move(vitesse, vitesse, 3);
    }
>>>>>>> 9b08c53ff0edcea932a820caad6454d4415fa5b3
}

/**
 * @brief MainWindow::on_upArrowBtn_pressed
 * Gestion du contrôle de la caméra lors de l'appui sur la flèche bas
 */
void MainWindow::on_downArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_DOWN);
    cameraControler->get(QNetworkRequest(url));
}

/**
<<<<<<< HEAD
 * @brief MainWindow::on_upArrowBtn_pressed
 * Gestion du contrôle de la caméra lors de l'appui sur la flèche gauche
 */
void MainWindow::on_leftArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_LEFT);
    cameraControler->get(QNetworkRequest(url));
}

/**
 * @brief MainWindow::on_upArrowBtn_pressed
 * Gestion du contrôle de la caméra lors de l'appui sur la flèche droite
 */
void MainWindow::on_rightArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_RIGHT);
    cameraControler->get(QNetworkRequest(url));
}

/**
 * @brief ::MainWindow::keyPressEvent
 * @param event
 * assignation des boutons aux touches
=======
 * @brief ::MainWindow::keyPressEvent event when a key is pressed
 * @param event
>>>>>>> 9b08c53ff0edcea932a820caad6454d4415fa5b3
 */
void::MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Z:
        ui->zBtn->animateClick();
        ui->zBtn->click();
        isPressedZ = true;
        break;

    case Qt::Key_S:
        ui->sBtn->animateClick();
        break;

    case Qt::Key_D:
        ui->dBtn->animateClick();
        break;

    case Qt::Key_Q:
        ui->qBtn->animateClick();
        break;

    case Qt::Key_Up:
        ui->upArrowBtn->animateClick();
        break;

    case Qt::Key_Down:
        ui->downArrowBtn->animateClick();
        ui->qBtn->click();
        break;

    case Qt::Key_Left:
        ui->leftArrowBtn->animateClick();
        ui->qBtn->click();
        break;

    case Qt::Key_Right:
        ui->rightArrowBtn->animateClick();
        break;
    }
    updateMove();
}

<<<<<<< HEAD
/* ***********************************
    Gestion du mouvement
*************************************/
=======

/**
 * @brief Event when a key is released
 * @param event
 */
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Z:
        isPressedZ = false;
        break;
    case Qt::Key_Q:
        isPressedD = false;
        break;
    case Qt::Key_S:
        isPressedS = false;
        break;
    case Qt::Key_D:
        isPressedD = false;
        break;
    }
    updateMove();
}


void MainWindow::on_upArrowBtn_pressed()
{
    QUrl url("http://"+ui->tfAddress->text()+":8080"+CAM_UP);
    cameraControler->get(QNetworkRequest(url));
>>>>>>> 9b08c53ff0edcea932a820caad6454d4415fa5b3

/**
 * @brief MainWindow::updateMove
 * Gestion du mouvement du robot
 */
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

/* ***********************************
 Gestion des composants de la fenêtre
*************************************/

/**
 * @brief MainWindow::setLbValue
 * @param v
 * affichage de la vitesse en fonction du curseur
 */
void MainWindow::setLbValue(int v){
    this->ui->lbSpeed->setText(QString::number(v));
}


/* ***********************************
            Autres
*************************************/

/**
 * @brief MainWindow::screenshot
 * capture d'écran du flux de la caméra
 */
void MainWindow::screenshot(){

    QPixmap capture = QPixmap();
    capture = QPixmap::grabWidget(this->ui->videoFrame);

    QString format = "png";
    QString path = QDir::currentPath() + tr("/capture.")+format;


    QString fileName = QFileDialog::getSaveFileName(this, tr("Save as"),
                                                    path,
                                                    tr("%1 Files (*.%2);;All Files(*)")
                                                    .arg(format.toUpper())
                                                    .arg(format));
    if(!fileName.isEmpty()){
        capture.save(fileName,format.toUtf8());
    }
}
