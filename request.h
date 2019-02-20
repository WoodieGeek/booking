#ifndef REQUEST_H
#define REQUEST_H
#include <QString>
#include <QMap>
#include <QStringList>
#include <QDebug>

class Request
{
public:
    Request(const QString& request);
    const QString& GetType() const;
    const QString& GetUri() const;
private:
    QString Type_;
    QString Uri_;
    QMap<QString, QString> Headers_;
};

#endif // REQUEST_H
