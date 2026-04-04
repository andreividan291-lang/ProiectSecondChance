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
        // 1️⃣ Alegem driver-ul SQLite
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

        // 2️⃣ Setăm numele fișierului DB
        db.setDatabaseName("aplicatie.db");

        // 3️⃣ Deschidem conexiunea
        if (!db.open()) {
            qDebug() << "Eroare conectare DB:" << db.lastError().text();
            return false;
        }

        qDebug() << "Conectare DB realizata cu succes!";
        return true;
}
