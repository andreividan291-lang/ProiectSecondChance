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
    QByteArray  m_buffer;   // FIX: buffer pentru pachete TCP fragmentate

    static int userIndexInApp;
    static int productIndexInApp;

public:
    static ServerManager& get_instance();
    static void destroy_instance();

    bool start_server(quint16 port);
    void stop_server();

    // Parametrii pasați prin const& (eficiență)
    void checkLoginUtilizator(const QString& email, const QString& parola);
    void checkLoginAdmin(const QString& email, const QString& parola, const QString& codPers);
    void registerClient(int id_app, const QString& email, const QString& parola,
                        const QString& n, const QString& pn,
                        const QString& t, const QString& b);

    bool numeValid(const QString& n);
    bool prenumeValid(const QString& pn);
    bool telefonValid(const QString& t);
    bool bioValid(const QString& b);

    int get_userIndexInApp()    { return ++userIndexInApp; }
    int get_productIndexInApp() { return ++productIndexInApp; }

signals:
    void loginResult(bool success, QString message);
    void registerResult(bool success, QString message);
    void adminLoginResult(bool success, QString message);
};

#endif // SERVERMANAGER_H
