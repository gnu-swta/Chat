#ifndef SUBMIT_FORM_H
#define SUBMIT_FORM_H

#include <QWidget>
#include <QDebug>
#include <QMouseEvent>


namespace Ui {
class Submit_form;
}

class Submit_form : public QWidget
{
    Q_OBJECT

public:
    explicit Submit_form(QWidget *parent = 0);
    ~Submit_form();
    void set_info(int num, QString studentName, QString fileName, QString subDate);
    virtual bool eventFilter(QObject *ob, QEvent *event);

private:
    Ui::Submit_form *ui;

private slots:
    void slotClickFile();

signals:
    void click();
    void upload(QString fileName);
};

#endif // SUBMIT_FORM_H
