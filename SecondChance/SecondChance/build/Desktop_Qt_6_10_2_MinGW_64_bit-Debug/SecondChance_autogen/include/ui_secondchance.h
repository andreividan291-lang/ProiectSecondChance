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
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *LogInButton;
    QPushButton *SignUpButton;
    QWidget *page_3;
    QPushButton *DoneButton;
    QLineEdit *InsertEmailBox;
    QLineEdit *InsertPasswordBox;
    QLabel *StatusSignUpLabelSignUp;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *InsertNumeBox;
    QLineEdit *InsertPrenumeBox;
    QLineEdit *InsertNrTelefonBox;
    QLineEdit *InsertBioBox;
    QLabel *label_7;
    QWidget *page_4;
    QLabel *label_8;
    QWidget *page_2;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *StatusSignUpLabelSignIn;
    QPushButton *SignInAppButton;
    QLineEdit *SignInEmailBox;
    QLineEdit *SignInPasswordBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *SecondChance)
    {
        if (SecondChance->objectName().isEmpty())
            SecondChance->setObjectName("SecondChance");
        SecondChance->resize(800, 600);
        centralwidget = new QWidget(SecondChance);
        centralwidget->setObjectName("centralwidget");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setGeometry(QRect(10, 10, 471, 291));
        page = new QWidget();
        page->setObjectName("page");
        LogInButton = new QPushButton(page);
        LogInButton->setObjectName("LogInButton");
        LogInButton->setGeometry(QRect(190, 60, 80, 18));
        SignUpButton = new QPushButton(page);
        SignUpButton->setObjectName("SignUpButton");
        SignUpButton->setGeometry(QRect(190, 110, 80, 18));
        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        DoneButton = new QPushButton(page_3);
        DoneButton->setObjectName("DoneButton");
        DoneButton->setGeometry(QRect(200, 270, 80, 18));
        InsertEmailBox = new QLineEdit(page_3);
        InsertEmailBox->setObjectName("InsertEmailBox");
        InsertEmailBox->setGeometry(QRect(250, 40, 113, 20));
        InsertPasswordBox = new QLineEdit(page_3);
        InsertPasswordBox->setObjectName("InsertPasswordBox");
        InsertPasswordBox->setGeometry(QRect(250, 70, 113, 20));
        StatusSignUpLabelSignUp = new QLabel(page_3);
        StatusSignUpLabelSignUp->setObjectName("StatusSignUpLabelSignUp");
        StatusSignUpLabelSignUp->setGeometry(QRect(170, 220, 131, 16));
        label = new QLabel(page_3);
        label->setObjectName("label");
        label->setGeometry(QRect(120, 40, 111, 20));
        label_2 = new QLabel(page_3);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(120, 70, 91, 20));
        label_3 = new QLabel(page_3);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 100, 37, 12));
        label_4 = new QLabel(page_3);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(130, 130, 37, 12));
        label_5 = new QLabel(page_3);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(130, 160, 71, 16));
        label_6 = new QLabel(page_3);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(130, 190, 71, 16));
        InsertNumeBox = new QLineEdit(page_3);
        InsertNumeBox->setObjectName("InsertNumeBox");
        InsertNumeBox->setGeometry(QRect(250, 100, 113, 20));
        InsertPrenumeBox = new QLineEdit(page_3);
        InsertPrenumeBox->setObjectName("InsertPrenumeBox");
        InsertPrenumeBox->setGeometry(QRect(250, 130, 113, 20));
        InsertNrTelefonBox = new QLineEdit(page_3);
        InsertNrTelefonBox->setObjectName("InsertNrTelefonBox");
        InsertNrTelefonBox->setGeometry(QRect(250, 160, 113, 20));
        InsertBioBox = new QLineEdit(page_3);
        InsertBioBox->setObjectName("InsertBioBox");
        InsertBioBox->setGeometry(QRect(250, 190, 113, 20));
        label_7 = new QLabel(page_3);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(210, 10, 81, 16));
        stackedWidget->addWidget(page_3);
        page_4 = new QWidget();
        page_4->setObjectName("page_4");
        label_8 = new QLabel(page_4);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(160, 30, 151, 16));
        stackedWidget->addWidget(page_4);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        label_9 = new QLabel(page_2);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(170, 60, 251, 16));
        label_10 = new QLabel(page_2);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(76, 120, 121, 20));
        label_11 = new QLabel(page_2);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(76, 150, 121, 20));
        StatusSignUpLabelSignIn = new QLabel(page_2);
        StatusSignUpLabelSignIn->setObjectName("StatusSignUpLabelSignIn");
        StatusSignUpLabelSignIn->setGeometry(QRect(110, 180, 261, 20));
        SignInAppButton = new QPushButton(page_2);
        SignInAppButton->setObjectName("SignInAppButton");
        SignInAppButton->setGeometry(QRect(190, 210, 80, 18));
        SignInEmailBox = new QLineEdit(page_2);
        SignInEmailBox->setObjectName("SignInEmailBox");
        SignInEmailBox->setGeometry(QRect(260, 120, 113, 20));
        SignInPasswordBox = new QLineEdit(page_2);
        SignInPasswordBox->setObjectName("SignInPasswordBox");
        SignInPasswordBox->setGeometry(QRect(260, 150, 113, 20));
        stackedWidget->addWidget(page_2);
        SecondChance->setCentralWidget(centralwidget);
        menubar = new QMenuBar(SecondChance);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 17));
        SecondChance->setMenuBar(menubar);
        statusbar = new QStatusBar(SecondChance);
        statusbar->setObjectName("statusbar");
        SecondChance->setStatusBar(statusbar);

        retranslateUi(SecondChance);

        stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(SecondChance);
    } // setupUi

    void retranslateUi(QMainWindow *SecondChance)
    {
        SecondChance->setWindowTitle(QCoreApplication::translate("SecondChance", "SecondChance", nullptr));
        LogInButton->setText(QCoreApplication::translate("SecondChance", "Log In", nullptr));
        SignUpButton->setText(QCoreApplication::translate("SecondChance", "Sign Up", nullptr));
        DoneButton->setText(QCoreApplication::translate("SecondChance", "Gata!", nullptr));
        StatusSignUpLabelSignUp->setText(QString());
        label->setText(QCoreApplication::translate("SecondChance", "Introcuceti Email-ul", nullptr));
        label_2->setText(QCoreApplication::translate("SecondChance", "IntroducetiParola", nullptr));
        label_3->setText(QCoreApplication::translate("SecondChance", "Nume:", nullptr));
        label_4->setText(QCoreApplication::translate("SecondChance", "Prenume", nullptr));
        label_5->setText(QCoreApplication::translate("SecondChance", "Numar Telefon", nullptr));
        label_6->setText(QCoreApplication::translate("SecondChance", "Bio (optional)", nullptr));
        label_7->setText(QCoreApplication::translate("SecondChance", "Pagina creare cont", nullptr));
        label_8->setText(QCoreApplication::translate("SecondChance", "SECOND CHANCE MARKETPLACE", nullptr));
        label_9->setText(QCoreApplication::translate("SecondChance", "Pagina accesare cont ", nullptr));
        label_10->setText(QCoreApplication::translate("SecondChance", "Introduceti Email-ul", nullptr));
        label_11->setText(QCoreApplication::translate("SecondChance", "parola", nullptr));
        StatusSignUpLabelSignIn->setText(QString());
        SignInAppButton->setText(QCoreApplication::translate("SecondChance", "Sign In", nullptr));
        SignInEmailBox->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SecondChance: public Ui_SecondChance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDCHANCE_H
