#define SECONDCHANCE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class SecondChance;
}
QT_END_NAMESPACE

class SecondChance : public QMainWindow
{
    Q_OBJECT

public:
    SecondChance(QWidget *parent = nullptr);
    ~SecondChance();
    int counter;


private slots:
    void on_pushButton_clicked();

private:
    Ui::SecondChance *ui;
};
