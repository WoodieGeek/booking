#ifndef DB_H
#define DB_H
#include <QSqlDatabase>
#include <QSqlQuery>
#include "operations.h"

struct Db {
   std::shared_ptr<QSqlQuery> operator() (const Operation& operation) {
        std::shared_ptr<QSqlQuery> result(new QSqlQuery(*DB_));
        qDebug() << operation.Serialization();
        if(!result->exec(operation.Serialization()))
            return {};
        return result;
   }
   std::shared_ptr<QSqlDatabase> DB_;
   Db(std::shared_ptr<QSqlDatabase> db_) : DB_(db_) {
   }
};

#endif // DB_H
