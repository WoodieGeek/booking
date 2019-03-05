#include "server.h"

Server::Server(QObject* parent)
    : QTcpServer(parent)
    , ThreadPool(new QThreadPool(this)) {
    DB_.reset(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE")));
    DB_->setDatabaseName(NameDB);
    if (!DB_->open())
        qDebug() << "DB dont open";
}

Server::~Server() {
}

void Server::StartServer() {
    QHostAddress localhost("127.0.0.1");
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
