#ifndef REQUEST_H
#define REQUEST_H
#include <QString>
#include <QMap>
#include <QStringList>
#include <QDebug>
#include <QUrl>

class Request
{
public:
    Request(const QString& request);
    const QString& GetType() const;
    const QString& GetUri() const;
    const QString& GetPath() const;
    QString GetCgi(const QString& name) const;
private:
    QString Type_;
    QString Url_;
    QString Path_;
    QMap<QString, QString> Headers_;
    QMap<QString, QString> Cgi_;
};

#endif // REQUEST_H
