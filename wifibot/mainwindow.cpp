#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow * MainWindow::mainW = nullptr;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainW = this;
    QMainWindow::setFocus();
    this->ui->upArrowBtn->setArrowType(Qt::UpArrow);
    this->ui->downArrowBtn->setArrowType(Qt::DownArrow);
    this->ui->rightArrowBtn->setArrowType(Qt::RightArrow);
    this->ui->leftArrowBtn->setArrowType(Qt::LeftArrow);
    this->ui->capteursFrame->setVisible(false);
    this->ui->videoFrame->setVisible(false);
    this->c= new Controler();
    this->cameraControler = new QNetworkAccessManager();
    connect(this->ui->speedSlider,SIGNAL(valueChanged(int)),SLOT(setLbValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* *************************************************************************
                                Gestion des boutons
****************************************************************************/

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
        if(c->askConnection(ip,port)){

            this->ui->capteursFrame->setVisible(true);
            this->ui->videoFrame->setVisible(true);
            QString source = "http://"+ui->tfAddress->text()+":8080/javascript_simple.html";
            this->ui->videoFrame->setVisible(true);
            this->ui->videoFrame->load(QUrl(source));
            this->ui->videoFrame->setZoomFactor(1.4);
            this->ui->videoFrame->setStyleSheet("background-color:#ffffff;");
            this->ui->videoFrame->show();
        }
    }
}

/**
 * @brief MainWindow::on_disconnectBtn_clicked
 * Gestion de la déconnexion au clic du bouton
 */
void MainWindow::on_disconnectBtn_clicked()
{
    c->disconnect();
    this->ui->videoFrame->stop();
    this->ui->videoFrame->setVisible(false);
    this->ui->capteursFrame->setVisible(false);
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
 * assignement des boutons aux touches
 */
void::MainWindow::keyPressEvent(QKeyEvent *event){
    switch(event->key()){
    case Qt::Key_Z:
        ui->zBtn->animateClick();
        isPressedZ = true;
        break;

    case Qt::Key_S:
        ui->sBtn->animateClick();
        isPressedS = true;
        break;

    case Qt::Key_D:
        ui->dBtn->animateClick();
        isPressedD= true;
        break;

    case Qt::Key_Q:
        isPressedQ = true;
        ui->qBtn->animateClick();
        break;

    case Qt::Key_Up:
        ui->upArrowBtn->animateClick();
        break;

    case Qt::Key_Down:
        ui->downArrowBtn->animateClick();
        break;

    case Qt::Key_Left:
        ui->leftArrowBtn->animateClick();
        break;

    case Qt::Key_Right:
        ui->rightArrowBtn->animateClick();
        break;
    }
    updateMove();
}


/* ************************************************************************
                                Gestion du mouvement
***************************************************************************/
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
        isPressedQ = false;
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

/**
 * @brief MainWindow::updateMove
 * Gestion du mouvement du robot
 */
void MainWindow::updateMove(){ 
    int vitesse = this->ui->speedSlider->value();
    if(isPressedZ && !isPressedQ && !isPressedS && !isPressedD){
        c->move(vitesse, vitesse, 1);
    }else if(!isPressedZ && isPressedQ && !isPressedS && !isPressedD){
        c->move(vitesse, vitesse, 3);
    }else if(!isPressedZ && !isPressedQ && isPressedS && !isPressedD){
        c->move(vitesse, vitesse, 4);
    }else if(!isPressedZ && !isPressedQ && !isPressedS && isPressedD){
        c->move(vitesse, vitesse, 2);
    }
    else{
        c->move(0,0,5);
    }
}

MainWindow *MainWindow::mainWindowPtr()
{
    return mainW;
}

/* **************************************************************
                Gestion des composants de la fenêtre
*****************************************************************/

/**
 * @brief MainWindow::setLbValue
 * @param v
 * affichage de la vitesse en fonction du curseur
 */
void MainWindow::setLbValue(int v){
    this->ui->lbSpeed->setText(QString::number(v));
}

/****BATTERIE ******/

/**
 * @brief MainWindow::updateBValue
 * @param batterie
 * maj de la valeur de la batterie du robot
 */
void MainWindow::updateBValue(unsigned char batterie){
    if(batterie>100){
        this->ui->pbBatterie->setValue(100);
    }
    else{
        this->ui->pbBatterie->setValue(batterie);
    }
}

/******* CAPTEURS *******/

/**
 * @brief MainWindow::updateFLValue
 * @param fL
 * maj de la valeur du capteur avant gauche
 */
void MainWindow::updateFLValue(unsigned char fL){
    if(fL>100){
        this->ui->frontLeft->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #ff6600;width: 20px;}");
    }
    else if(fL<100 && fL>50){
        this->ui->frontLeft->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #ff0000;width: 20px;}");
    }
    else{
        this->ui->frontLeft->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #00ff00;width: 20px;}");
    }
}

/**
 * @brief MainWindow::updateRLValue
 * @param fR
 * maj de la valeur du capteur aavant droit
 */
void MainWindow::updateFRValue(unsigned char fR){
    if(fR>100){
        this->ui->frontRight->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #ff6600;width: 20px;}");
    }
    else if(fR<100 && fR>50){
        this->ui->frontRight->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #ff0000;width: 20px;}");
    }
    else{
        this->ui->frontRight->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #00ff00;width: 20px;}");
    }
}

/**
 * @brief MainWindow::updateBLValue
 * @param bL
 * maj de la valeur du capteur arrière gauche
 */
void MainWindow::updateBLValue(unsigned char bL){
    if(bL>100){
        this->ui->backLeft->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #ff6600;width: 20px;}");
    }
    else if(bL<100 && bL>50){
        this->ui->backLeft->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #ff0000;width: 20px;}");
    }
    else{
        this->ui->backLeft->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #00ff00;width: 20px;}");
    }
}

/**
 * @brief MainWindow::updateBRValue
 * @param bR
 * maj de la valeur du capteur arrière droit
 */
void MainWindow::updateBRValue(unsigned char bR){
    if(bR>100){
        this->ui->backRight->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #ff0000;width: 20px;}");
    }
    else if(bR<100 && bR>50){
        this->ui->backRight->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #ff6600;width: 20px;}");
    }
    else{
        this->ui->backRight->setStyleSheet("QProgressBar {border: 2px solid grey; border-radius: 5px;text-align:center;}QProgressBar::chunk {background-color: #00ff00;width: 20px;}");
    }
}

/**
 * @brief MainWindow::updateCValue
 */
void MainWindow::updateCValue(unsigned char fL, unsigned char fR, unsigned char bL, unsigned char bR){
    updateFLValue(fL);
    this->ui->frontLeft->setValue(fL);
    updateFRValue(fR);
    this->ui->frontRight->setValue(fR);
    updateBLValue(bL);
    this->ui->backLeft->setValue(bL);
    updateBRValue(bR);
    this->ui->backRight->setValue(bR);
}

/* ***************************************************************
                            Autres
******************************************************************/

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

