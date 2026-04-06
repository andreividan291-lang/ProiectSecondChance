#define PRODUS_H

#include <QUuid>
#include <QCryptographicHash>
#include <QRegularExpression>
#include <QTcpServer>
#include <QDebug>
#include <QList>
#include "mythread.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "utilizator.h"
#include "myexception.h"

class Produs
{

protected:

    static int IndexInApp;
    int indexProduct;

    QString titleProduct;
    QString descriptionProduct;



public:
    Produs();
};

