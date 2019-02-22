#include "requestprocessing.h"

RequestProcessing::RequestProcessing(qintptr socket_id, std::shared_ptr<QSqlDatabase> db)
    : Socket_id(socket_id)
    , DB_(db) {
    qDebug() << "clinet id = " <<  socket_id;
}

void RequestProcessing::Responce() {
    QString ask(Socket_->readAll());
    if (ask.isEmpty())
        return;
    Request_.reset(new Request(ask));
    RequestHandler handler(DB_, Request_);
    QString responce;
    if (Request_->GetPath() == "/restaurants.json") {
        responce = handler.RestaurantHandle();
    }
    if (Request_->GetPath() == "/orders.json") {
        responce = handler.OrderByUserIDHandle();
    }
    if (responce.isEmpty()) {
        Socket_->write("HTTP/1.1 404 \r\n\r\nBad request");
    }
    else {
        responce = "HTTP/1.1 200 OK \r\n\r\n" + responce;
        Socket_->write(responce.toLocal8Bit());
    }
    Socket_->disconnectFromHost();
}

void RequestProcessing::run() {
    Socket_.reset(new QTcpSocket());
    Socket_->setSocketDescriptor(Socket_id);
    Socket_->waitForReadyRead(1000);
    Responce();
    Socket_->waitForBytesWritten(1000);
    Socket_->close();
    Socket_->deleteLater();
}

RequestProcessing::~RequestProcessing() {

}
