#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include "chatpage.h"
#include "classinfo.h"
#include "chatcontextlistitem.h"
#include "api_http.h"
#include "type.h"
#include <QDebug>


#define CLICK_CHAT      1
#define CLICK_REPORT    2
#define CLICK_SET       3

namespace Ui {
class mainPage;
}

class mainPage : public QWidget
{
    Q_OBJECT

private:
    ChatPage *chatpage;
    struct classArr classInfo[10];
    int classCnt ;

    QString loginData;
    QString token;
    QString studentNum;

    Api_http *http_api;


public:
    explicit mainPage(QString stdNum, QString loginData ,QWidget *parent = 0);
    ~mainPage();
    void addChatList(QString className );
    void addReportList(QString className);
    void setClassInfo(QString data);
    void showClassList();

private:
    Ui::mainPage *ui;
    void setMainpage(int number);
    void initConnect();
    void setStudentInfo(QString name, QString stdID);
    QString makeListString(int idx);
    QStringList getParsData(QString data);
    void setToken(QString tk);
    void setStudentNumber(QString stnm);


private slots:
    void slotClickReport();
    void slotClickSet();
    void slotClickChat();
    void slotClickChatList(QModelIndex idx);
    void slotGetReply(QNetworkReply *re);

};

#endif // MAINPAGE_H
