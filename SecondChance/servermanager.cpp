#include "servermanager.h"

int ServerManager::userIndexInApp = 1000;
int ServerManager::productIndexInApp = 1000;

ServerManager* ServerManager::instance = nullptr;

ServerManager::ServerManager(QObject* parent) : QTcpServer(parent)
{
    // Lăsăm constructorul gol. Nu apelăm listen() aici și nu conectăm newConnection!
}

ServerManager& ServerManager::get_instance()
{
    if(instance == nullptr)
    {
        instance = new ServerManager;
    }
    return *instance;
}

void ServerManager::destroy_instance()
{
    if(instance)
    {
        delete instance;
        instance = nullptr;
    }
}

bool ServerManager::start_server(quint16 port)
{
    // Verificăm dacă serverul ascultă deja ca să nu îl pornim de două ori
    if(this->isListening()) {
        qDebug() << "Server is already running.";
        return true;
    }

    if(listen(QHostAddress::Any, port))
    {
        qDebug() << "Server started on port " << port;
        return true;
    }

    qDebug() << "Server failed to start!";
    return false;
}

void ServerManager::stop_server()
{
    if(this->isListening())
    {
        this->close();
        qDebug() << "Server stopped.";
    }
}

void ServerManager::incomingConnection(qintptr socketDescriptor)
{
    qDebug() << "Client nou detectat. Alocam descriptorul:" << socketDescriptor;

    // Creăm thread-ul și îi pasăm descriptorul numeric
    MyThread *thread = new MyThread(socketDescriptor, this);

    // Când thread-ul își termină treaba (la deconectare), se șterge automat din memorie
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    // Pornim thread-ul
    thread->start();
}

ServerManager::~ServerManager()
{
    stop_server();
}

bool ServerManager::connectDB()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");

    QString connectionString =
        "Driver={ODBC Driver 17 for SQL Server};"
        "Server=UNCELEBRUANONIM\\SQLEXPRESS;"
        "Database=DB_POO;"
        "Trusted_Connection=yes;";

    db.setDatabaseName(connectionString);

    if (!db.open()) {
        qDebug() << "Eroare conectare:" << db.lastError().text();
        return false;
    }

    qDebug() << "Conectat la DB_POO!";
    return true;
}

bool ServerManager::registerClient(int id_app,QString email, QString parola, QString n, QString pn, QString t, QString b)
{
    // 1️⃣ Generează salt unic pentru fiecare user
    QString salt = QUuid::createUuid().toString();

    // 2️⃣ Creează hash-ul parolei + salt
    QByteArray data = (parola + salt).toUtf8();
    QString hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex();

    // 3️⃣ Inserăm în baza de date
    QSqlQuery query;
    query.prepare("INSERT INTO Utilizatori (id_in_app, email, password_hash, salt, nume, prenume, telefon, bio) "
                  "VALUES (:id_in_app, :email, :hash, :salt, :nume, :prenume, :telefon, :bio)");

    query.bindValue(":id_in_app",id_app);
    query.bindValue(":email", email);
    query.bindValue(":hash", hash);
    query.bindValue(":salt", salt);
    query.bindValue(":nume", n);
    query.bindValue(":prenume", pn);
    query.bindValue(":telefon", t);
    query.bindValue(":bio", b);

    if (!query.exec()) {
        qDebug() << "Eroare INSERT:" << query.lastError().text();
        return false;
    }

    qDebug() << "User salvat in DB!";
    return true;
}

bool ServerManager::numeValid(QString n)
{
    QRegularExpression regex("^[A-Za-z]+$"); // doar litere mari și mici
    if (regex.match(n).hasMatch()) {
        return true;
    }
    return false;
}

bool ServerManager::prenumeValid(QString pn)
{
    QRegularExpression regex("^[A-Za-z]+$"); // doar litere mari și mici
    if (regex.match(pn).hasMatch()) {
        return true;
    }
    return false;
}

bool ServerManager::telefonValid(QString t)
{
    bool onlyDigits = true;
    for (int i = 0; i < t.length(); ++i) {
        if (!t.at(i).isDigit()) {
            onlyDigits = false;
            break;
        }
    }
    return onlyDigits;
}

bool ServerManager::bioValid(QString b)
{
    if(b.length()<200)
    {
        return true;
    }
    return false;
}

// Funcție care returnează true dacă email și parola există în DB
bool ServerManager::checkLogin(QString email, QString parola)
{
    QSqlQuery query;
    query.prepare("SELECT password_hash, salt FROM Utilizatori WHERE email = :email");
    query.bindValue(":email", email);

    // 1️⃣ Verificăm dacă există userul
    if (!query.exec() || !query.next())
        return false;

    QString hash_db = query.value(0).toString();
    QString salt_db = query.value(1).toString();

    // 2️⃣ Refacem hash-ul cu parola introdusă
    QByteArray data = (parola + salt_db).toUtf8();
    QString hash_input = QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex();

    // 3️⃣ Comparăm
    return hash_input == hash_db;
}

bool ServerManager::registerAdmin(int id_app, QString email, QString parola, QString nume, int nivel)
{
    // 1️⃣ Generează salt unic pentru fiecare admin
    QString salt = QUuid::createUuid().toString();

    // 2️⃣ Creează hash-ul parolei + salt
    QByteArray data = (parola + salt).toUtf8();
    QString hash = QCryptographicHash::hash(data, QCryptographicHash::Sha256).toHex();

    // 3️⃣ Pregătim interogarea INSERT
    QSqlQuery query;
    query.prepare("INSERT INTO Admini (id_in_app, email, password_hash, salt, nume, nivel) "
                  "VALUES (:id_in_app, :email, :hash, :salt, :nume, :nivel)");

    query.bindValue(":id_in_app", id_app);
    query.bindValue(":email", email);
    query.bindValue(":hash", hash);
    query.bindValue(":salt", salt);
    query.bindValue(":nume", nume);
    query.bindValue(":nivel", nivel);

    if (!query.exec()) {
        qDebug() << "Eroare INSERT Admin:" << query.lastError().text();
        return false;
    }

    qDebug() << "Admin salvat in DB!";
    return true;
}
