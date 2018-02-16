#include "mainwindow.h"
#include <QApplication>
#include "wifibot.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Wifibot *wb = new Wifibot();

    return a.exec();
}
