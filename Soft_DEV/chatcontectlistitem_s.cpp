#include "chatcontectlistitem_s.h"
#include "ui_chatcontectlistitem_s.h"

Chatcontectlistitem_s::Chatcontectlistitem_s(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Chatcontectlistitem_s)
{
    ui->setupUi(this);
}

Chatcontectlistitem_s::~Chatcontectlistitem_s()
{
    delete ui;
}


void Chatcontectlistitem_s::setContextInfo(QString context, QString hash, int hash_type)
{
    if(hash_type == 0) // 전체
        ui->hash_lb->setText("<font color='black'>"+hash+"</font>");

    else if(hash_type == 1) // 비밀
        ui->hash_lb->setText("<font color='blue'>"+hash+"</font>");

    else if(hash_type == 2) // 귓말     
        ui->hash_lb->setText("<font color='red'>"+hash+"</font>");

    ui->context_lb->setText("<font color='black'>"+context+"</font>");
}
