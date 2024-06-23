#include "roleta.h"
#include "ui_roleta.h"
#include <QWidget>
#include <QPropertyAnimation>
#include <QMetaEnum>
#include <QMessageBox>
#include <QDebug>

Roleta::Roleta(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Roleta)
{
    ui->setupUi(this);
    if(kontroler.currentState()==QAbstractSocket::ConnectedState)
        kontroler.disconnectFromServer();
    else{
        auto ip="127.0.0.1";
        auto port=12345;
        kontroler.connectWithServer(ip,port);
    }
    auto message = "Roleta";
    kontroler.send(message);
    setKontroler();

}

Roleta::~Roleta()
{
    delete ui;
}



void Roleta::roletaConnected()
{

}

void Roleta::roletaDisconnected()
{

}

void Roleta::roletaStateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();


}

void Roleta::roletaErrorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketError>();

}

void Roleta::roletaDataReady(QByteArray data)
{

}

void Roleta::action(QByteArray data)
{
    QString command= QString(data);
    if(command=="Down" && status != "Down"){
        rollDown();
        status="Down";
    }
    else if(command=="Up" && status !="Up"){
        rollUp();
        //QMessageBox::critical(this, "Tytuł komunikatu", "To jest komunikat błędu.");

        status="Up";
    }
}

void Roleta::rollUp()
{
    QPropertyAnimation *animation1 = new QPropertyAnimation(ui->rol, "geometry");
    animation1->setDuration(2000); // 2 seconds
    animation1->setStartValue(QRect(ui->win->x(), ui->win->y(), ui->win->width(), ui->win->height()));
    animation1->setEndValue(QRect(ui->rol->x(), ui->rol->y(), ui->win->width(), ui->rol->height()-600));
    animation1->start();
}
//ui->win->x(), ui->win->y(), ui->win->width(), ui->win->height()

void Roleta::rollDown()
{
    QPropertyAnimation *animation = new QPropertyAnimation(ui->rol, "geometry");
    animation->setDuration(2000); // 2 seconds
    animation->setStartValue(QRect(ui->rol->x(), ui->rol->y(), ui->rol->width(), ui->rol->height()));
    animation->setEndValue(QRect(ui->rol->x(), ui->win->y(), ui->rol->width(), ui->win->height()));
    animation->start();
}

void Roleta::setKontroler()
{
    connect(&kontroler,&Kontroler::connected,this, &Roleta::roletaConnected);
    connect(&kontroler,&Kontroler::disconnected,this, &Roleta::roletaDisconnected);
    connect(&kontroler,&Kontroler::stateChanged,this, &Roleta::roletaStateChanged);
    connect(&kontroler,&Kontroler::errorOccurred,this, &Roleta::roletaErrorOccurred);
    connect(&kontroler,&Kontroler::dataReady,this, &Roleta::roletaDataReady);
    connect(&kontroler,&Kontroler::dataReady,this, &Roleta::action);


}
