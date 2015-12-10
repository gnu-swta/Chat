#include "submit_form.h"
#include "ui_submit_form.h"

Submit_form::Submit_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Submit_form)
{
    ui->setupUi(this);
    ui->file_name->installEventFilter(this);
    connect(this,SIGNAL(click()),SLOT(slotClickFile()));
}

void Submit_form::slotClickFile()
{
    qDebug()<<"클릭했네";
    emit upload(ui->file_name->text());
}

Submit_form::~Submit_form()
{
    delete ui;
}

void Submit_form::set_info(int num, QString studentName, QString fileName, QString subDate)
{
    if(num%2) this->setStyleSheet("background:rgb(226,233,246)");
    else this->setStyleSheet("background:rgb(255,255,255)");

    QString number;
    ui->number->setText(number.setNum(num));
    ui->student_info->setText(studentName);
    ui->file_name->setText(fileName);
    ui->date->setText(subDate);
}


bool Submit_form::eventFilter(QObject *ob, QEvent *event)
{
    if(event->type()==QMouseEvent::MouseButtonPress)
        emit click();
}
