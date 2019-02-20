#include "requesthandler.h"

RequestHandler::RequestHandler(std::shared_ptr<QSqlDatabase> db)
    : DB_(db) {
}

QString RequestHandler::RestaurantHandle() {
    QString responce = "HTTP/1.1 200 OK\r\n\r\n";
    QJsonArray restaurantsArray;
    std::unique_ptr<QSqlQuery> query(new QSqlQuery(*DB_));
    if (query->exec("SELECT * FROM Restaurants")) {
        while (query->next()) {
            QVector<QString> Columns = {"ID", "Name", "Description", "Address", "Thumbmail"};
            QJsonObject restaurant;
            for (int i = 0; i < Columns.size(); i++)
                restaurant[Columns[i]] = query->value(i).toString();
            restaurantsArray.append(std::move(restaurant));
        }
    }
    QJsonDocument result;
    result.setArray(restaurantsArray);
    return responce + QString(result.toJson());
}
