#ifndef CHATPAGE_H
#define CHATPAGE_H

#include <QWidget>
#include <QDebug>
#include <QKeyEvent>
#include "chatcontextlistitem.h"
#include "chatcontectlistitem_s.h"

#define SECRET      "#비밀"
#define ALL         "#전체"
#define WHISPER     "#귓말"
#define ENTERKEY    16777220

namespace Ui {
class ChatPage;
}

class ChatPage : public QWidget
{
    Q_OBJECT

public:
    explicit ChatPage(QString sub_name, QString name, QString std_id, QWidget *parent = 0);
    ~ChatPage();

private:
    void setSubjectName(QString name);
    void initHachCombo();
    void initConnect();
    void getStudentInfo(QString name, QString id);
    virtual void keyPressEvent(QKeyEvent *event);

private:
    Ui::ChatPage *ui;
    QString studentName;
    QString studentID;

signals:
    void sendMessage(QString msg, QString stdID);
    void pressEnterkey();

private slots:
    void slotChangeHash(QString hash);
    void slotClickSendBtn();
    void slotSendMessage(QString msg, QString stdID);
    void slotGetMessage();

};

#endif // CHATPAGE_H
