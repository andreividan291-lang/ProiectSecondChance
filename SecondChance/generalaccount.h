#define GENERALACCOUNT_H

#include <QString>

class GeneralAccount
{

protected:

    QString Email;
    QString Parola;
    QString Nume;
    QString Prenume;
    QString NrTelefon;
    QString Bio;

public:
    GeneralAccount(QString e, QString p,QString n, QString pn, QString t, QString b = NULL);
    virtual ~GeneralAccount() = default;
    QString getEmail() const;
    QString getParola() const;
};

