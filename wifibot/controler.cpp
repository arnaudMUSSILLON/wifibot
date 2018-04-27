#include "controler.h"

Controler::Controler(QObject *parent) : QObject(parent)
{
    socket = new QTcpSocket();
    QObject::connect(socket, SIGNAL(read()),this, SLOT(read()));    //Creates a connection of the given type from the signal in the sender object
    buffer = new QByteArray();
}

bool Controler::connect(QString address, int port){
    bool res = false;
    QHostAddress a = QHostAddress(address);   //transform the string into IPV4 address
    socket->connectToHost(a, port);     //connexion to remote host
    if(socket->waitForConnected(1000)){     //waiting 1 second for a response
            res = true;
    }
    return res;
}


/**
 * @brief Controler::disconnect
 * Disconnection form the robot
 */
void Controler::disconnect(){
    socket->disconnectFromHost();
}


/**
 * @brief Controler::read
 * Reading of the data send by the robot after the connection
 */
void Controler::read(){
    qDebug() << "Connection successful";
    qDebug() << socket->readAll();      //Read all data from the socket
}

