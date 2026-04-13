#pragma once // Previne redefinirea clasei (eroarea ta veche)

#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(int ID, QObject *parent = nullptr);
    ~MyThread();

protected:
    void run() override;

private slots:
    void readyRead();
    void disconnected();

signals:

    void dataReceived(QByteArray data);

private:
    qintptr socketDescriptor;
    QTcpSocket *socket;
};
