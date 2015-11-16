#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mainpage.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    mainPage *mainpage;

private slots:
    void slotClickLoginBtn();
};

#endif // WIDGET_H
