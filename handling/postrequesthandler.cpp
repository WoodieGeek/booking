#include "postrequesthandler.h"

PostRequestHandler::PostRequestHandler(std::shared_ptr<QSqlDatabase> db, std::shared_ptr<Request> request)
    : DB_(db)
    , Request_(request) {

}

QString PostRequestHandler::AddOrder() const {

}
