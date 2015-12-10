#ifndef SUBJECTREPORT_H
#define SUBJECTREPORT_H

#include <QMainWindow>
#include "type.h"
#include "classinfo.h"
#include "api_http.h"
#include "eachreport.h"

namespace Ui {
class SubjectReport;
}

class SubjectReport : public QMainWindow
{
    Q_OBJECT

public:
    explicit SubjectReport(classArr data, QWidget *parent = 0);
    ~SubjectReport();

private slots:

private:
    Ui::SubjectReport *ui;
    Api_http *api_http;
    struct reportArr list[100];
    void get_Report_List(QString data);
    int report_count;
    void set_report();
    struct classArr test;
    void show_report(int num);
    EachReport *item[20];
    Loading *load;
    QTimer timer;

private slots:
    void slot_Get_Reply(QNetworkReply* re);
    void slot_upload();
    void slotTimeout();

signals:
    void done();
};

#endif // SUBJECTREPORT_H
