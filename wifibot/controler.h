#ifndef CONTROLER_H
#define CONTROLER_H

//#include "controler.moc"
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
    short Crc16(unsigned char *Adresse_tab , unsigned char Taille_max);
    struct Capteur{
        quint16 speedL;     //speed left wheels
        quint16 speedR;     //speed right wheels
        quint8 battery;
        quint8 power;
        quint8 c1;
        quint8 c2;
        quint8 c3;
        quint8 c4;
    };

public slots:
    void read();

private:
    QTcpSocket *socket;
    QByteArray* buffer;
    Capteur capteur;
};

#endif // CONTROLER_H
