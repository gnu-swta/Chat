#include "submit_form.h"
#include "ui_submit_form.h"

Submit_form::Submit_form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Submit_form)
{
    ui->setupUi(this);
    connect(ui->file_name,SIGNAL(clicked()),SLOT(slotClickFile()));
}

void Submit_form::slotClickFile()
{

}

Submit_form::~Submit_form()
{
    delete ui;
}

void Submit_form::set_info(QString number, QString studentName, QString fileName, QString subDate)
{
    int num = number.toInt();

    if(num%2) this->setStyleSheet("background:rgb(226,233,246)");
    else this->setStyleSheet("background:rgb(255,255,255)");

    ui->number->setText(number);
    ui->student_info->setText(studentName);
    ui->file_name->setText(fileName);
    ui->date->setText(subDate);
}
