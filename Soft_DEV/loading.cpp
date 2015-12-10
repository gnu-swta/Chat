#include "loading.h"
#include "ui_loading.h"

Loading::Loading(QWidget *parent) :
    QWidget(0, Qt::FramelessWindowHint),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
    this->setAutoFillBackground(true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
}


void Loading::setTxt(QString txt)
{
    ui->label->setText(txt);
}

Loading::~Loading()
{
    qDebug()<<"quit load";
    delete ui;
}
