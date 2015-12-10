#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "classinfo.h"
#include "api_http.h"
#include "type.h"
#include "loading.h"
#include "mainpage.h"

#define STD     0
#define PRFS   1

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
    Api_http *login;
    Loading *load;

    void initPointer();

private slots:
    void slotClickLoginBtn();
    void slotGetReply(QNetworkReply* re);
    void slotReturnPress();
};

#endif // WIDGET_H
