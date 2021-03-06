#include "subjectreport.h"
#include "ui_subjectreport.h"
#include "qcheckbox.h"
#include "qfiledialog.h"
#include "eachreport.h"

SubjectReport::SubjectReport(struct classArr data,QWidget *parent):QMainWindow(parent),ui(new Ui::SubjectReport)
{
    ui->setupUi(this);
    test = data;
    api_http = new Api_http;
    connect(api_http, SIGNAL(getReply(QNetworkReply*)), this, SLOT(slot_Get_Reply(QNetworkReply*)));

    QString parameter;

    parameter.append(data.classNum+"/");
    parameter.append(data.token);

    api_http->get_url(DONCARE,GET_REPORTLIST,parameter,2);
    ui->class_2->setText(data.className);
    ui->id->setText(data.id);

    qDebug()<<data.id;
    qDebug()<<data.className;
    connect(&timer,SIGNAL(timeout()),this,SLOT(slotTimeout()));
}

SubjectReport::~SubjectReport()
{
    delete ui;
}


void SubjectReport::slot_Get_Reply(QNetworkReply *re)
{
    QString getData;

    if(re->error()==QNetworkReply::NoError)
    {
        // 에러가 없을경우
        getData = QString(re->readAll());
        get_Report_List(getData);
    }
    else
    {
        // 에러가 있을경우
        qDebug()<<"Reply Error!";
    }
}

void SubjectReport::get_Report_List(QString data)
{
    QStringList para = api_http->getParsData(data);
    int i;


    report_count = 0;

    for(i = 0;i < para.size();)
    {
        if(para.at(i)==PK_REPORT)
        {list[report_count].pk_report = para.at(++i);}

        // 위와 같은 학번이므로 생략
        else if(para.at(i)==FK_CLASS)
        {list[report_count].fk_class = para.at(++i);}

        else if(para.at(i)==TITLE)
        {list[report_count].title = para.at(++i);}

        else if(para.at(i)==INDEX)
        {list[report_count].index = para.at(++i);}

        else if(para.at(i)==START)
        {list[report_count].start = para.at(++i);}

        else if(para.at(i)==DEADLINE)
        {list[report_count++].deadline = para.at(++i);}
        i++ ;
    }

    set_report();

}

void SubjectReport::show_report(int num)
{
    // 레포트 리스트를 화면에 출력한다.

    QListWidgetItem *subject = new QListWidgetItem();
    subject->setSizeHint(QSize(0,35));

    ui->listWidget->addItem(subject);
    ui->listWidget->setItemWidget(subject, item[num]);
}

void SubjectReport::set_report()
{
    // 서버로부터 강의의 정보를 가지고 과제 리스트를 받아온다.
    // 레포트 명, 레포트 기간
    int num = 0;
    QListWidgetItem *subject = new QListWidgetItem();
    subject->setSizeHint(QSize(0,50));

    while(num != report_count)
    {
        item[num] = new EachReport(num, list[num].title,  list[num].start+list[num].deadline,test.id);
        connect(item[num],SIGNAL(upload()),this,SLOT(slot_upload()));
        show_report(num);
        num++;
    }
}

void SubjectReport::slot_upload()
{
    load = new Loading();
    load->setTxt("레포트 업로드중...");
    setWindowOpacity(0.8);
    load->show();
    timer.start(2000);
}

void SubjectReport::slotTimeout()
{
    load->close();
    setWindowOpacity(1.0);
    timer.stop();
}

