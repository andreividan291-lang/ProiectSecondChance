#include "secondchance.h"
#include <QDebug>
#include <QApplication>
#include <QString>
#include "servermanager.h"
#include "mythread.h"
#include <ctime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SecondChance w;
    w.show();

    ServerManager &MyServer = ServerManager::get_instance();
    MyServer.start_server(1234);
    MyServer.connectDB();
    // MyServer.generateAdminCredentials();
    return a.exec();
}
