#include "requesthandler.h"

RequestHandler::RequestHandler(std::shared_ptr<QSqlDatabase> db, std::shared_ptr<Request> request)
    : DB_(db)
    , Request_(request) {
}

QString RequestHandler::RestaurantHandle() {
    QJsonArray restaurantsArray;
    std::unique_ptr<QSqlQuery> query(new QSqlQuery(*DB_));
    QVector<QString> Columns = {"ID", "Name", "Description", "Address", "Thumbmail"};
    if (query->exec("SELECT * FROM Restaurants")) {
        while (query->next()) {
            QJsonObject restaurant;
            for (int i = 0; i < Columns.size(); i++)
                restaurant[Columns[i]] = query->value(i).toString();
            restaurantsArray.append(std::move(restaurant));
        }
    }
    QJsonDocument result;
    result.setArray(restaurantsArray);
    return QString(result.toJson());
}

QString RequestHandler::OrderByUserIDHandle() {
    QJsonArray ordersArray;
    std::unique_ptr<QSqlQuery> query(new QSqlQuery(*DB_));
    std::unique_ptr<QSqlQuery> queryTables(new QSqlQuery(*DB_));
    QString getRestaurants(QString("SELECT ") +
                                "Orders.ID, Orders.StartTime, Orders.FinishTime, " +
                                "Restaurants.ID, Restaurants.Name, Restaurants.Description, Restaurants.Address, Restaurants.Thumbnail " +
                                "FROM Orders " +
                                "INNER JOIN Restaurants on Orders.RestaurantID = Restaurants.ID " +
                                "where Orders.UserID = %1");
    QString getTables(QString("SELECT ") +
                              "Tables.ID, Tables.H, Tables.W, Tables.X, Tables.Y, " +
                              "TableType.Name " +
                              "FROM BookedTables " +
                              "INNER JOIN Tables on BookedTables.TableID = Tables.ID " +
                              "INNER JOIN TableType on Tables.Type = TableType.ID " +
                              "where OrderID = %1");
    if (Request_->GetCgi("id").isEmpty()) {
        return QString();
    }
    QVector<QString> columnsOrder = {"ID", "StartTime", "FinishTime"};
    QVector<QString> columnRestaurant = {"ID", "Name", "Description", "Address", "Thumbnail"};
    QVector<QString> columntTable = {"ID", "H", "W", "X", "Y", "Type"};
    if (query->exec(getRestaurants.arg(Request_->GetCgi("id")))) {
        while (query->next()) {
            QJsonObject order, restaurant;
            int current = 0;
            for (int i = 0; i < columnsOrder.size(); i++, current++)
                order[columnsOrder[i]] = query->value(current).toString();
            for (int i = 0; i < columnRestaurant.size(); i++, current++)
                restaurant[columnRestaurant[i]] = query->value(current).toString();
            order["Restaurant"] = std::move(restaurant);
            if (queryTables->exec(getTables.arg(order["ID"].toString()))) {
                QJsonArray tables;
                while (queryTables->next()) {
                    QJsonObject table;
                    for (int i = 0; i < columntTable.size(); i++)
                        table[columntTable[i]] = queryTables->value(i).toString();
                    tables.append(std::move(table));
                }
                order["Tables"] = std::move(tables);
            }
            ordersArray.append(std::move(order));
        }
    }
    QJsonDocument result;
    result.setArray(ordersArray);
    return QString(result.toJson());
}
