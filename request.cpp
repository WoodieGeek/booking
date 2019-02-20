#include "request.h"

Request::Request(const QString& request) {
    QStringList headers = request.split("\r\n");
    QStringList StartingLine = headers[0].split(' ');
    this->Type_ = StartingLine[0];
    this->Uri_ = StartingLine[1];
    headers.pop_front();
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
}

const QString& Request::GetType() const {
    return Type_;
}

const QString& Request::GetUri() const {
    return Uri_;
}
