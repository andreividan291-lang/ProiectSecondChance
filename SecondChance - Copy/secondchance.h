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
    void on_pushButton_clicked();    // pentru trecere la page_2
    void on_pushButton_2_clicked();  // pentru trecere la page_3
    void onEmailReturnPressed();
    void onParolaReturnPressed();

    void on_DoneButton_clicked();

private:

    Ui::SecondChance *ui;
    int counter;

    QLineEdit* emailLineEdit;
    QLineEdit* parolaLineEdit;

};

