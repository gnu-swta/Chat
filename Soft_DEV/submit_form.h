#ifndef SUBMIT_FORM_H
#define SUBMIT_FORM_H

#include <QWidget>

namespace Ui {
class Submit_form;
}

class Submit_form : public QWidget
{
    Q_OBJECT

public:
    explicit Submit_form(QWidget *parent = 0);
    ~Submit_form();
    void set_info(QString number, QString studentName, QString fileName, QString subDate);

private:
    Ui::Submit_form *ui;

private slots:
    void slotClickFile();
};

#endif // SUBMIT_FORM_H
