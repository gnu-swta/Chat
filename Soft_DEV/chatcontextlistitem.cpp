#include "chatcontextlistitem.h"
#include "ui_chatcontextlistitem.h"

ChatcontextlistItem::ChatcontextlistItem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatcontextlistItem)
{
    ui->setupUi(this);
}

ChatcontextlistItem::~ChatcontextlistItem()
{
    delete ui;
}

void ChatcontextlistItem::setContextInfo(QString name, QString major,
                                         QString ID, QString context, QString hash, int hash_type)
{
    QPalette *palette = new QPalette();

    if(hash_type == 0) // 전체
       palette->setColor(QPalette::WindowText,Qt::black);

    else if(hash_type == 1) // 비밀
        palette->setColor(QPalette::WindowText,Qt::blue);

    else if(hash_type == 2) // 귓말
        palette->setColor(QPalette::WindowText,Qt::red);

    qDebug()<<hash_type;

    ui->name_lb->setText(name);
    ui->major_lb->setText(major);
    ui->id_lb->setText(ID);
    ui->context_lb->setText(context);

    ui->hash_lb->setPalette(*palette);
    ui->hash_lb->setText(hash);
}
