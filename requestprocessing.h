#ifndef REQUESTPROCESSING_H
#define REQUESTPROCESSING_H
#include <QRunnable>
#include <QTcpSocket>
#include <QTcpServer>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonDocument>

#include "request.h"
#include "requesthandler.h"

class RequestProcessing : public QRunnable
{
public:
    RequestProcessing(qintptr socket_id, std::shared_ptr<QSqlDatabase> db);
    ~RequestProcessing();
    void run();
private:
    void Responce();
private:
    qintptr Socket_id;
    std::unique_ptr<QTcpSocket> Socket_;
    std::shared_ptr<QSqlDatabase> DB_;
    std::shared_ptr<Request> Request_;
};

#endif // REQUESTPROCESSING_H
