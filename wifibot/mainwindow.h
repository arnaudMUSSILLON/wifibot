#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
#include <QWebEngineView>
#include "controler.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);
    void updateMove();

private slots:
    void on_connectBtn_clicked();
    void on_disconnectBtn_clicked();

private:
    Ui::MainWindow *ui;
    Controler* c;

    bool isPressedZ = false;
    bool isPressedQ = false;
    bool isPressedS = false;
    bool isPressedD = false;

};

#endif // MAINWINDOW_H
