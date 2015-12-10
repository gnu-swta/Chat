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
void Api_http::post_url(int user, int url_type, QString data, QString header, int count, int isHeader)
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

    if(isHeader == HEADER_INCLUDE)
    {
        QString key = "Authorization";
        QString sender = "Bearer ";
        QByteArray tk;
        QByteArray ky;
        QByteArray sd;


        tk = header.toLatin1();
        ky = key.toLatin1();
        sd = sender.toLatin1();


        networkRequest.setRawHeader(ky,sd+tk);
    }

    getParameters(data, count);
    // url 세팅
    serviceUrl = QUrl(url);

    // 임시방편으로 파라미터 맨앞에 더미데이터 넣음
    query.clear();
    query.addQueryItem("dummy","dummy");

    for(i=0;i<count/2;i++)
    {
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

QStringList Api_http::getParsData(QString data)
{
    QRegExp parseType("("+QRegExp::escape(":[{")+"|"+
                      QRegExp::escape("}]}")+"|"+
                      QRegExp::escape("\",\"")+"|"+
                      QRegExp::escape("\":")+"|"+
                      QRegExp::escape("},{")+"|"+
                      QRegExp::escape(",\"")+"|"+
                      QRegExp::escape("\”")+"|"+
                      QRegExp::escape("\"")+"|"+
                      QRegExp::escape("{")+"|"+
                      QRegExp::escape("}")+")");

     QStringList parameter;
     parameter=data.split(parseType,QString::SkipEmptyParts);

     return parameter;
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
    case (POST_CHAT):
        url.append(URL_CHAT);
        break;
    case (GET_CHAT):
        url.append(URL_CHAT);
        break;
    case (POST_CLASS):
        //url.append(URL_PROFESSOR);
        break;
    case (POST_REGISTER_REPORT):
        url.append(URL_REGISTER);
        break;
    case (GET_SUMMIT_LIST):
        url.append(URL_SUMMIT_LIST);
        break;
    case (GET_REPORTLIST):
        url.append(URL_REGISTER);
        break;
    case (POST_SUMMIT):
        url.append(URL_SUMMIT);
        break;
    default:
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

    // 채팅일경우 누가 사용하든 상관없기때문에 생략
    default:
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

    // parameter 0 : 학번 or pk_class
    // parameter 1 : 토큰
    // parameter 2 : 시퀀스 넘버

    // make url
    url = appendUrl(user,url_type);
    getParameters(data, count);

    url.append("/"+parameters[0]);

    if(count>2)
        url.append("/"+parameters[2]);

    serviceUrl = QUrl(url);
    tk = parameters[1].toLatin1();

    ky = key.toLatin1();
    sd = sender.toLatin1();

    serviceUrl.setQuery(query);
    networkRequest.setRawHeader(ky,sd+tk);

    networkRequest.setUrl(serviceUrl);
    networkManager->get(networkRequest);
}

/**
 * @brief Api_http::getParameters
 * @param data      : 파라미터가 담긴 배열
 * @param count     : 파라미터 개수
 */
QString* Api_http::getParameters(QString data, int count)
{
    QRegExp parseType("/");
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
