#ifndef CONTROLER_H
#define CONTROLER_H

#include <QTimer>
#include <QtNetwork>
#include <QObject>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>
#include <QByteArray>

class Controler : public QObject
{
    Q_OBJECT
public:
    explicit Controler(QObject *parent = 0);
    bool askConnection(QString address, int port);
    void disconnect();
    void move(int vitesseG, int vitesseD, int direction);
    short Crc16(unsigned char *Adresse_tab , unsigned char Taille_max);
    struct Capteur{
        quint16 vitesseG;     //speed left wheels
        quint16 vitesseD;     //speed right wheels
        quint8 batterie;
        quint8 courant;
        quint8 c1;
        quint8 c2;
        quint8 c3;
        quint8 c4;
    };

public slots:
    void whenConnected();
    void receiveData();
    void sendData();
    void whenBytesWritten(qint64 bytes);

private:
    QTcpSocket *socket;
    QByteArray* buffer;
    Capteur capteur;
    QTimer* timer;
    QTimer* timer2;
};

#endif // CONTROLER_H
