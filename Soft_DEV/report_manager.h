#ifndef REPORT_MANAGER_H
#define REPORT_MANAGER_H

#include "report_create.h"
#include "submit_manager.h"
#include "report_form.h"
#include "classinfo.h"
#include "api_http.h"
#include <QWidget>
#include <QDebug>
#include <QModelIndex>
#include <QListWidgetItem>

namespace Ui {
class Report_manager;
}

class Report_manager : public QWidget
{
    Q_OBJECT

public:
    explicit Report_manager(struct classArr data, QWidget *parent = 0);
    struct reportArr list[100];
    ~Report_manager();

private:
    Ui::Report_manager *ui;
    void set_report();
    void show_report(int num);
    classArr test;
    int report_count;
    Api_http *api_http;
    Report_form *item[10];

private slots:
    void slot_create();
    void slot_submit(QModelIndex idx);
    void slot_renwwal();
    void slot_click_mod(int num);
    void slot_click_del(int num);
    void slot_item_clicked(QListWidgetItem*);
    void slot_Get_Reply(QNetworkReply* re);
    void get_Report_List(QString data);
};

#endif // REPORT_MANAGER_H
