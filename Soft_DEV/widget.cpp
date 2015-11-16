#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->login_btn, SIGNAL(clicked()),this,SLOT(slotClickLoginBtn()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::slotClickLoginBtn()
{
    mainpage = new mainPage();
    this->setHidden(true);
    mainpage->show();
}
