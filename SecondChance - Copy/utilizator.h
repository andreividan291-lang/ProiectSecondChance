#pragma once
#define UTILIZATOR_H

#include <QString>

class Utilizator
{

protected:

    QString Email;
    QString Parola;

public:

    Utilizator(QString e, QString p);


    QString getEmail() const { return Email; }
    QString getParola() const { return Parola; }

    void setEmail(const QString& e) { Email = e; }
    void setParola(const QString& p) { Parola = p; }


};

