#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QKeyEvent>
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

private slots:
    void on_connectBtn_clicked();
    void on_disconnectBtn_clicked();

private:
    Ui::MainWindow *ui;
    Controler* c;
};

#endif // MAINWINDOW_H
