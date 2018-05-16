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
    connect(socket, SIGNAL(disconnected()),this, SLOT(write()));
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


void Controler::write(){
    qDebug() << socket->write("Demande de connexion");      //Read all data from the socket
}

/**
 * @brief Controler::read
 * Reading of the data send by the robot after the connection
 */
void Controler::read(){
    qDebug() << "Lecture des données en cours";
    qDebug() << socket->readAll();      //Read all data from the socket
}


