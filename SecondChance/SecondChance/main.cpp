#include "secondchance.h"
#include <QDebug>
#include <QApplication>
#include <QString>
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SecondChance w;
    w.show();

    return a.exec();
}
