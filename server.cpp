#include "server.h"

Server::Server(QObject* parent)
    : QTcpServer(parent)
    , ThreadPool(new QThreadPool(this)) {
    qDebug() << ThreadPool->maxThreadCount();
    ReadConfig();
    DB_.reset(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")));
    DB_->setDatabaseName(NameDB);
    if (!DB_->open())
        qDebug() << "DB dont open";
}

Server::~Server() {
}

void Server::StartServer() {
    QHostAddress localhost(IP);
    if (this->listen(localhost, PORT)) {
        qDebug() << "Listening";
    }
    else {
        qDebug() << "Server not started";
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    RequestProcessing* requestProcessing = new RequestProcessing(socketDescriptor, DB_);
    ThreadPool->start(requestProcessing);
}

void Server::ReadConfig() {
    QFile config("config");
    if (config.exists() && config.open(QIODevice::ReadOnly)) {
        QJsonDocument configDocument = QJsonDocument::fromJson(config.readAll());
        QJsonObject options = configDocument.object();
        PORT = static_cast<quint16>(options["PORT"].toInt());
        IP = options["IP"].toString();
        NameDB = options["DB"].toString();
        qDebug() << IP << ":" << PORT;
        qDebug() << "DB: " << NameDB;
    }
    else {
        throw("Config not found");
    }
    QString configString;
}
