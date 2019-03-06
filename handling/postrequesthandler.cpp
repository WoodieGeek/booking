#include "postrequesthandler.h"

PostRequestHandler::PostRequestHandler(std::shared_ptr<QSqlDatabase> db, std::shared_ptr<Request> request)
    : Db_(db)
    , Request_(request) {
}

template <typename I, typename U>
QString PostRequestHandler::ChoiceMethod(I&& Insert, U&& Update, const QJsonValue& body) {
    const auto bodyMap = body.toObject();
    QJsonValue value;
    if (bodyMap.contains("insert")) {
        value = bodyMap["insert"];
        return (this->*Insert)(value);
    }
    else if (bodyMap.contains("update")){
        value = bodyMap["update"];
        return (this->*Update)(value);
    }
}

QString PostRequestHandler::Order() {
    const auto& orderJson = QJsonDocument::fromJson(Request_->GetBody().toUtf8()).object();
    return ChoiceMethod(&PostRequestHandler::InsertOrder, &PostRequestHandler::UpdateOrder , orderJson);
}

QString PostRequestHandler::InsertOrder(QJsonValue& orderJson) {
    TableUsers Users;
    TableOrders Orders;
    TableBookedTables BookedTables;
    qDebug() << orderJson;
    QJsonObject orderMap(orderJson.toObject());
    QJsonArray tables(orderMap["Tables"].toArray());
    orderMap.erase(orderMap.find("Tables"));
    auto get = [&](const QString& name) {
        return orderMap[name].toInt();
    };
    Db_(INSERT_INTO(Orders).SET(Orders.RestaurantID = get("RestaurantID"),
                                Orders.UserID = get("UserID"),
                                Orders.StartTime = get("StartTime"),
                                Orders.FinishTime = get("FinishTime")));
    int ID = Db_.LastInsertRowID();
    for (const auto table : tables) {
        Db_(INSERT_INTO(BookedTables).SET(BookedTables.OrderID = ID, BookedTables.TableID = table.toInt()));
    }
    return "HTTP/1.1 200 OK \r\n\r\n";
}

QString PostRequestHandler::UpdateOrder(QJsonValue&) {
    return "HTTP/1.1 200 OK \r\n\r\n";
}

QString PostRequestHandler::User() {
    QJsonValue userJson = QJsonDocument::fromJson(Request_->GetBody().toUtf8()).object();
    return ChoiceMethod(&PostRequestHandler::InsertUser, &PostRequestHandler::UpdateUser, userJson);
}

QString PostRequestHandler::InsertUser(QJsonValue& userJson) {
    TableUsers Users;
    const auto& userMap = userJson.toObject();
    const auto& resp = Db_(INSERT_INTO(Users).SET(Users.Name = userMap["Name"].toString(), Users.Type = userMap["Type"].toInt()));
    return "HTTP/1.1 200 OK \r\n\r\n";
}

QString PostRequestHandler::UpdateUser(QJsonValue&) {
    return "HTTP/1.1 200 OK \r\n\r\n";
}
