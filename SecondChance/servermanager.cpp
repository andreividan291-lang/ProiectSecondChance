#include "servermanager.h"

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

void ServerManager::addUtilizator(Utilizator *u)
{
    ListaUtilizatoriAplicatie.push_back(u);
}

void ServerManager::deleteUtilizator(Utilizator *u)
{
    ListaUtilizatoriAplicatie.remove(u);
    delete u;
}

void ServerManager::printUtilizatori()
{
    for(auto& u : ListaUtilizatoriAplicatie)
    {
        qDebug()<<u->getEmail()<<" "<<u->getParola()<<"\n";
    }
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

bool ServerManager::registerUser(QString email, QString parola, QString n, QString pn, QString t, QString b)
{
    QSqlQuery query;

    query.prepare("INSERT INTO Utilizatori (email, parola, nume, prenume, telefon, bio) "
                  "VALUES (:email, :parola, :nume, :prenume, :telefon, :bio)");

    query.bindValue(":email", email);
    query.bindValue(":parola", parola);
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

    // Interogare pregătită pentru a evita SQL injection
    query.prepare("SELECT COUNT(*) FROM Utilizatori WHERE email = :email AND parola = :parola");
    query.bindValue(":email", email);
    query.bindValue(":parola", parola);

    if (!query.exec()) {
        qDebug() << "Eroare la exec query:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            qDebug() << "Login valid!";
            return true;
        } else {
            qDebug() << "Email sau parola incorectă";
            return false;
        }
    }
    return false;
}
