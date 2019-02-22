#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include <bits/stdc++.h>
#include <QSqlDatabase>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QSqlQuery>
#include "request.h"

class RequestHandler
{
public:
    RequestHandler(std::shared_ptr<QSqlDatabase> db, std::shared_ptr<Request> request);
    QString RestaurantHandle();
    QString OrderByUserIDHandle();
private:
    std::shared_ptr<QSqlDatabase> DB_;
    std::shared_ptr<Request> Request_;
};

#endif // REQUESTHANDLER_H
