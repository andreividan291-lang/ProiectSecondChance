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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SecondChance
{
public:
    QWidget *centralwidget;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *page_3;
    QPlainTextEdit *plainTextEdit;
    QTextEdit *textEdit;
    QTextEdit *textEdit_2;
    QPushButton *DoneButton;
    QLineEdit *InsertEmailBox;
    QLineEdit *InsertPasswordBox;
    QWidget *page_2;
    QTextEdit *textEdit_5;
    QTextEdit *textEdit_6;
    QPlainTextEdit *plainTextEdit_2;
    QTextEdit *textEdit_7;
    QTextEdit *textEdit_8;
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
        stackedWidget->setGeometry(QRect(0, 0, 471, 291));
        page = new QWidget();
        page->setObjectName("page");
        pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(190, 60, 80, 18));
        pushButton_2 = new QPushButton(page);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(190, 110, 80, 18));
        stackedWidget->addWidget(page);
        page_3 = new QWidget();
        page_3->setObjectName("page_3");
        plainTextEdit = new QPlainTextEdit(page_3);
        plainTextEdit->setObjectName("plainTextEdit");
        plainTextEdit->setGeometry(QRect(150, 50, 91, 21));
        textEdit = new QTextEdit(page_3);
        textEdit->setObjectName("textEdit");
        textEdit->setGeometry(QRect(130, 110, 104, 16));
        textEdit_2 = new QTextEdit(page_3);
        textEdit_2->setObjectName("textEdit_2");
        textEdit_2->setGeometry(QRect(130, 140, 104, 21));
        DoneButton = new QPushButton(page_3);
        DoneButton->setObjectName("DoneButton");
        DoneButton->setGeometry(QRect(190, 200, 80, 18));
        InsertEmailBox = new QLineEdit(page_3);
        InsertEmailBox->setObjectName("InsertEmailBox");
        InsertEmailBox->setGeometry(QRect(250, 110, 113, 20));
        InsertPasswordBox = new QLineEdit(page_3);
        InsertPasswordBox->setObjectName("InsertPasswordBox");
        InsertPasswordBox->setGeometry(QRect(250, 140, 113, 20));
        stackedWidget->addWidget(page_3);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        textEdit_5 = new QTextEdit(page_2);
        textEdit_5->setObjectName("textEdit_5");
        textEdit_5->setGeometry(QRect(140, 150, 104, 21));
        textEdit_6 = new QTextEdit(page_2);
        textEdit_6->setObjectName("textEdit_6");
        textEdit_6->setGeometry(QRect(250, 150, 104, 16));
        plainTextEdit_2 = new QPlainTextEdit(page_2);
        plainTextEdit_2->setObjectName("plainTextEdit_2");
        plainTextEdit_2->setGeometry(QRect(160, 60, 101, 21));
        textEdit_7 = new QTextEdit(page_2);
        textEdit_7->setObjectName("textEdit_7");
        textEdit_7->setGeometry(QRect(250, 120, 104, 16));
        textEdit_8 = new QTextEdit(page_2);
        textEdit_8->setObjectName("textEdit_8");
        textEdit_8->setGeometry(QRect(140, 120, 104, 16));
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
        pushButton->setText(QCoreApplication::translate("SecondChance", "Log In", nullptr));
        pushButton_2->setText(QCoreApplication::translate("SecondChance", "Sign Up", nullptr));
        plainTextEdit->setPlainText(QCoreApplication::translate("SecondChance", "Pagina de creare cont", nullptr));
        textEdit->setHtml(QCoreApplication::translate("SecondChance", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Introduceti Email:</p></body></html>", nullptr));
        textEdit_2->setHtml(QCoreApplication::translate("SecondChance", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Introduceti Parola:</p></body></html>", nullptr));
        DoneButton->setText(QCoreApplication::translate("SecondChance", "Gata!", nullptr));
        textEdit_5->setHtml(QCoreApplication::translate("SecondChance", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Introduceti Parola:</p></body></html>", nullptr));
        plainTextEdit_2->setPlainText(QCoreApplication::translate("SecondChance", "Pagina de accesare cont", nullptr));
        textEdit_8->setHtml(QCoreApplication::translate("SecondChance", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"hr { height: 1px; border-width: 0; }\n"
"li.unchecked::marker { content: \"\\2610\"; }\n"
"li.checked::marker { content: \"\\2612\"; }\n"
"</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Introduceti Email:</p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecondChance: public Ui_SecondChance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDCHANCE_H
