#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#define CAM_UP "/?action=command&dest=0&plugin=0&id=10094853&group=1&value=-200"
#define CAM_DOWN "/?action=command&dest=0&plugin=0&id=10094853&group=1&value=200"
#define CAM_LEFT "/?action=command&dest=0&plugin=0&id=10094852&group=1&value=200"
#define CAM_RIGHT "/?action=command&dest=0&plugin=0&id=10094852&group=1&value=-200"

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
    void keyReleaseEvent(QKeyEvent *event);
    void updateMove();
    QNetworkAccessManager *cameraControler;

private slots:
    void on_connectBtn_clicked();
    void on_disconnectBtn_clicked();
    void on_upArrowBtn_pressed();
    void on_downArrowBtn_pressed();
    void on_leftArrowBtn_pressed();
    void on_rightArrowBtn_pressed();
    void screenshot();
    void on_captureBtn_clicked();

private:
    Ui::MainWindow *ui;
    Controler* c;
    bool isPressedZ = false;
    bool isPressedQ = false;
    bool isPressedS = false;
    bool isPressedD = false;

};

#endif // MAINWINDOW_H
