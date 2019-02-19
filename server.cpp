#include "server.h"

Server::Server(QObject* parent) : QTcpServer(parent) {
    ThreadPool = new QThreadPool(this);
    DB = QSqlDatabase::addDatabase("QSQLITE");
    DB.setDatabaseName("vhost.db");
    if (!DB.open()) qDebug() << "DB dont open";
}

Server::~Server() {
}

void Server::StartServer() {
    QHostAddress localhost("192.168.0.34");
    if (this->listen(localhost, PORT)) {
        qDebug() << "Listening";
    }
    else {
        qDebug() << "Server not started";
    }
}

void Server::incomingConnection(qintptr socketDescriptor) {
    RequestProcessing* requestProcessing = new RequestProcessing(socketDescriptor, &DB);
    ThreadPool->start(requestProcessing);
}
