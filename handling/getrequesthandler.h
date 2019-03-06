#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include <QSqlDatabase>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>
#include <QSqlQuery>
#include <QDateTime>
#include "request.h"
#include "sqlalchemy/operations.h"
#include "sqlalchemy/db.h"
#include "sqlalchemy/select.h"
#include "sqlalchemy/sqltable.h"
#include "sqlalchemy/on.h"


class GetRequestHandler
{
public:
    GetRequestHandler(std::shared_ptr<QSqlDatabase> db, std::shared_ptr<Request> request);
    QString RestaurantHandle();
    QString OrderByUserIDHandle();
    QString TablesByRestaurantIDHandle();
private:
    Db Db_;
    std::shared_ptr<Request> Request_;
};

#endif // REQUESTHANDLER_H
