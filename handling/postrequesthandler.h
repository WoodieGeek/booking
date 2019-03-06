#ifndef POSTREQUESTHANDLER_H
#define POSTREQUESTHANDLER_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "request.h"
#include "sqlalchemy/sqltable.h"
#include "sqlalchemy/insert_into.h"
#include "sqlalchemy/sqltable.h"
#include "sqlalchemy/db.h"

class PostRequestHandler
{
public:
    PostRequestHandler(std::shared_ptr<QSqlDatabase> db, std::shared_ptr<Request> request);
    QString Order();
    QString User();
private:
    QString InsertOrder(QJsonValue& orderJson);
    QString UpdateOrder(QJsonValue& orderJson);
    QString InsertUser(QJsonValue& userJson);
    QString UpdateUser(QJsonValue& userJson);
    template <typename I, typename U>
    QString ChoiceMethod(I&& Insert, U&& Update, const QJsonValue& body);
private:
    Db Db_;
    std::shared_ptr<Request> Request_;
};

#endif // POSTREQUESTHANDLER_H
