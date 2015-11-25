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
    struct studentArr studentInfo;
    struct chatArr chatInfo;
    int classCnt ;

    QString loginData;
    QString token;
    QString studentNum;
    QString studentData;

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
    void setStudentInfo(QString name, QString stdID, QString depart);
    QString makeListString(int idx);
    void setToken(QString tk);
    void setStudentNumber(QString stnm);
    void getStudentInfo(QString data);
    void requireStudentInfo();


private slots:
    void slotClickReport();
    void slotClickSet();
    void slotClickChat();
    void slotClickChatList(QModelIndex idx);
    void slotGetReply(QNetworkReply *re);

};

#endif // MAINPAGE_H
