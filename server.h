#ifndef SERVER_H
#define SERVER_H

#include "handling/requestprocessing.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QFile>
#include <QThreadPool>
#include <QSqlDatabase>
#include <QSqlQuery>

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
    std::unique_ptr<QThreadPool> ThreadPool;
    std::shared_ptr<QSqlDatabase> DB_;
    quint16 PORT = 8001;
    QString NameDB = "../booking/booking.db";
};

#endif // SERVER_H
