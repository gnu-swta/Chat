#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(0, Qt::FramelessWindowHint),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    initPointer();
    connect(ui->login_btn, SIGNAL(clicked()),this,SLOT(slotClickLoginBtn()));
    connect(login,SIGNAL(getReply(QNetworkReply*)),this, SLOT(slotGetReply(QNetworkReply*)));
    connect(ui->id, SIGNAL(returnPressed()), this, SLOT(slotReturnPress()));
    connect(ui->pw, SIGNAL(returnPressed()), this, SLOT(slotClickLoginBtn()));
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



    // 학생 모드일경우
    if(ui->type->currentIndex() == STD)
    {
        parameters.append("student/");
        parameters.append(stdNum);
        parameters.append("/");

        parameters.append("passwd/");
        parameters.append(passwd);
        login->post_url(STUDENT,POST_LOGIN, parameters, NULL ,4,HEADER_NON);
    }
    // 교수 모드일경우
    else
    {
        parameters.append("professor/");
        parameters.append(stdNum);
        parameters.append("/");

        parameters.append("passwd/");
        parameters.append(passwd);
        login->post_url(PROFESSOR,POST_LOGIN, parameters, NULL ,4,HEADER_NON);
    }
    load = new Loading();
    setWindowOpacity(0.8);
    load->show();
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

        mainpage = new mainPage(ui->type->currentIndex(),stdNum,getData);
        this->setHidden(true);
        mainpage->show();
        load->close();
    }
    else
    {
        // 에러가 있을경우
        qDebug()<<"Reply Error!";
        ui->guide->setText("로그인 실패입니다. 다시 로그인해주세요.");

        load->hide();
        setWindowOpacity(1);
    }
}

void Widget::slotReturnPress()
{
    ui->pw->setFocus();
}
