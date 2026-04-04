#pragma once
#define UTILIZATOR_H

#include <QString>

class Utilizator
{

protected:

    QString Email;
    QString Parola;
    QString Nume;
    QString Prenume;
    QString NrTelefon;
    QString Bio;

public:

    Utilizator(QString e, QString p,QString n, QString pn, QString t, QString b = NULL);


    QString getEmail() const { return Email; }
    QString getParola() const { return Parola; }

    void setEmail(const QString& e) { Email = e; }
    void setParola(const QString& p) { Parola = p; }


};

