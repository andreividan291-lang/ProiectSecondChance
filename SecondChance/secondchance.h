#ifndef SECONDCHANCE_H
#define SECONDCHANCE_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QRegularExpression>
#include "servermanager.h"

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
    // Navigare
    void on_SignInButton_clicked();
    void on_SignUpButton_clicked();
    void on_SignInClientButton_clicked();
    void on_SignUpClientButton_clicked();
    void on_ChooseClientTypeButton_clicked();
    void on_BackButtonSU_clicked();
    void on_BackButtonSI_clicked();
    void on_ChooseAdminClientButton_clicked();
    void on_AdminSignInButton_clicked();
    void on_BackToUserType_clicked();
    void on_BackButtonSI_Admin_clicked();
    void on_FromAdminSignInToAccountType_clicked();
    void on_Create_Product_clicked();
    void on_pushButton_clicked();

    // Actiuni Logica
    void on_SignIntoAppButton_clicked();
    void on_SignUpIntoApp_clicked();
    void on_SignIntoAppButton_Admin_clicked();
    void on_CreateProductDoneButton_clicked();

    // Focus / Return Pressed
    void onEmailReturnPressed();
    void onParolaReturnPressed();
    void onNumeReturnPressed();
    void onPrenumeReturnPressed();
    void onNrTelefonReturnPressed();
    void onBioReturnPressed();
    void onSignInEmailReturnPressed();
    void onSignInPasswordPressed() { signInParolaEdit->clearFocus(); }
    void onEmailAdminReturnPressed();
    void onParolaAdminEmailPressed();
    void onCodPersonalEmailPressed();
    void onCreateProductTitleReturnPressed();
    void onCreateProductDescriptionReturnPressed();
    void onCreateProductPriceReturnPressed();
    void onCreateProductCategoryReturnPressed();
    void onCreateProductLocationReturnPressed();
    void onCreateProductDateReturnPressed();

private:
    Ui::SecondChance *ui;

    // Pointeri UI - Sign Up
    QLineEdit *emailLineEdit, *parolaLineEdit, *numeLineEdit, *prenumeLineEdit;
    QLineEdit *nrTelefonLineEdit, *bioLineEdit;

    // Pointeri UI - Sign In
    QLineEdit *signInEmailEdit, *signInParolaEdit;

    // Pointeri UI - Admin
    QLineEdit *emailLineEdit_admin, *parolaLineEdit_admin, *codPersonalEdit_admin;

    // Pointeri UI - Produs
    QLineEdit *createProductTitleLineEdit, *createProductDescriptionLineEdit;
    QLineEdit *createProductPriceLineEdit, *createProductCategoryLineEdit;
    QLineEdit *createProductLocationLineEdit, *createProductDateLineEdit;

    // Helper-e de validare vizuala
    void setFieldError(QLineEdit* field, const QString& tooltip = "");
    void setFieldOk(QLineEdit* field);
    void clearFieldState(QLineEdit* field);
    bool validateSignUpFields();
    bool validateSignInFields();
    bool validateAdminFields();
    bool validateProductFields();

    // Conectare semnale de stergere erori la modificare text
    void connectClearOnType(QLineEdit* field);
};

#endif // SECONDCHANCE_H
