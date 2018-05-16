#include "controler.h"

Controler::Controler(QObject *parent) : QObject(parent)
{
    buffer = new QByteArray();
}

/**
 * @brief Controler::connect
 * Connection to the robot (require an address and a port)
 * @param address
 * @param port
 * @return
 */
bool Controler::askConnection(QString address, int port){
    bool res = false;

    //Create new socket
    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(connected()),this, SLOT(read()));    //Creates a connection of the given type from the signal in the sender object
    //connect(socket, SIGNAL(disconnected()),this, SLOT(write()));
    //QHostAddress a = QHostAddress(address);   //transform the string into IPV4 address
    socket->connectToHost(address, port);     //connexion to remote host
    if(socket->waitForConnected(5000)){     //waiting 1 second for a response
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
}

/**
 * @brief Controler::read
 * Reading of the data send by the robot after the connection
 */
void Controler::read(){
    qDebug() << "Lecture des données en cours";
    QDataStream Capteur(this->socket);
}


short Controler::Crc16(unsigned char *Adresse_tab , unsigned char Taille_max) {
    unsigned int Crc = 0xFFFF;
    unsigned int Polynome = 0xA001;
    unsigned int CptOctet = 0;
    unsigned int CptBit = 0;
    unsigned int Parity= 0;
    Crc = 0xFFFF;
    Polynome = 0xA001;
    for ( CptOctet= 0 ; CptOctet < Taille_max ; CptOctet++) {
        Crc ^= *( Adresse_tab + CptOctet);
        for ( CptBit = 0; CptBit <= 7 ; CptBit++) {
            Parity= Crc;
            Crc >>= 1;
            if (Parity%2 == true) Crc ^= Polynome;
        }
    }
    return(Crc);
}
