#ifndef SERVERMANAGER_H
#define SERVERMANAGER_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QRegularExpression>
#include <QJsonDocument>
#include <QJsonObject>

class ServerManager : public QObject
{
    Q_OBJECT

private:
    static ServerManager* instance;
    explicit ServerManager(QObject* parent = nullptr);
    ~ServerManager();
    ServerManager(const ServerManager&) = delete;
    ServerManager& operator=(const ServerManager&) = delete;

    QTcpSocket* m_socket;
    QByteArray  m_buffer;

    // FIX #3: eliminat userIndexInApp – nu mai e folosit nicăieri
    static int productIndexInApp;

public:
    static ServerManager& get_instance();
    static void destroy_instance();

    bool start_server(quint16 port);
    void stop_server();

    // FIX #3: eliminat parametrul id_app din registerClient
    void checkLoginUtilizator(const QString& email, const QString& parola);
    void checkLoginAdmin(const QString& email, const QString& parola, const QString& codPers);
    void registerClient(const QString& email, const QString& parola,
                        const QString& n, const QString& pn,
                        const QString& t, const QString& b);

    void adaugaProdus(int idVanzator,
                      const QString& nume,
                      const QString& descriere,
                      const QString& pozaCale,
                      double pret,
                      const QString& categorie,
                      const QString& stare);

    void alimenteazaPortofel(int idUtilizator, double suma);
    void schimbaMail(int idUtilizator, const QString& emailNou);
    void schimbaParola(int idUtilizator, const QString& parolaNova);

    bool numeValid(const QString& n);
    bool prenumeValid(const QString& pn);
    bool telefonValid(const QString& t);
    bool bioValid(const QString& b);

    int get_productIndexInApp() { return ++productIndexInApp; }




signals:
    // FIX #4: loginResult transmite și id-ul utilizatorului
    void loginResult(bool success, QString message, int userId);
    void registerResult(bool success, QString message);
    void adminLoginResult(bool success, QString message);
    void adaugaProdusResult(bool success, QString message, int idProdus);
    void alimentarePortofelResult(bool success, QString message, double soldNou);
    void schimbareMailResult(bool success, QString message);
    void schimbareParolaResult(bool success, QString message);
};

#endif // SERVERMANAGER_H
