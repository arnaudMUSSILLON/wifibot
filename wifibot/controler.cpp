#include "controler.h"
#include "mainwindow.h"
Controler::Controler(QObject *parent) : QObject(parent)
{
    this->buffer = new QByteArray();

    //Envoie régulier du buffer pour la gestion du robot
    timer = new QTimer(this);
    timer->setInterval(25);
    connect(timer, SIGNAL(timeout()),this,SLOT(sendData()));

    //Timer pour la lecture des informations
    timer2 = new QTimer(this);
    timer2->setInterval(250);
    connect(timer2, SIGNAL(timeout()),this, SLOT(receiveData()));
}


/***************************************************************
                        CONNEXION AU ROBOT
****************************************************************/

/**
 * @brief Controler::connect
 * Connection to the robot (require an address and a port)
 * @param address
 * @param port
 * @return
 */
bool Controler::askConnection(QString address, int port){
    bool res = false;
    qDebug() << "Tentative de connexion ...";
    //Create new socket
    socket = new QTcpSocket();

    //binding events
    connect(socket, SIGNAL(connected()),this, SLOT(whenConnected()));
    //connect(socket, SIGNAL(bytesWritten(qint64)),this, SLOT(whenBytesWritten(qint64)));

    socket->connectToHost(address, port);     //connexion to remote host
    if(socket->waitForConnected(5000)){     //waiting 1 second for a response
        timer->start();
        timer2->start();
        move(0,0,5);
        socket->write(*this->buffer);
        res = true;
    }
    else{
        qDebug("Erreur : la connexion a échoué");
    }
    return res;
}

/**
 * @brief Controler::disconnect
 * Disconnection form the robot
 */
void Controler::disconnect(){
    socket->disconnectFromHost();
    qDebug("Deconnexion : OK");
    timer->stop();
    this->buffer->clear();
    timer2->stop();
}

void Controler::whenConnected(){
    qDebug() << "Connexion réussie";
}

/***************************************************************
                        MANIPULATION DES DONNEES
****************************************************************/

/**
 * @brief Controler::sendData
 * envoi des données
 */
void Controler::sendData(){
    this->socket->write(*this->buffer);
}

/**
 * @brief Controler::read
 * Reading of the data send by the robot after the connection
 */
void Controler::receiveData(){
    qDebug() << "Lecture des données en cours";
    QByteArray data = socket->readAll();
    capteur.batterie = data[2];
    capteur.c1 = data[3]; //capteur avant gauche
    capteur.c2 = data[11]; //capteur avant droit
    capteur.c3 = data[12]; //capteur arrière gauche
    capteur.c4 = data[4]; // capteur arrière droit
    MainWindow* mw = MainWindow::mainWindowPtr();
    mw->updateBValue(capteur.batterie);
    mw->updateCValue(capteur.c1,capteur.c2,capteur.c3,capteur.c4);

    qDebug() << "Batterie" << capteur.batterie;
    qDebug() << "Capteur avant gauche" << capteur.c1;
    qDebug() << "Capteur avant droit" << capteur.c2;
}

short Controler::Crc16(unsigned char *Adresse_tab , unsigned char Taille_max)
{
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;

    for (CptOctet = 1; CptOctet < Taille_max ; CptOctet++)
    {
        Crc ^= *( Adresse_tab + CptOctet);
        for ( CptBit = 0; CptBit <= 7 ; CptBit++)
        {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}

void Controler::whenBytesWritten(qint64 bytes){
    qDebug() << bytes << " octets écrits...";
}


/***************************************************************
                        DEPLACEMENT DU ROBOT
****************************************************************/

/**
 * @brief Controler::veuillezRouler donne les instructions au robot
 * @param vitesseG
 * @param vitesseD
 */
void Controler::move(int vitesseG, int vitesseD, int direction){
    //La vitesse doit être entre 0 et 240
    this->buffer->clear();
    this->buffer->append((char)255);        // Char1 (255)
    this->buffer->append(0x07);       // Char2 (0x07)
    this->buffer->append((char)vitesseG);  // Char3 leftspeed control
    this->buffer->append(1);          // Char4 leftspeed control
    this->buffer->append((char)vitesseD); // Char5 rightspeed control
    this->buffer->append(1);          // Char6 rightspeed control
    if(direction == 4){
        buffer->append((char) 0b00000000);     //recule
    }else if(direction==1){
        buffer->append((char) 0b01010000);     //avance
    }else if(direction == 2){
        buffer->append((char) 0b01000000);     //droite
    }else if(direction == 3){
        buffer->append((char) 0b00010000);     //gauche
    }
    if(direction==1 || direction==2 || direction==3 || direction==4){
        // Les octets 8 et 9 correspondent au crc
        unsigned short crc = Crc16((unsigned char* )buffer->constData(), buffer->length());
        this->buffer->append(crc);
        this->buffer->append((crc>>8));
    }

    /*char octet;
    for(int i=0; i<=8; i++){
        octet = buffer->at(i);
        for(int j=8; j>=0; j--){
            qDebug() << ((octet >> j)&1);
        }
        qDebug() << "\n";
    }*/
}

qint8 Controler::getBatterie(){
    return this->capteur.batterie;
}
