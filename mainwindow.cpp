#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  //    ui(new Ui::MainWindow)
{
    // Creating the vector of snake body
    Snake_body.append(Create_New_Button());
    Snake_body[0]->setGeometry(0,0,40,40);


    Snake_body[0]->setParent(this);
    Snake_body[0]->setText("H");
    Snake_body[0]->setStyleSheet( "background-color: black;border-radius:10%;");
    for(int i = 0; i <100;i++)
    {
        Snake_body.append(Create_New_Button());
        Snake_body[i+1]->setStyleSheet( "background-color: red;border-radius:10%; border-width:15px;border-style: solid; border-color:black;");
        Snake_body[i+1]->setParent(this);
        Snake_body[i+1]->setGeometry(1000,1000,40,40);
    }
    food = new QPushButton(this);
    food->setStyleSheet("QPushButton{ background-color:rgb(250,0,0); color:white; font-size: 17px; font-family: Arial;border-radius:20%; border-width:0.5px;border-style: solid; border-color:white;}");
    food->setGeometry(200,200,40,40);
    socket = new QTcpSocket(this);
    socket->connectToHost("127.0.0.1",8082);
    socket->bind();


}

QPushButton *MainWindow::Create_New_Button()
{
    QPushButton *new_button = new QPushButton();
    return new_button;
}

void MainWindow::Update(QPushButton * Snake_body_second, QPushButton * Snake_body_first)
{
    if(counter >1)
    {
        if(Snake_body[counter-1]->x() > Snake_body_first->x())
        {
            last_pressed = 'D';
        }else if(Snake_body[counter-1]->y() > Snake_body_first->y())
        {
            last_pressed = 'W';
        }else if(Snake_body[counter-1]->y() < Snake_body_first->y())
        {
            last_pressed = 'S';
        }else if(Snake_body[counter-1]->x() < Snake_body_first->x())
        {
            last_pressed = 'A';
        }
    }
    switch(last_pressed){
    case'D':
        Snake_body_second->setGeometry(Snake_body_first->x()-40,Snake_body_first->y(),Snake_body_first->width(),Snake_body_first->height());
        break;
    case'W':
        Snake_body_second->setGeometry(Snake_body_first->x(),Snake_body_first->y()+40,Snake_body_first->width(),Snake_body_first->height());
        break;
    case'A':
        Snake_body_second->setGeometry(Snake_body_first->x()+40,Snake_body_first->y(),Snake_body_first->width(),Snake_body_first->height());
        break;
    case'S':
        Snake_body_second->setGeometry(Snake_body_first->x(),Snake_body_first->y()- 40,Snake_body_first->width(),Snake_body_first->height());
        break;
    default:
        Snake_body_second->setGeometry(Snake_body_first->x(),Snake_body_first->y(),Snake_body_first->width(),Snake_body_first->height());
        break;
    }
    qDebug()<<"First snake x : "<<Snake_body_first->x()<< "Second snake x : "<<Snake_body_second->x();


}

void MainWindow::Follow()
{
    qDebug()<<"Follow is called";

    for(int i = counter;i >0;i--)
    {
        Snake_body[i]->setGeometry(Snake_body[i-1]->x(),Snake_body[i-1]->y(),Snake_body[i-1]->width(),Snake_body[i-1]->height());
    }

}
void MainWindow::keyPressEvent(QKeyEvent *event){


    switch(char(event->key()))
    {
    case 'D':
        socket->write("right1");
        qDebug()<<socket->waitForReadyRead(1000);
        Server_order =socket->readAll();
        if(Server_order == "RIGHT")
        {
            Follow();
            last_pressed = 'D';
            Snake_body[0]->setGeometry(Snake_body[0]->x()+Snake_body[0]->width(),Snake_body[0]->y(),Snake_body[0]->width(),Snake_body[0]->height());
            break;
        }


    case 'S':
        socket->write("down1");
        qDebug()<<socket->waitForReadyRead(1000);
        Server_order =socket->readAll();
        if(Server_order == "DOWN")
        {
            Follow();
            last_pressed = 'S';
            Snake_body[0]->setGeometry(Snake_body[0]->x(),Snake_body[0]->y() + 40,Snake_body[0]->width(),Snake_body[0]->height());
            break;
        }

    case 'W':
        socket->write("up1");
        qDebug()<<socket->waitForReadyRead(1000);
        Server_order =socket->readAll();
        if(Server_order == "UP")
        {
            Follow();
            last_pressed = 'W';
            Snake_body[0]->setGeometry(Snake_body[0]->x(),Snake_body[0]->y() - 40,Snake_body[0]->width(),Snake_body[0]->height());
            break;
        }
    case'A':
        socket->write("left1");
        qDebug()<<socket->waitForReadyRead(1000);
        Server_order =socket->readAll();
        if(Server_order == "LEFT")
        {
            Follow();
            last_pressed = 'A';
            Snake_body[0]->setGeometry(Snake_body[0]->x()-Snake_body[0]->width(),Snake_body[0]->y(),Snake_body[0]->width(),Snake_body[0]->height());
            break;
        }
    default:
        break;
    }

    if((Snake_body[0]->y()>560) && char(event->key()) == 'S')
    {
        Snake_body[0]->setGeometry(Snake_body[0]->x(),0,Snake_body[0]->width(),Snake_body[0]->height());
    }else if((Snake_body[0]->y()<0) && char(event->key()) == 'W')
    {
        Snake_body[0]->setGeometry(Snake_body[0]->x(),560,Snake_body[0]->width(),Snake_body[0]->height());
    }else if((Snake_body[0]->x()<0) && char(event->key()) == 'A')
    {
        Snake_body[0]->setGeometry(560,Snake_body[0]->y(),Snake_body[0]->width(),Snake_body[0]->height());
    }else if((Snake_body[0]->x() > 560) && char(event->key()) == 'D')
    {
        Snake_body[0]->setGeometry(0,Snake_body[0]->y(),Snake_body[0]->width(),Snake_body[0]->height());
    }
    if(Snake_body[0]->x() == food->x() && Snake_body[0]->y() == food->y())
    {
        qDebug()<<"Value for counter : "<<counter;
        Update(Snake_body[counter+1],Snake_body[counter]);
        counter++;
        food->setGeometry(40*(rand()%16),40* (rand()%16),40,40);
        qDebug()<<food->x()<<food->y();
    }

}

void MainWindow::move(int index)
{
    if(Snake_body[index]->x());
}


//QPushButton * Create_New_Button()
//{
//    QPushButton *new_button = new QPushButton();
//    return new_button;
//}




MainWindow::~MainWindow()
{
    delete ui;
}
