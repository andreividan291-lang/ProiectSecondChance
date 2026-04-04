#define SECONDCHANCE_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include "utilizator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class SecondChance; }
QT_END_NAMESPACE

class SecondChance : public QMainWindow
{
    Q_OBJECT

public:
    SecondChance(QWidget *parent = nullptr);
    ~SecondChance();

private slots:
    void on_LogInButton_clicked();    // pentru trecere la page_2
    void on_SignUpButton_clicked();  // pentru trecere la page_3
    void onEmailReturnPressed();
    void onParolaReturnPressed();
    void onNumeReturnPressed();
    void onPrenumeReturnPressed();
    void onNrTelefonReturnPressed();
    void onBioReturnPressed();
    void onSignInEmailReturnPressed();
    void onSignInPasswordPressed();


    void on_DoneButton_clicked();

    void on_SignInAppButton_clicked();

private:

    Ui::SecondChance *ui;
    int counter;

    QLineEdit* emailLineEdit;
    QLineEdit* parolaLineEdit;
    QLineEdit* numeLineEdit;
    QLineEdit* prenumeLineEdit;
    QLineEdit* nrTelefonLineEdit;
    QLineEdit* bioLineEdit;
    QLineEdit* signInEmailEdit;
    QLineEdit* signInParolaEdit;
};

