#include "request.h"

Request::Request(const QString& request) {
    QStringList headers = request.split("\r\n");
    QStringList StartingLine = headers[0].split(' ');
    this->Type_ = StartingLine[0];
    this->Url_ = StartingLine[1];
    headers.pop_front();
    qDebug() << headers.back();
    this->Body_ = headers.back();
    headers.pop_back();
    for (auto& line : headers) {
        QString key, value;
        bool wasDelimiter = false;
        for (int i = 0; i < line.size(); i++) {
            if (!wasDelimiter) {
                if (line[i] == ':') {
                    i++;
                    wasDelimiter = true;
                    continue;
                }
                key.push_back(line[i]);
            }
            else
                value.push_back(line[i]);
        }
        this->Headers_[std::move(key)] = std::move(value);
    }
    QUrl url(Url_);
    this->Path_ = url.path();
    QStringList cgi = url.query().split('&');
    for (const auto& param : cgi) {
        QStringList paramList = param.split('=');
        if (paramList.size() == 2)
            this->Cgi_[paramList[0]] = paramList[1];
    }
}

const QString& Request::GetType() const {
    return Type_;
}

const QString& Request::GetUri() const {
    return Url_;
}

const QString& Request::GetPath() const {
    return Path_;
}

QString Request::GetCgi(const QString& name) const {
    if (Cgi_.contains(name))
        return Cgi_[name];
    else
        return QString();
}

const QString& Request::GetBody() const {
    return Body_;
}
