#include "eachreport.h"
#include "ui_eachreport.h"
#include "qfiledialog.h"

EachReport::EachReport(int num, QString subject, QString time, QString id,QWidget *parent):QWidget(parent),ui(new Ui::EachReport)
{
    ui->setupUi(this);

    if(num%2) this->setStyleSheet("background:rgb(226,233,246)");
    else this->setStyleSheet("background:rgb(255,255,255)");

    ui->label_num->setText(QString("%1").arg(num));
    ui->label_subject->setText(subject);
    ui->label_time->setText(time);
    sid=id;

    qDebug()<<id;

    connect(ui->button_upload, SIGNAL(clicked(bool)), this, SLOT(on_Button_FileUpload_clicked()));

}

EachReport::~EachReport()
{
    delete ui;
}

QString EachReport::ConvertKor(char *str)
{
   QString korStr = QString::fromUtf8(str);
   return korStr;
}

void EachReport::on_Button_FileUpload_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this,tr("Select file"), "/home/", tr("All Files (*.*)"));
    qDebug()<<filename;
    int i = 0;
    for(i=0;i<filename.length();i++)
        if(filename.at(i)=='.')
            break;

    qDebug()<<i;
    qDebug()<<filename.mid(i);

     QString fileText;
     fileText.append(sid);
     fileText.append(filename.mid(i));

     ui->filename->setText(fileText);

     emit upload();
}
