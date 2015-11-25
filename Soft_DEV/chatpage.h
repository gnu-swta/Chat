#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QTimer>
#include "chatcontextlistitem.h"
#include "chatcontectlistitem_s.h"
#include "classinfo.h"
#include "api_http.h"

#define SECRET      "#비밀"
#define ALL         "#전체"
#define WHISPER     "#귓말"
#define ENTERKEY    16777220

#define MINE             0
#define ANOTHER_PERSON   1

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(chatArr chatInfo, QWidget *parent = 0);
    ~ChatPage();

private:
    void setSubjectName(QString name);
    void initHachCombo();
    void initConnect();
    void setChatInfo(struct chatArr chIf);
    void getStudentInfo(QString name, QString id);
    virtual void keyPressEvent(QKeyEvent *event);
    void getDate(QString data);
    void setMessage(struct msgArr msg, int isMine);
    void requestBeforeData(int seq);

private:
    Ui::ChatPage *ui;
    QString studentName;
    QString studentID;
    Api_http *http_api;
    struct chatArr chatIf;
    int msgSeq;
    QTimer timer;

signals:
    void sendMessage(QString msg);
    void pressEnterkey();

private slots:
    void slotChangeHash(QString hash);
    void slotClickSendBtn();
    void slotSendMessage(QString message);
    void slotGetMessage(QNetworkReply*re);
    void slotTimeout();
};

#endif // CHATPAGE_H
