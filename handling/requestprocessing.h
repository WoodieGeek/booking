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
#include "getrequesthandler.h"
#include "postrequesthandler.h"

class RequestProcessing : public QRunnable
{
public:
    RequestProcessing(qintptr socket_id, std::shared_ptr<QSqlDatabase> db);
    ~RequestProcessing();
    void run();
private:
    void Responce();
    void GetRequest();
    void PostRequest();
private:
    qintptr Socket_id;
    std::unique_ptr<QTcpSocket> Socket_;
    std::shared_ptr<QSqlDatabase> DB_;
    std::shared_ptr<Request> Request_;
};

#endif // REQUESTPROCESSING_H
