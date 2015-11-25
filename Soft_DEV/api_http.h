#ifndef API_HTTP_H
#define API_HTTP_H

#include <QDebug>
#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QWidget>


#include "type.h"

class Api_http : public QObject
{
    Q_OBJECT
public:
    Api_http(QObject *parent = 0);
    void post_url(int user, int url_type, QString data, QString header, int count, int isHeader);
    void get_url(int user, int url_type, QString data, int count);
    QStringList getParsData(QString data);


private:
    QString appendUrl(int user, int url_type);

private:
    QString* getParameters(QString data, int count);
    QNetworkAccessManager *networkManager;
    QString parameters[10];

public slots:
    void slotGetreply(QNetworkReply* re);

signals:
    void getReply(QNetworkReply* re);

};

#endif // API_HTTP_H
