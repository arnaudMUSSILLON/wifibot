#ifndef CONTROLER_H
#define CONTROLER_H

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
    bool connect(QString address, int port);
    void disconnect();

public slots:
    void read();

private:
    QTcpSocket *socket;
    QByteArray* buffer;
};

#endif // CONTROLER_H