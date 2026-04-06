#pragma once
#define UTILIZATOR_H

#include "generalaccount.h"
#include <QString>

class Utilizator : public GeneralAccount
{


protected:

public:

    Utilizator(QString e, QString p,QString n, QString pn, QString t, QString b = NULL):GeneralAccount(e,p,n,pn,t,b){};
    ~Utilizator(){};

};

