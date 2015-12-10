#ifndef REPORT_FORM_H
#define REPORT_FORM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class Report_form;
}

class Report_form : public QWidget
{
    Q_OBJECT

public:
    explicit Report_form(int number, QWidget *parent = 0);

    ~Report_form();
    void set_info(int num, QString name, QString s_date, QString e_date);

signals:
    void click_modify(int num);
    void click_del(int num);

private slots:
    void slotClick_modify();
    void slotClick_del();

private:
    Ui::Report_form *ui;
    int num;
};

#endif // REPORT_FORM_H
