/********************************************************************************
** Form generated from reading UI file 'secondchance.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECONDCHANCE_H
#define UI_SECONDCHANCE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SecondChance
{
public:
    QWidget *centralwidget;
    QFormLayout *formLayout;
    QStackedWidget *stackedWidget;
    QWidget *SignIn_UpPageClient;
    QPushButton *SignInClientButton;
    QPushButton *SignUpClientButton;
    QWidget *AdminSignUpPage;
    QWidget *ChooseAccountTypePage;
    QPushButton *ChooseClientTypeButton;
    QPushButton *ChooseAdminClientButton;
    QWidget *AdminSignInUpPage;
    QPushButton *AdminSignInButton;
    QLabel *label_12;
    QWidget *PaginaAplicatieAdmin;
    QLabel *label_16;
    QWidget *AdminSignInPage;
    QLabel *label_13;
    QLabel *StatusSignUpLabelSignIn_Admin;
    QLabel *label_14;
    QLabel *label_15;
    QPushButton *SignIntoAppButton_Admin;
    QLineEdit *InsertPasswordBoxSi_Admin;
    QPushButton *BackButtonSI_Admin;
    QLineEdit *InsertEmailBoxSI_Admin;
    QLabel *label_17;
    QLineEdit *InsertPersonalCodeBox;
    QWidget *SignUpClient;
    QPushButton *SignUpIntoApp;
    QLineEdit *InsertEmailBoxSU;
    QLineEdit *InsertPasswordBoxSU;
    QLabel *StatusSignUpLabelSU;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *InsertNumeBoxSU;
    QLineEdit *InsertPrenumeBoxSU;
    QLineEdit *InsertNrTelefonBoxSU;
    QLineEdit *InsertBioBoxSU;
    QLabel *label_7;
    QPushButton *BackButtonSU;
    QWidget *PaginaPrincipalaMagazinClient;
    QLabel *label_8;
    QWidget *SignInClient;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *StatusSignUpLabelSignIn;
    QPushButton *SignIntoAppButton;
    QLineEdit *InsertEmailBoxSI;
    QLineEdit *InsertPasswordBoxSi;
    QPushButton *BackButtonSI;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SecondChance)
    {
        if (SecondChance->objectName().isEmpty())
            SecondChance->setObjectName("SecondChance");
        SecondChance->resize(546, 600);
        SecondChance->setMaximumSize(QSize(800, 600));
        centralwidget = new QWidget(SecondChance);
        centralwidget->setObjectName("centralwidget");
        formLayout = new QFormLayout(centralwidget);
        formLayout->setObjectName("formLayout");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setMinimumSize(QSize(441, 0));
        SignIn_UpPageClient = new QWidget();
        SignIn_UpPageClient->setObjectName("SignIn_UpPageClient");
        SignInClientButton = new QPushButton(SignIn_UpPageClient);
        SignInClientButton->setObjectName("SignInClientButton");
        SignInClientButton->setGeometry(QRect(230, 90, 80, 18));
        SignUpClientButton = new QPushButton(SignIn_UpPageClient);
        SignUpClientButton->setObjectName("SignUpClientButton");
        SignUpClientButton->setGeometry(QRect(230, 130, 80, 18));
        stackedWidget->addWidget(SignIn_UpPageClient);
        AdminSignUpPage = new QWidget();
        AdminSignUpPage->setObjectName("AdminSignUpPage");
        stackedWidget->addWidget(AdminSignUpPage);
        ChooseAccountTypePage = new QWidget();
        ChooseAccountTypePage->setObjectName("ChooseAccountTypePage");
        ChooseAccountTypePage->setEnabled(true);
        ChooseClientTypeButton = new QPushButton(ChooseAccountTypePage);
        ChooseClientTypeButton->setObjectName("ChooseClientTypeButton");
        ChooseClientTypeButton->setGeometry(QRect(220, 100, 80, 18));
        ChooseAdminClientButton = new QPushButton(ChooseAccountTypePage);
        ChooseAdminClientButton->setObjectName("ChooseAdminClientButton");
        ChooseAdminClientButton->setGeometry(QRect(220, 140, 80, 18));
        stackedWidget->addWidget(ChooseAccountTypePage);
        AdminSignInUpPage = new QWidget();
        AdminSignInUpPage->setObjectName("AdminSignInUpPage");
        AdminSignInButton = new QPushButton(AdminSignInUpPage);
        AdminSignInButton->setObjectName("AdminSignInButton");
        AdminSignInButton->setGeometry(QRect(190, 130, 80, 18));
        label_12 = new QLabel(AdminSignInUpPage);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(190, 80, 181, 16));
        stackedWidget->addWidget(AdminSignInUpPage);
        PaginaAplicatieAdmin = new QWidget();
        PaginaAplicatieAdmin->setObjectName("PaginaAplicatieAdmin");
        label_16 = new QLabel(PaginaAplicatieAdmin);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(150, 90, 221, 16));
        stackedWidget->addWidget(PaginaAplicatieAdmin);
        AdminSignInPage = new QWidget();
        AdminSignInPage->setObjectName("AdminSignInPage");
        label_13 = new QLabel(AdminSignInPage);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(96, 160, 121, 20));
        StatusSignUpLabelSignIn_Admin = new QLabel(AdminSignInPage);
        StatusSignUpLabelSignIn_Admin->setObjectName("StatusSignUpLabelSignIn_Admin");
        StatusSignUpLabelSignIn_Admin->setGeometry(QRect(130, 190, 261, 20));
        label_14 = new QLabel(AdminSignInPage);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(96, 130, 121, 20));
        label_15 = new QLabel(AdminSignInPage);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(190, 70, 251, 16));
        SignIntoAppButton_Admin = new QPushButton(AdminSignInPage);
        SignIntoAppButton_Admin->setObjectName("SignIntoAppButton_Admin");
        SignIntoAppButton_Admin->setGeometry(QRect(210, 220, 80, 18));
        InsertPasswordBoxSi_Admin = new QLineEdit(AdminSignInPage);
        InsertPasswordBoxSi_Admin->setObjectName("InsertPasswordBoxSi_Admin");
        InsertPasswordBoxSi_Admin->setGeometry(QRect(280, 160, 113, 20));
        BackButtonSI_Admin = new QPushButton(AdminSignInPage);
        BackButtonSI_Admin->setObjectName("BackButtonSI_Admin");
        BackButtonSI_Admin->setGeometry(QRect(40, 30, 80, 18));
        InsertEmailBoxSI_Admin = new QLineEdit(AdminSignInPage);
        InsertEmailBoxSI_Admin->setObjectName("InsertEmailBoxSI_Admin");
        InsertEmailBoxSI_Admin->setGeometry(QRect(280, 130, 113, 20));
        label_17 = new QLabel(AdminSignInPage);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(100, 190, 101, 16));
        InsertPersonalCodeBox = new QLineEdit(AdminSignInPage);
        InsertPersonalCodeBox->setObjectName("InsertPersonalCodeBox");
        InsertPersonalCodeBox->setGeometry(QRect(280, 190, 113, 20));
        stackedWidget->addWidget(AdminSignInPage);
        SignUpClient = new QWidget();
        SignUpClient->setObjectName("SignUpClient");
        SignUpIntoApp = new QPushButton(SignUpClient);
        SignUpIntoApp->setObjectName("SignUpIntoApp");
        SignUpIntoApp->setGeometry(QRect(200, 270, 80, 18));
        InsertEmailBoxSU = new QLineEdit(SignUpClient);
        InsertEmailBoxSU->setObjectName("InsertEmailBoxSU");
        InsertEmailBoxSU->setGeometry(QRect(250, 40, 113, 20));
        InsertPasswordBoxSU = new QLineEdit(SignUpClient);
        InsertPasswordBoxSU->setObjectName("InsertPasswordBoxSU");
        InsertPasswordBoxSU->setGeometry(QRect(250, 70, 113, 20));
        StatusSignUpLabelSU = new QLabel(SignUpClient);
        StatusSignUpLabelSU->setObjectName("StatusSignUpLabelSU");
        StatusSignUpLabelSU->setGeometry(QRect(170, 220, 131, 16));
        label = new QLabel(SignUpClient);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 40, 111, 20));
        label_2 = new QLabel(SignUpClient);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 70, 91, 20));
        label_3 = new QLabel(SignUpClient);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 100, 37, 12));
        label_4 = new QLabel(SignUpClient);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(130, 130, 37, 12));
        label_5 = new QLabel(SignUpClient);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(130, 160, 71, 16));
        label_6 = new QLabel(SignUpClient);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(130, 190, 71, 16));
        InsertNumeBoxSU = new QLineEdit(SignUpClient);
        InsertNumeBoxSU->setObjectName("InsertNumeBoxSU");
        InsertNumeBoxSU->setGeometry(QRect(250, 100, 113, 20));
        InsertPrenumeBoxSU = new QLineEdit(SignUpClient);
        InsertPrenumeBoxSU->setObjectName("InsertPrenumeBoxSU");
        InsertPrenumeBoxSU->setGeometry(QRect(250, 130, 113, 20));
        InsertNrTelefonBoxSU = new QLineEdit(SignUpClient);
        InsertNrTelefonBoxSU->setObjectName("InsertNrTelefonBoxSU");
        InsertNrTelefonBoxSU->setGeometry(QRect(250, 160, 113, 20));
        InsertBioBoxSU = new QLineEdit(SignUpClient);
        InsertBioBoxSU->setObjectName("InsertBioBoxSU");
        InsertBioBoxSU->setGeometry(QRect(250, 190, 113, 20));
        label_7 = new QLabel(SignUpClient);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(180, 10, 111, 20));
        BackButtonSU = new QPushButton(SignUpClient);
        BackButtonSU->setObjectName("BackButtonSU");
        BackButtonSU->setGeometry(QRect(20, 30, 80, 18));
        stackedWidget->addWidget(SignUpClient);
        PaginaPrincipalaMagazinClient = new QWidget();
        PaginaPrincipalaMagazinClient->setObjectName("PaginaPrincipalaMagazinClient");
        label_8 = new QLabel(PaginaPrincipalaMagazinClient);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(140, 30, 171, 20));
        stackedWidget->addWidget(PaginaPrincipalaMagazinClient);
        SignInClient = new QWidget();
        SignInClient->setObjectName("SignInClient");
        label_9 = new QLabel(SignInClient);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(170, 60, 251, 16));
        label_10 = new QLabel(SignInClient);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(76, 120, 121, 20));
        label_11 = new QLabel(SignInClient);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(76, 150, 121, 20));
        StatusSignUpLabelSignIn = new QLabel(SignInClient);
        StatusSignUpLabelSignIn->setObjectName("StatusSignUpLabelSignIn");
        StatusSignUpLabelSignIn->setGeometry(QRect(110, 180, 261, 20));
        SignIntoAppButton = new QPushButton(SignInClient);
        SignIntoAppButton->setObjectName("SignIntoAppButton");
        SignIntoAppButton->setGeometry(QRect(190, 210, 80, 18));
        InsertEmailBoxSI = new QLineEdit(SignInClient);
        InsertEmailBoxSI->setObjectName("InsertEmailBoxSI");
        InsertEmailBoxSI->setGeometry(QRect(260, 120, 113, 20));
        InsertPasswordBoxSi = new QLineEdit(SignInClient);
        InsertPasswordBoxSi->setObjectName("InsertPasswordBoxSi");
        InsertPasswordBoxSi->setGeometry(QRect(260, 150, 113, 20));
        BackButtonSI = new QPushButton(SignInClient);
        BackButtonSI->setObjectName("BackButtonSI");
        BackButtonSI->setGeometry(QRect(20, 20, 80, 18));
        stackedWidget->addWidget(SignInClient);

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, stackedWidget);

        SecondChance->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SecondChance);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 546, 17));
        SecondChance->setMenuBar(menubar);
        statusbar = new QStatusBar(SecondChance);
        statusbar->setObjectName("statusbar");
        SecondChance->setStatusBar(statusbar);

        retranslateUi(SecondChance);

        stackedWidget->setCurrentIndex(5);


        QMetaObject::connectSlotsByName(SecondChance);
    } // setupUi

    void retranslateUi(QMainWindow *SecondChance)
    {
        SecondChance->setWindowTitle(QCoreApplication::translate("SecondChance", "SecondChance", nullptr));
        SignInClientButton->setText(QCoreApplication::translate("SecondChance", "Sign In", nullptr));
        SignUpClientButton->setText(QCoreApplication::translate("SecondChance", "Sign Up", nullptr));
        ChooseClientTypeButton->setText(QCoreApplication::translate("SecondChance", "Client", nullptr));
        ChooseAdminClientButton->setText(QCoreApplication::translate("SecondChance", "Admin", nullptr));
        AdminSignInButton->setText(QCoreApplication::translate("SecondChance", "Sign In", nullptr));
        label_12->setText(QCoreApplication::translate("SecondChance", "ADMIN ALEGE:", nullptr));
        label_16->setText(QCoreApplication::translate("SecondChance", "Asta vede adminul", nullptr));
        label_13->setText(QCoreApplication::translate("SecondChance", "parola", nullptr));
        StatusSignUpLabelSignIn_Admin->setText(QString());
        label_14->setText(QCoreApplication::translate("SecondChance", "Introduceti Email-ul", nullptr));
        label_15->setText(QCoreApplication::translate("SecondChance", "Pagina accesare cont ADMIN", nullptr));
        SignIntoAppButton_Admin->setText(QCoreApplication::translate("SecondChance", "Sign In", nullptr));
        BackButtonSI_Admin->setText(QCoreApplication::translate("SecondChance", "Back", nullptr));
        InsertEmailBoxSI_Admin->setText(QString());
        label_17->setText(QCoreApplication::translate("SecondChance", "Cod personal", nullptr));
        SignUpIntoApp->setText(QCoreApplication::translate("SecondChance", "Sign Up", nullptr));
        StatusSignUpLabelSU->setText(QString());
        label->setText(QCoreApplication::translate("SecondChance", "Introcuceti Email-ul", nullptr));
        label_2->setText(QCoreApplication::translate("SecondChance", "IntroducetiParola", nullptr));
        label_3->setText(QCoreApplication::translate("SecondChance", "Nume:", nullptr));
        label_4->setText(QCoreApplication::translate("SecondChance", "Prenume", nullptr));
        label_5->setText(QCoreApplication::translate("SecondChance", "Numar Telefon", nullptr));
        label_6->setText(QCoreApplication::translate("SecondChance", "Bio (optional)", nullptr));
        label_7->setText(QCoreApplication::translate("SecondChance", "Pagina creare cont client", nullptr));
        BackButtonSU->setText(QCoreApplication::translate("SecondChance", "Back", nullptr));
        label_8->setText(QCoreApplication::translate("SecondChance", "SECOND CHANCE MARKETPLACE CLIENT", nullptr));
        label_9->setText(QCoreApplication::translate("SecondChance", "Pagina accesare cont client", nullptr));
        label_10->setText(QCoreApplication::translate("SecondChance", "Introduceti Email-ul", nullptr));
        label_11->setText(QCoreApplication::translate("SecondChance", "parola", nullptr));
        StatusSignUpLabelSignIn->setText(QString());
        SignIntoAppButton->setText(QCoreApplication::translate("SecondChance", "Sign In", nullptr));
        InsertEmailBoxSI->setText(QString());
        BackButtonSI->setText(QCoreApplication::translate("SecondChance", "Back", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecondChance: public Ui_SecondChance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDCHANCE_H
