#include <QWidget>

#ifndef CLASSINFO
#define CLASSINFO

struct classArr{
    QString classNum;
    QString classRoomNum;
    QString className;
    QString classTime;
};

struct studentArr{
    QString studentID;
    QString name;
    QString department;
};

struct chatArr{
    QString token;
    QString className;
    QString stdID;
    QString name;
    QString fkClass;
};

struct msgArr{
    QString pkChat;
    QString fkClass;
    QString fkStudent;
    QString time;
    QString msg;
};


#define PK_CLASS        "pk_class"
#define NAME            "name"
#define GROUP           "group"
#define CLASSTIME       "classTime"
#define NON_CLASSTIME   "  [ ]"

#define PK_STUDENT      "pk_student"
#define NUMBER          "number"
#define NAME            "name"
#define DEPARTMENT      "department"

#define PK_CHAT         "pk_chat"
#define FK_CLASS        "fk_class"
#define FK_STUDENT      "fk_student"
#define TIME            "time"
#define MESSAGE         "msg"


#endif // CLASSINFO

