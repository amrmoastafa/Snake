#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QDebug"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QVBoxLayout"
#include "QGraphicsEllipseItem"
#include "QPushButton"
#include <QMainWindow>
#include "QString"
#include "QKeyEvent"
#include <QVector>
#include "cstdlib"
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString Server_order;
    QPushButton *Temp;
    QPushButton *food;
    QVector <QPushButton *> Snake_body;
    QPushButton * Create_New_Button();
    void Update(QPushButton * Snake_body_second, QPushButton * Snake_body_first);
    void Follow();
    int counter;
    char last_pressed;
    void moveByServer(QString order);
    QTcpSocket *socket;
    ~MainWindow();



protected:
    void keyPressEvent(QKeyEvent *event);


public slots:
    void move(int index);


private:

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
