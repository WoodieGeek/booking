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
    RequestHandler(std::shared_ptr<QSqlDatabase> db);
    QString RestaurantHandle();
private:
    std::shared_ptr<QSqlDatabase> DB_;
};

#endif // REQUESTHANDLER_H
