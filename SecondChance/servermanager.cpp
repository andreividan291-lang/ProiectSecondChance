#include "servermanager.h"

ServerManager* ServerManager::instance = nullptr;
int ServerManager::productIndexInApp = 1000;

ServerManager::ServerManager(QObject* parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_buffer.clear();

    connect(m_socket, &QTcpSocket::connected, []() {
        qDebug() << "[Qt] Conectat la server (127.0.0.1:1234)";
    });

    connect(m_socket, &QTcpSocket::errorOccurred, [this](QAbstractSocket::SocketError) {
        qDebug() << "[Qt] Eroare socket:" << m_socket->errorString();
    });

    // FIX: Acumulăm datele într-un buffer până găsim '\n'
    connect(m_socket, &QTcpSocket::readyRead, this, [this]() {
        m_buffer.append(m_socket->readAll());

        // Procesăm toate mesajele complete din buffer (separate prin '\n')
        while (m_buffer.contains('\n')) {
            int idx = m_buffer.indexOf('\n');
            QByteArray mesajComplet = m_buffer.left(idx).trimmed();
            m_buffer.remove(0, idx + 1);

            if (mesajComplet.isEmpty()) continue;

            qDebug() << "[Qt] Mesaj primit:" << mesajComplet;

            QJsonParseError parseError;
            QJsonDocument doc = QJsonDocument::fromJson(mesajComplet, &parseError);

            if (doc.isNull()) {
                qDebug() << "[Qt] JSON invalid:" << parseError.errorString();
                continue;
            }

            QJsonObject obj = doc.object();
            QString action  = obj["action"].toString();
            bool success    = (obj["status"].toString() == "SUCCESS");
            QString message = obj["message"].toString();

            if (action == "LOGIN") {
                int userId = obj["id"].toInt();
                emit loginResult(success, message, userId);
            }            else if (action == "REGISTER")    emit registerResult(success, message);
            else if (action == "LOGIN_ADMIN") emit adminLoginResult(success, message);
            else if (action == "ADAUGA_PRODUS") {
                int idProdus = obj["id_produs"].toInt();
                emit adaugaProdusResult(success, message, idProdus);
            }
            else if (action == "ALIMENTARE_PORTOFEL") {
                double soldNou = obj["sold_nou"].toDouble();
                emit alimentarePortofelResult(success, message, soldNou);
            }
            else if (action == "SCHIMBARE_MAIL") {
                emit schimbareMailResult(success, message);
            }
            else if (action == "SCHIMBARE_PAROLA") {
                emit schimbareParolaResult(success, message);
            }
            else qDebug() << "[Qt] Actiune necunoscuta:" << action;
        }
    });
}

ServerManager& ServerManager::get_instance()
{
    if (instance == nullptr) instance = new ServerManager;
    return *instance;
}

void ServerManager::destroy_instance()
{
    if (instance) {
        delete instance;
        instance = nullptr;
    }
}

bool ServerManager::start_server(quint16 port)
{
    if (m_socket->isOpen()) m_socket->close();

    qDebug() << "[Qt] Conectare la server port" << port;
    m_socket->connectToHost("127.0.0.1", port);

    if (m_socket->waitForConnected(3000)) return true;

    qDebug() << "[Qt] Conectare esuata:" << m_socket->errorString();
    return false;
}

void ServerManager::stop_server()
{
    if (m_socket->isOpen()) m_socket->disconnectFromHost();
}

void ServerManager::checkLoginUtilizator(const QString& email, const QString& parola)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[Qt] Eroare: socket deconectat!";
        return;
    }
    QJsonObject json;
    json["action"]   = "LOGIN";
    json["email"]    = email;
    json["password"] = parola;

    // FIX: adăugăm '\n' ca terminator de mesaj
    QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(data);
    m_socket->flush();
}

void ServerManager::checkLoginAdmin(const QString& email, const QString& parola, const QString& codPers)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QJsonObject json;
    json["action"]       = "LOGIN_ADMIN";
    json["email"]        = email;
    json["password"]     = parola;
    json["cod_personal"] = codPers;

    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}

void ServerManager::registerClient( const QString& email, const QString& parola,
                                   const QString& n, const QString& pn,
                                   const QString& t, const QString& b)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QJsonObject json;
    json["action"]   = "REGISTER";
    json["email"]    = email;
    json["password"] = parola;
    json["nume"]     = n;
    json["prenume"]  = pn;
    json["tel"]      = t;
    json["bio"]      = b;

    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}

bool ServerManager::numeValid(const QString& n)   { return QRegularExpression("^[A-Za-z ]+$").match(n).hasMatch(); }
bool ServerManager::prenumeValid(const QString& pn) { return QRegularExpression("^[A-Za-z ]+$").match(pn).hasMatch(); }
bool ServerManager::bioValid(const QString& b)    { return b.length() <= 200; }
bool ServerManager::telefonValid(const QString& t) {
    if (t.isEmpty()) return false;
    for (QChar c : t) if (!c.isDigit()) return false;
    return t.length() >= 10;
}
void ServerManager::adaugaProdus(int idVanzator,
                                 const QString& nume,
                                 const QString& descriere,
                                 const QString& pozaCale,
                                 double pret,
                                 const QString& categorie,
                                 const QString& stare)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[Qt] Eroare: socket deconectat!";
        return;
    }

    QJsonObject json;
    json["action"]      = "ADAUGA_PRODUS";
    json["id_vanzator"] = idVanzator;
    json["nume"]        = nume;
    json["descriere"]   = descriere;   // poate fi gol - optional
    json["poza_cale"]   = pozaCale;    // poate fi gol
    json["pret"]        = pret;
    json["categorie"]   = categorie;
    json["stare"]       = stare;

    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}
ServerManager::~ServerManager() { stop_server(); }

void ServerManager::alimenteazaPortofel(int idUtilizator, double suma)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QJsonObject json;
    json["action"]        = "ALIMENTARE_PORTOFEL";
    json["id_utilizator"] = idUtilizator;
    json["suma"]          = suma;

    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}

void ServerManager::schimbaMail(int idUtilizator, const QString& emailNou)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QJsonObject json;
    json["action"]        = "SCHIMBARE_MAIL";
    json["id_utilizator"] = idUtilizator;
    json["email_nou"]     = emailNou;

    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}

void ServerManager::schimbaParola(int idUtilizator, const QString& parolaNova)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;

    QJsonObject json;
    json["action"]        = "SCHIMBARE_PAROLA";
    json["id_utilizator"] = idUtilizator;
    json["parola_noua"]   = parolaNova;

    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}
