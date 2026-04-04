#include "secondchance.h"
#include "./ui_secondchance.h"
#include "utilizator.h"
#include "servermanager.h"

SecondChance::SecondChance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SecondChance)
{
    ui->setupUi(this);
    counter=0;

    emailLineEdit = ui->InsertEmailBox;
    parolaLineEdit = ui->InsertPasswordBox;

    connect(emailLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onEmailReturnPressed);
    connect(parolaLineEdit, &QLineEdit::returnPressed, this, &SecondChance::onParolaReturnPressed);

}

SecondChance::~SecondChance()
{
    delete ui;
}

void SecondChance::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_2);
}


void SecondChance::on_pushButton_2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->page_3);
}

void SecondChance::onEmailReturnPressed() {
    QString text = emailLineEdit->text();
    qDebug() << "Email:" << text;
    emailLineEdit->clearFocus();
}

void SecondChance::onParolaReturnPressed() {
    QString text = parolaLineEdit->text();
    qDebug() << "Parola:" << text;
    parolaLineEdit->clearFocus();
}



void SecondChance::on_DoneButton_clicked()
{
    int pozAt = emailLineEdit->text().indexOf("@");
    QString dupaAt = emailLineEdit->text().mid(pozAt + 1);

    if (!emailLineEdit->text().contains("@") || (pozAt == 0 || pozAt == emailLineEdit->text().length() - 1) ||
        (!dupaAt.contains(".")))
    {
        qDebug()<<"Email invalid\n";
        return;
    }
    else
    {
        qDebug()<<"Informatii valide.\n";
        Utilizator* u = new Utilizator(emailLineEdit->text(),parolaLineEdit->text());
        ServerManager::get_instance().addUtilizator(u);
    }
}
