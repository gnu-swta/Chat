#include "report_manager.h"
#include "ui_report_manager.h"

Report_manager::Report_manager(struct classArr data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Report_manager)
{
    ui->setupUi(this);

    test = data;
    report_count = 0;

    ui->user_name->setText(data.userName);
    ui->class_name->setText(data.className);

    //set_report();

    api_http = new Api_http;

    QString parameter;

    parameter.append(test.classNum+"/");
    parameter.append(test.token);

    api_http->get_url(DONCARE,GET_REPORTLIST,parameter,2);

    connect(ui->report_create, SIGNAL(clicked()), this, SLOT(slot_create()));
    connect(ui->renewal, SIGNAL(clicked()), this, SLOT(slot_renwwal()));
    connect(ui->report_list, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slot_submit(QModelIndex)));
    connect(api_http, SIGNAL(getReply(QNetworkReply*)), this, SLOT(slot_Get_Reply(QNetworkReply*)));

}

Report_manager::~Report_manager()
{
    delete ui;
}

void Report_manager::slot_item_clicked(QListWidgetItem *)
{
    qDebug()<<"itmes";
}

void Report_manager::slot_renwwal()
{
    // 레포트 리스트를 갱신한다.

    ui->report_list->clear();
    ui->report_list->clear();
    QString parameter;

    parameter.append(test.classNum+"/");
    parameter.append(test.token);

    api_http->get_url(DONCARE,GET_REPORTLIST,parameter,2);

}

void Report_manager::slot_create()
{
    // 레포트를 생성하는 위젯을 생성한다.

    Report_create *r_create = new Report_create(test);
    r_create->show();
}

void Report_manager::slot_submit(QModelIndex idx)
{
    // 레포트 제출관리하는 위젯을 생성한다.

    Submit_manager *s_manager = new Submit_manager(list[idx.row()],test);
    s_manager->show();
}

void Report_manager::slot_Get_Reply(QNetworkReply *re)
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

void Report_manager::get_Report_List(QString data)
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

void Report_manager::set_report()
{
    // 서버로부터 강의의 정보를 가지고 과제 리스트를 받아온다.
    // 레포트 명, 레포트 기간
    int num = 0;

    while(num != report_count)
    {
        item[num] = new Report_form(num);
        item[num]->set_info(num, list[num].title, list[num].start, list[num].deadline);

        show_report(num);
        connect(item[num], SIGNAL(click_modify(int)), this, SLOT(slot_click_mod(int)));
        connect(item[num], SIGNAL(click_del(int)), this, SLOT(slot_click_del(int)));
        num++;
    }
}

void Report_manager::show_report(int num)
{
    // 레포트 리스트를 화면에 출력한다.

    QListWidgetItem *subject = new QListWidgetItem();
    subject->setSizeHint(QSize(0,35));

    ui->report_list->addItem(subject);
    ui->report_list->setItemWidget(subject, item[num]);
}

void Report_manager::slot_click_mod(int num)
{
    //Report_create *r_create = new Report_create(test, &list[num]);
   // r_create->show();
}

void Report_manager::slot_click_del(int num)
{
    int i;

    for(i = 0; i < report_count; i++)
    {
        delete ui->report_list->item(i);
    }

    for(i = num; i < report_count - 1; i++)
    {
        list[i] = list[i+1];
    }
    report_count--;

    set_report();
}
