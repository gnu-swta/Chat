#ifndef REPORT_CREATE_H
#define REPORT_CREATE_H

#include "report_manager.h"
#include "classinfo.h"
#include "report_form.h"
#include "api_http.h"
#include <QWidget>
#include <QDate>

namespace Ui {
class Report_create;
}

class Report_create : public QWidget
{
    Q_OBJECT

public:
    explicit Report_create(struct classArr data, QWidget *parent = 0);
    explicit Report_create(struct classArr data, Report_form *ori, QWidget *parent = 0);
    ~Report_create();

private:
    Ui::Report_create *ui;
    classArr test;
    void set_report();
    Api_http *api_http;

private slots:
    void slot_create();
    void slot_cancel();
};

#endif // REPORT_CREATE_H
