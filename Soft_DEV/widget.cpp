#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    initPointer();
    connect(ui->login_btn, SIGNAL(clicked()),this,SLOT(slotClickLoginBtn()));
    connect(login,SIGNAL(getReply(QNetworkReply*)),this, SLOT(slotGetReply(QNetworkReply*)));
}

Widget::~Widget()
{
    delete ui;
    delete mainpage;
}

void Widget::initPointer()
{
    login = new Api_http();
}

void Widget::slotClickLoginBtn()
{
    QString stdNum = ui->id->text();
    QString passwd = ui->pw->text();

    QString parameters;

    parameters.append("student ");
    parameters.append(stdNum);
    parameters.append(" ");

    parameters.append("passwd ");
    parameters.append(passwd);

    login->post_url(STUDENT,POST_LOGIN, parameters ,4);
}

void Widget::slotGetReply(QNetworkReply *re)
{

    QString getData;

    if(re->error()==QNetworkReply::NoError)
    {
        // 에러가 없을경우

        QString stdNum = ui->id->text();
        getData = QString(re->readAll());

        qDebug()<<getData;

        mainpage = new mainPage(stdNum,getData);
        this->setHidden(true);
        mainpage->show();
    }
    else
    {
        // 에러가 있을경우
        qDebug()<<"Reply Error!";
    }


}
