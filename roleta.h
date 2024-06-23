#ifndef ROLETA_H
#define ROLETA_H
#include <QWidget>
#include <QMainWindow>
#include <QStyle>
#include <QHostAddress>
#include "kontroler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Roleta;
}
QT_END_NAMESPACE

class Roleta : public QMainWindow
{
    Q_OBJECT

public:
    Roleta(QWidget *parent = nullptr);
    ~Roleta();

private slots:


    void roletaConnected();
    void roletaDisconnected();
    void roletaStateChanged(QAbstractSocket::SocketState);
    void roletaErrorOccurred(QAbstractSocket::SocketError);
    void roletaDataReady(QByteArray data);
    void action(QByteArray data);
    void rollDown();
    void rollUp();
private:
    Ui::Roleta *ui;
    Kontroler kontroler;
    QString status="Up";


    void setKontroler();
};
#endif // ROLETA_H
