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

    if (Request_->GetCgi("id").isEmpty())
        return QString();

    QJsonArray ordersArray;
    TableRestaurants Restaurants;
    TableOrders Orders;
    TableTables Tables;
    TableTableType TableType;
    TableBookedTables BookedTables;
    std::shared_ptr<QSqlQuery> getRestaurants(Db_(
                                         SELECT(
                                         Orders.ID, Orders.StartTime, Orders.FinishTime,
                                         Restaurants.ID, Restaurants.Name, Restaurants.Description, Restaurants.Address, Restaurants.Thumbnail).
                                         FROM(Orders).
                                         INNER_JOIN(Restaurants).
                                         ON(Orders.ID == Restaurants.ID).
                                         WHERE(Orders.UserID == Request_->GetCgi("id").toInt())));
    QVector<QString> columnsOrder = {"ID", "StartTime", "FinishTime"};
    QVector<QString> columnRestaurant = {"ID", "Name", "Description", "Address", "Thumbnail"};
    QVector<QString> columntTable = {"ID", "H", "W", "X", "Y", "Type"};
    if (getRestaurants) {
        while (getRestaurants->next()) {
            QJsonObject order, restaurant;
            int current = 0;
            for (int i = 0; i < columnsOrder.size(); i++, current++)
                order[columnsOrder[i]] = getRestaurants->value(current).toString();
            for (int i = 0; i < columnRestaurant.size(); i++, current++)
                restaurant[columnRestaurant[i]] = getRestaurants->value(current).toString();
            order["Restaurant"] = std::move(restaurant);
            int orderID = order["ID"].toString().toInt();
            std::shared_ptr<QSqlQuery> queryTables(Db_(
                                       SELECT(Tables.ID, Tables.H, Tables.W, Tables.X, TableType.Name).
                                       FROM(BookedTables).
                                       INNER_JOIN(Tables).ON(BookedTables.TableID == Tables.ID).
                                       INNER_JOIN(TableType).ON(Tables.Type == TableType.ID).WHERE(BookedTables.OrderID == orderID)));
            if (queryTables) {
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

QString GetRequestHandler::TablesByRestaurantIDHandle() {
    TableOrders Orders;
    TableBookedTables BookedTables;
    TableTables Tables;
    QJsonArray tables;
    if (Request_->GetCgi("id").isEmpty())
        return QString();
    int restaurantID = Request_->GetCgi("id").toInt();
    std::shared_ptr<QSqlQuery> queryRestaurant(Db_(SELECT(Tables.ID, Tables.H, Tables.W, Tables.X, Tables.Y, Tables.Type).
                                                   FROM(Tables).WHERE(Tables.RestaurantID == restaurantID)));
    QVector<QString> columnTable = {"ID", "H", "W", "X", "Y", "Type"};
    QDateTime current;
    if (Request_->GetCgi("date").isEmpty())
        return QString();
    current.setSecsSinceEpoch(Request_->GetCgi("date").toInt());
    QDate day = current.date();
    QDateTime startDay(day);
    QDateTime finishDay(day.addDays(1));
    int left = static_cast<int>(startDay.toSecsSinceEpoch());
    int right = static_cast<int>(finishDay.toSecsSinceEpoch());
    if (queryRestaurant) {
        while (queryRestaurant->next()) {
            QJsonObject table;
            for (int i = 0; i < columnTable.size(); i++) {
                table[columnTable[i]] = queryRestaurant->value(i).toString();
            }
            int tableID = table["ID"].toString().toInt();
            std::shared_ptr<QSqlQuery> queryTables(Db_(SELECT(Orders.StartTime, Orders.FinishTime).FROM(BookedTables).
                                                       INNER_JOIN(Orders).ON(BookedTables.OrderID == Orders.ID).
                                                       WHERE(BookedTables.TableID == tableID & Orders.StartTime >= left & Orders.FinishTime <= right)));
            QJsonArray orders;
            if (queryTables) {
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

}
