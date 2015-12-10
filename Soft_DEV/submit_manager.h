#ifndef SUBMIT_MANAGER_H
#define SUBMIT_MANAGER_H

#include "report_manager.h"
#include "submit_form.h"
#include "classinfo.h"
#include <QWidget>
#include "api_http.h"

namespace Ui {
class Submit_manager;
}

class Submit_manager : public QWidget
{
    Q_OBJECT

public:
    explicit Submit_manager(reportArr, struct classArr data, QWidget *parent = 0);
    ~Submit_manager();

    struct submitArr list[100];
    int listCnt;

private:
    Ui::Submit_manager *ui;
    classArr test;
    void set_submit();
    void show_submit(Submit_form *student);
    void down_report();
    void getSummitList(QString data);

    Api_http *api_http;

private slots:
    void slotGetReply(QNetworkReply* re);

private slots:

};

#endif // SUBMIT_MANAGER_H
