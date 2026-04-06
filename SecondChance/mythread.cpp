#include "mythread.h"

MyThread::MyThread(int ID, QObject *parent) : QThread(parent)
{
    this->socketDescriptor = ID;
}

MyThread::~MyThread()
{
    qInfo() << "Thread distrus pentru descriptorul:" << socketDescriptor;
}

void MyThread::run()
{
    qDebug() << socketDescriptor << " Starting thread";

    socket = new QTcpSocket();

    if (!socket->setSocketDescriptor(this->socketDescriptor))
    {
        qDebug() << "Eroare la setarea descriptorului!";
        delete socket;
        return;
    }

    // Conexiunile standard din Qt vor rula automat pe acest thread
    connect(socket, &QTcpSocket::readyRead, this, &MyThread::readyRead);
    connect(socket, &QTcpSocket::disconnected, this, &MyThread::disconnected);

    qDebug() << "Client conectat cu succes pe thread.";

    // Pornește bucla de evenimente a thread-ului (esențială pentru semnale/sloturi)
    exec();
}

void MyThread::readyRead()
{
    QByteArray data = socket->readAll();
    qDebug() << "Date primite pe thread:" << data;

    emit dataReceived(data);  // trimite datele către alt obiect/thread

    socket->write(data); // dacă vrei să faci echo
}

void MyThread::disconnected()
{
    qDebug() << "Clientul s-a deconectat.";
    socket->deleteLater();

    quit();
}
