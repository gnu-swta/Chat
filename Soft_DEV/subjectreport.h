#ifndef SUBJECTREPORT_H
#define SUBJECTREPORT_H

#include <QMainWindow>
#include "type.h"
#include "classinfo.h"
#include "api_http.h"

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
    void on_Button_AddTest_clicked();

private:
    Ui::SubjectReport *ui;
    Api_http *api_http;
    struct reportArr list[100];
    void get_Report_List(QString data);
    int report_count;
    void set_report();
    struct classArr data;

private slots:
    void slot_Get_Reply(QNetworkReply* re);
};

#endif // SUBJECTREPORT_H
