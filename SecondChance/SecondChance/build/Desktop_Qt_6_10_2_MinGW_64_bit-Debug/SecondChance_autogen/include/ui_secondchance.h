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
#include <QtWidgets/QCheckBox>
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
    QPushButton *pushButton;
    QWidget *page_2;
    QCheckBox *checkBox;
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
        stackedWidget->setGeometry(QRect(0, -1, 431, 281));
        page = new QWidget();
        page->setObjectName("page");
        pushButton = new QPushButton(page);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(170, 60, 80, 18));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        checkBox = new QCheckBox(page_2);
        checkBox->setObjectName("checkBox");
        checkBox->setGeometry(QRect(180, 90, 57, 17));
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

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SecondChance);
    } // setupUi

    void retranslateUi(QMainWindow *SecondChance)
    {
        SecondChance->setWindowTitle(QCoreApplication::translate("SecondChance", "SecondChance", nullptr));
        pushButton->setText(QCoreApplication::translate("SecondChance", "PushButton", nullptr));
        checkBox->setText(QCoreApplication::translate("SecondChance", "CheckBox", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecondChance: public Ui_SecondChance {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECONDCHANCE_H
