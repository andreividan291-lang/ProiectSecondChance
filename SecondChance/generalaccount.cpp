#include "generalaccount.h"


GeneralAccount::GeneralAccount(QString e, QString p, QString n, QString pn, QString t, QString b)
{
    Email=e;
    Parola=p;
    Nume=n;
    Prenume=pn;
    NrTelefon=t;
    Bio=b;
}

QString GeneralAccount::getEmail() const
{
    return Email;
}

QString GeneralAccount::getParola() const
{
    return Parola;
}
