#include "servermanager.h"
#include <QJsonArray>

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
            }
            else if (action == "REGISTER") {
                bool success = obj["status"].toString() == "SUCCESS";
                QString msg  = obj["message"].toString();
                int userId   = obj["id"].toInt();  // <-- trebuie sa existe
                emit registerResult(success, msg, userId);
            }
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
            else if (action == "GET_PRODUSE_CLIENT") {
                bool    success = obj["status"].toString() == "SUCCESS";
                QString msg     = obj["message"].toString();
                QJsonArray data = obj["data"].toArray();
                emit produseClientResult(success, msg, data);
            }
            else if (action == "ADAUGA_FAVORIT") {
                bool    success = obj["status"].toString() == "SUCCESS";
                QString msg     = obj["message"].toString();
                emit adaugaFavoritResult(success, msg);
            }
            else if (action == "GET_PRODUSE_UTILIZATOR") {
                QJsonArray data = obj["data"].toArray();
                emit produseUtilizatorResult(success, message, data);
            }
            else if (action == "GET_FAVORITE") {
                QJsonArray data = obj["data"].toArray();
                emit getFavoriteResult(success, message, data);
            }
            else if (action == "CUMPARA_PRODUS") {
                emit cumparaProdusResult(success, message);
            }
            else if (action == "NOTIFICARE") {
                QString tip     = obj["tip"].toString();
                QString mesaj   = obj["message"].toString();
                emit notificareNoua(tip, mesaj);
            }
            else if (action == "GET_NOTIFICARI") {
                QJsonArray data = obj["data"].toArray();
                emit getNotificariResult(success, data);
            }
            else if (action == "MARCHEAZA_CITITE") {
                emit marcheazaCititeResult(success);
            }
            else if (action == "GET_PRODUSE_CUMPARATE") {
                QJsonArray data = obj["data"].toArray();
                emit produseCumparateResult(success, message, data);
            }
            else if (action == "GET_NOTA_VANZATOR") {
                double nota    = obj["nota_medie"].toDouble();
                int    nrRev   = obj["nr_review_uri"].toInt();
                emit notaVanzatorResult(nota, nrRev);
            }
            else if (action == "LASA_REVIEW") {
                emit lasaReviewResult(success, message);
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

void ServerManager::getProduseClient(int idUtilizator,
                                     const QString& textCautare,
                                     const QString& categorie)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[Qt] Eroare: socket deconectat!";
        return;
    }
    QJsonObject json;
    json["action"]        = "GET_PRODUSE_CLIENT";
    json["id_utilizator"] = idUtilizator;
    json["text_cautare"]  = textCautare;
    json["categorie"]     = categorie;

    QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(data);
    m_socket->flush();
}

void ServerManager::adaugaFavorit(int idUser, int idProdus)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[Qt] Eroare: socket deconectat!";
        return;
    }
    QJsonObject json;
    json["action"]    = "ADAUGA_FAVORIT";
    json["id_user"]   = idUser;
    json["id_produs"] = idProdus;

    QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(data);
    m_socket->flush();
}

void ServerManager::getProduseUtilizator(int idUtilizator)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[Qt] Eroare: socket deconectat!";
        return;
    }
    QJsonObject json;
    json["action"]        = "GET_PRODUSE_UTILIZATOR";
    json["id_utilizator"] = idUtilizator;

    QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(data);
    m_socket->flush();
}
void ServerManager::getFavorite(int idUser)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[Qt] Eroare: socket deconectat!";
        return;
    }
    QJsonObject json;
    json["action"]   = "GET_FAVORITE";
    json["id_user"]  = idUser;

    QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(data);
    m_socket->flush();
}

void ServerManager::cumparaProdus(int idCumparator, int idProdus)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) {
        qDebug() << "[Qt] Eroare: socket deconectat!";
        return;
    }
    QJsonObject json;
    json["action"]        = "CUMPARA_PRODUS";
    json["id_cumparator"] = idCumparator;
    json["id_produs"]     = idProdus;

    QByteArray data = QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n";
    m_socket->write(data);
    m_socket->flush();
}

void ServerManager::getNotificari(int idUser)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;
    QJsonObject json;
    json["action"]   = "GET_NOTIFICARI";
    json["id_user"]  = idUser;
    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}

void ServerManager::marcheazaCitite(int idUser)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;
    QJsonObject json;
    json["action"]   = "MARCHEAZA_CITITE";
    json["id_user"]  = idUser;
    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}

void ServerManager::getProduseCumparate(int idUser)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;
    QJsonObject json;
    json["action"]  = "GET_PRODUSE_CUMPARATE";
    json["id_user"] = idUser;
    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}

void ServerManager::getNotaVanzator(int idVanzator)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;
    QJsonObject json;
    json["action"]      = "GET_NOTA_VANZATOR";
    json["id_vanzator"] = idVanzator;
    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}

void ServerManager::lasaReview(int idCumparator, int idComanda, int nota, const QString& comentariu)
{
    if (m_socket->state() != QAbstractSocket::ConnectedState) return;
    QJsonObject json;
    json["action"]       = "LASA_REVIEW";
    json["id_cumparator"] = idCumparator;
    json["id_comanda"]   = idComanda;
    json["nota"]         = nota;
    json["comentariu"]   = comentariu;
    m_socket->write(QJsonDocument(json).toJson(QJsonDocument::Compact) + "\n");
    m_socket->flush();
}
