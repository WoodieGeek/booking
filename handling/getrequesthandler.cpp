#include "getrequesthandler.h"

GetRequestHandler::GetRequestHandler(std::shared_ptr<QSqlDatabase> db, std::shared_ptr<Request> request)
    : Db_(db)
    , Request_(request) {

}

QString GetRequestHandler::RestaurantHandle() {
    TableRestaurants Restaurants;
    std::shared_ptr<QSqlQuery> query(Db_(SELECT
                                        (Restaurants.ID, Restaurants.Name, Restaurants.Description, Restaurants.Address, Restaurants.Thumbnail).
                                        FROM(Restaurants)));
    QJsonArray restaurantsArray;
    QVector<QString> Columns = {"ID", "Name", "Description", "Address", "Thumbmail"};
    while (query->next()) {
        QJsonObject restaurant;
        for (int i = 0; i < Columns.size(); i++)
            restaurant[Columns[i]] = query->value(i).toString();
        restaurantsArray.append(std::move(restaurant));
    }
    QJsonDocument result;
    result.setArray(restaurantsArray);
    return QString(result.toJson());
}

QString GetRequestHandler::OrderByUserIDHandle() {
    /*
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
    */
}

QString GetRequestHandler::TablesByRestaurantIDHandle() {
    /*
    QJsonArray tables;
    QString getRestaurant("SELECT ID, H, W, X, Y, Type FROM Tables WHERE RestaurantID = %1");
    QString getOrders(QString("SELECT ") +
                      "Orders.StartTime, Orders.FinishTime FROM BookedTables INNER JOIN Orders on " +
                      "BookedTables.OrderID = Orders.ID " +
                      "WHERE BookedTables.TableID = %1  and Orders.StartTime >= %2 and FinishTime <= %3");
    QVector<QString> columnTable = {"ID", "H", "W", "X", "Y", "Type"};
    QDateTime current;
    if (Request_->GetCgi("date").isEmpty())
        return QString();
    current.setSecsSinceEpoch(Request_->GetCgi("date").toInt());
    QDate day = current.date();
    QDateTime startDay(day);
    QDateTime finishDay(day.addDays(1));
    QString left = QString::number(startDay.toSecsSinceEpoch());
    QString right = QString::number(finishDay.toSecsSinceEpoch());
    std::unique_ptr<QSqlQuery> queryRestaurant(new QSqlQuery(*DB_));
    if (Request_->GetCgi("id").isEmpty())
        return QString();
    if (queryRestaurant->exec(getRestaurant.arg(Request_->GetCgi("id")))) {
        while (queryRestaurant->next()) {
            QJsonObject table;
            for (int i = 0; i < columnTable.size(); i++) {
                table[columnTable[i]] = queryRestaurant->value(i).toString();
            }
            std::unique_ptr<QSqlQuery> queryTables(new QSqlQuery(*DB_));
            QJsonArray orders;
            if (queryTables->exec(getOrders.arg(table["ID"].toString(), left, right))) {
                while (queryTables->next()) {
                    orders.append(queryTables->value(0).toString());
                    orders.append(queryTables->value(1).toString());
                }
            }
            table["Orders"] = std::move(orders);
            tables.append(std::move(table));
        }
    }
    QJsonDocument result;
    result.setArray(tables);
    return QString(result.toJson());
    */
}
