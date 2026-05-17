#include "secondchance.h"
#include <QDebug>
#include <QApplication>
#include <QString>
#include "servermanager.h"
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SecondChance w;
    w.show();

    // ELIMINĂ SAU COMENTEAZĂ LINIILE DE MAI JOS:
    // ServerManager &MyServer = ServerManager::get_instance();
    // MyServer.start_server(1234);

    return a.exec();
}
