#define SERVERMANAGER_H

#include <QRegularExpression>
#include <QTcpServer>
#include <QDebug>
#include <QList>
#include "mythread.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include "utilizator.h"
#include "myexception.h"

class ServerManager : public QTcpServer
{
    Q_OBJECT

private:
    static ServerManager* instance;
    std::list<Utilizator*> ListaUtilizatoriAplicatie;

    // Constructor privat pentru Singleton
    explicit ServerManager(QObject* parent = nullptr);
    ~ServerManager();

    // Blocăm copierea și mutarea (Regula Singleton-ului)
    ServerManager(const ServerManager& s) = delete;
    ServerManager(ServerManager&& s) = delete;
    ServerManager& operator=(const ServerManager& s) = delete;
    ServerManager& operator=(ServerManager&& s) = delete;

public:
    static ServerManager& get_instance();
    static void destroy_instance();

    bool start_server(quint16 port);
    void stop_server();
    void addUtilizator(Utilizator* u);
    void deleteUtilizator(Utilizator* u);
    void printUtilizatori();
    bool connectDB();
    bool registerUser(QString email, QString parola, QString n, QString pn, QString t, QString b);
    bool numeValid(QString n);
    bool prenumeValid(QString pn);
    bool telefonValid(QString n);
    bool bioValid(QString n);
    bool checkLogin(QString email, QString parola);

protected:
    // Override-ul corect pentru multi-threading
    void incomingConnection(qintptr socketDescriptor) override;

};

