#ifndef SERVER_H
#define SERVER_H

#include "handling/requestprocessing.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QFile>
#include <QThreadPool>
#include <QSqlDatabase>
#include <QJsonObject>
#include <QJsonDocument>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject* parent = nullptr);
    ~Server();
    void incomingConnection(qintptr socketDescriptor);
public slots:
    void StartServer();
private:
    void ReadConfig();
private:
    std::unique_ptr<QThreadPool> ThreadPool;
    std::shared_ptr<QSqlDatabase> DB_;
    quint16 PORT;
    QString NameDB;
    QString IP;
};

#endif // SERVER_H
