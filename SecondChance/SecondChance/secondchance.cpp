#include "secondchance.h"
#include "./ui_secondchance.h"

SecondChance::SecondChance(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SecondChance)
{
    ui->setupUi(this);
    counter=0;
}

SecondChance::~SecondChance()
{
    delete ui;
}

void SecondChance::on_pushButton_clicked()
{
    counter++;
    qDebug()<<counter;
    ui->stackedWidget->setCurrentIndex(1);
}

