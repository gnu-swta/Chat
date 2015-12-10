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
    id=id;

    connect(ui->button_upload, SIGNAL(clicked(bool)), this, SLOT(on_Button_FileUpload_clicked()));
    connect(&timer,SIGNAL(timeout()),this,SLOT(slotTimeout()));
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

    QRegExp parseType(".");

     QStringList parameter;
     parameter=filename.split(parseType,QString::SkipEmptyParts);

     QString fileText;
     fileText.append(id);
     fileText.append(".");
     fileText.append(parameter.at(1));

     ui->filename->setText(fileText);

     load = new Loading();
     setWindowOpacity(0.8);
     load->show();
     timer.start(2000);
}

void EachReport::slotTimeout()
{
    timer.stop();
    load->close();
}
