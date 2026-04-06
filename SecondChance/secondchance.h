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

    void on_SignInButton_clicked();
    void on_SignUpButton_clicked();
    void onEmailReturnPressed();
    void onParolaReturnPressed();
    void onNumeReturnPressed();
    void onPrenumeReturnPressed();
    void onNrTelefonReturnPressed();
    void onBioReturnPressed();
    void onSignInEmailReturnPressed();
    void onSignInPasswordPressed();

    void onEmailAdminReturnPressed();
    void onParolaAdminEmailPressed();
    void onCodPersonalEmailPressed();

    void on_SignIntoAppButton_clicked();

    void on_SignUpIntoApp_clicked();

    void on_SignInClientButton_clicked();

    void on_pushButton_clicked();

    void on_ChooseClientTypeButton_clicked();

    void on_BackButtonSU_clicked();

    void on_SignUpClientButton_clicked();

    void on_BackButtonSI_clicked();

    void on_ChooseAdminClientButton_clicked();

    void on_AdminSignInButton_clicked();

    void on_SignIntoAppButton_Admin_clicked();

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

    QLineEdit* emailLineEdit_admin;
    QLineEdit* parolaLineEdit_admin;
    QLineEdit* codPersonalEdit_admin;
};

