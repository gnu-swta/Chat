#include "api_http.h"

Api_http::Api_http(QObject *parent)
{
    networkManager = new QNetworkAccessManager();
    connect(networkManager,SIGNAL(finished(QNetworkReply*)),
            this,SLOT(slotGetreply(QNetworkReply*)));
}


/**
 * @brief Api_http::post_url
 * @param user      : 사용자 (학생, 교수)
 * @param url_type  : url 종류 ( 로그인, 정보요청 )
 * @param data      : 파라미터
 * @param count     : 파라미터 개수
 */
void Api_http::post_url(int user, int url_type, QString data, int count)
{
    QString url;

    QByteArray postData;

    QUrl params;
    QUrlQuery query;
    QUrl serviceUrl;
    QNetworkRequest networkRequest;

    int i=0,j=0;

    // make url
    url = appendUrl(user,url_type);
    getParameters(data, count);

    // url 세팅
    serviceUrl = QUrl(url);

    // 임시방편으로 파라미터 맨앞에 더미데이터 넣음
    query.clear();
    query.addQueryItem("dummy","dummy");

    for(i=0;i<count/2;i++)
    {

        qDebug()<<parameters[j]+" "+parameters[j+1];
        query.addQueryItem(parameters[j],parameters[j+1]);

        j+=2;
    }

    params.setQuery(query);
    postData = params.toEncoded(QUrl::FullyEncoded);

    networkRequest.setUrl(serviceUrl);
    networkRequest.setHeader(QNetworkRequest::ContentDispositionHeader,
                             "application/x-www-form-urlencoded");
    networkManager->post(networkRequest,postData);
}


QString Api_http::appendUrl(int user, int url_type)
{
    QString url;

    // SERVER_ADD "http://203.255.43.246:3000"
    url.append(SERVER_ADD);

    switch(url_type)
    {
    case (POST_LOGIN):
        url.append(URL_LOGIN);
        break;
    case (POST_USER):
        url.append(URL_USER);

        break;
    case (POST_CLASS):
        //url.append(URL_PROFESSOR);
        break;
    }

    switch(user)
    {
    case (STUDENT):
        url.append(URL_STUDENT);
        break;
    case (PROFESSOR):
        url.append(URL_PROFESSOR);
        break;
    }

    return url;
}

void Api_http::get_url(int user, int url_type, QString data, int count)
{

    QString url;

    QUrl serviceUrl;
    QUrlQuery query;
    QNetworkRequest networkRequest;
    QByteArray tk;
    QByteArray ky;
    QByteArray sd;
    QString key = "Authorization";
    QString sender = "Bearer ";

    // parameter 1 : 학번
    // parameter 2 : 전달자
    // parameter 3 : 토큰

    // make url
    url = appendUrl(user,url_type);
    getParameters(data, count);

    url.append("/"+parameters[0]);

    qDebug()<<parameters[0];
    qDebug()<<parameters[1];
    qDebug()<<parameters[2];

    serviceUrl = QUrl(url);
    tk = parameters[2].toLatin1();
    ky = key.toLatin1();
    sd = sender.toLatin1();

    //query.addQueryItem("student_number",parameters[0]);
    serviceUrl.setQuery(query);
    //networkRequest.setRawHeader("Authorization","Bearer "+parameters[2].toLatin1());
    networkRequest.setRawHeader(ky,sd+tk);

    qDebug()<<key.toLatin1();

    networkRequest.setUrl(serviceUrl);
    networkManager->get(networkRequest);

    qDebug()<<"Get!!";
}

/**
 * @brief Api_http::getParameters
 * @param data      : 파라미터가 담긴 배열
 * @param count     : 파라미터 개수
 */
QString* Api_http::getParameters(QString data, int count)
{
    QRegExp parseType(" ");
    QStringList parameter =data.split(parseType,QString::SkipEmptyParts);

    int i=0;

    // 짝수 인덱스 : 파라미터 이름
    // 홀수 인덱스 : 파라미터

    for(i=0;i<count;i++)
        parameters[i] = parameter.at(i);

    return parameters;
}


/**
 * @brief Api_http::slotGetreply
 * @param re
 */
void Api_http::slotGetreply(QNetworkReply *re)
{
    // 서버로부터 응답이 왔을경우
    emit getReply(re);
}
