#ifndef POSTREQUESTHANDLER_H
#define POSTREQUESTHANDLER_H
#include <bits/stdc++.h>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QJsonObject>
#include <QJsonArray>
#include "request.h"
#include "sqlalchemy/sqltable.h"

class PostRequestHandler
{
public:
    PostRequestHandler(std::shared_ptr<QSqlDatabase> db, std::shared_ptr<Request> request);
    QString AddOrder() const;
private:
    std::shared_ptr<QSqlDatabase> DB_;
    std::shared_ptr<Request> Request_;
};

#endif // POSTREQUESTHANDLER_H
