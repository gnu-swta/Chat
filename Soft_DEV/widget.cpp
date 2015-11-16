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
    struct classArr test[5];
    int i=0;

    // 임시변수
    QString tmp;

    mainpage = new mainPage();

    for(i=0;i<5;i++)
    {
        test[i].className=tmp.setNum(i)+"테스트";
        test[i].classNum = tmp.setNum(i);
        test[i].classRoomNum = tmp.setNum(i+2);
        test[i].classTime = "월8, 9 [024-0175]";

        mainpage->setClassInfo(test[i]);
    }


    mainpage->showClassList();
    this->setHidden(true);
    mainpage->show();
}
