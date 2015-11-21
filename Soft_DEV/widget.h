#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "mainpage.h"
#include "classinfo.h"
#include "api_http.h"
#include "type.h"
#include "loading.h"

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
};

#endif // WIDGET_H
