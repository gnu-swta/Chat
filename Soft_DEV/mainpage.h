#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>
#include <QListWidgetItem>
#include "chatpage.h"
#include "classinfo.h"
#include "chatcontextlistitem.h"
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
    int classCnt = 0;

public:
    explicit mainPage(QWidget *parent = 0);
    ~mainPage();
    void addChatList(QString className );
    void addReportList(QString className);
    void setClassInfo(struct classArr csInfo);
    void showClassList();

private:
    Ui::mainPage *ui;
    void setMainpage(int number);
    void initConnect();
    void setStudentInfo(QString name, QString stdID);
    QString makeListString(int idx);

private slots:
    void slotClickReport();
    void slotClickSet();
    void slotClickChat();
    void slotClickChatList(QModelIndex idx);
};

#endif // MAINPAGE_H
