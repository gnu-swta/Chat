#include "submit_manager.h"
#include "ui_submit_manager.h"

Submit_manager::Submit_manager(struct reportArr report, struct classArr data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Submit_manager)
{
    ui->setupUi(this);

    QString parameter;

    test = data;
    listCnt = 0;

    parameter.append(report.pk_report+"/");
    parameter.append(test.token);

    api_http = new Api_http;

    connect(api_http,SIGNAL(getReply(QNetworkReply*)),this,SLOT(slotGetReply(QNetworkReply*)));
    api_http->get_url(DONCARE,GET_SUMMIT_LIST,parameter,2);

    ui->user_name->setText(test.userName);
    ui->class_name->setText(test.className);
}

Submit_manager::~Submit_manager()
{
    delete ui;
}

void Submit_manager::slotGetReply(QNetworkReply *re)
{
    QString getData;
    getData = QString(re->readAll());


    qDebug()<<getData;
    getSummitList(getData);

}

void Submit_manager::getSummitList(QString data)
{
    QStringList para = api_http->getParsData(data);
    int i = 0;

    for(i=0;i<para.size();)
    {
        if(para.at(i)==PK_REPORTSUBMIT)
        {list[listCnt].pk_reportSubmit = para.at(++i);}

        // 위와 같은 학번이므로 생략
        else if(para.at(i)==FK_STUDENT)
        {list[listCnt].fk_student = para.at(++i);}

        else if(para.at(i)==FK_REPORT)
        {list[listCnt].fk_report = para.at(++i);}

        else if(para.at(i)==TIME)
        {list[listCnt].time = para.at(++i);}

        else if(para.at(i)==FILEURL)
        {list[listCnt].fileURL = para.at(++i);}

        else if(para.at(i)==EXTENSION)
        {list[listCnt].extension = para.at(++i);}

        else if(para.at(i)==MODIFIED)
        {list[listCnt].modified = para.at(++i);}

        else if(para.at(i)==OPENED)
        {list[listCnt++].opened = para.at(++i);}
        i++ ;
    }

    set_submit();
}

void Submit_manager::set_submit()
{
    // 서버로부터 학생들의 정보와 제출여부를 받아온다.

    Submit_form *student;
    QString fileName;
    int i = 0;

    for(i=0;i<listCnt;i++)
    {
        student = new Submit_form();

        fileName.append(list[i].fk_student);
        fileName.append(".");
        fileName.append(list[i].fileURL);

        student->set_info(list[i].pk_reportSubmit, list[i].fk_student,fileName,list[i].time);
        show_submit(student);
    }
}

void Submit_manager::show_submit(Submit_form *student)
{
    // 학생들의 정보와 제출여부를 화면에 출력한다.

    QListWidgetItem *subject = new QListWidgetItem();

    ui->student_list->addItem(subject);
    ui->student_list->setItemWidget(subject, student);
}

void Submit_manager::down_report()
{
    // 학생이 업로드한 레포트를 다운로드한다.
}
