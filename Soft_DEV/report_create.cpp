#include "report_create.h"
#include "ui_report_create.h"

Report_create::Report_create(struct classArr data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Report_create)
{
    ui->setupUi(this);

    test = data;

    ui->user_name->setText(test.userName);
    ui->class_name->setText(test.className);

    api_http = new Api_http();
    connect(ui->add, SIGNAL(clicked()), this, SLOT(slot_create()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(slot_cancel()));
}

Report_create::Report_create(classArr data, Report_form *ori, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Report_create)
{
    ui->setupUi(this);

    test = data;

    ui->user_name->setText(test.userName);
    ui->class_name->setText(test.className);
    ui->add->setText("수정");

    connect(ui->add, SIGNAL(clicked()), this, SLOT(slot_create()));
    connect(ui->cancel, SIGNAL(clicked()), this, SLOT(slot_cancel()));
}

Report_create::~Report_create()
{
    delete ui;
}

void Report_create::slot_create()
{
    // 레포트를 등록한다.

    set_report();

    this->close();
}

void Report_create::slot_cancel()
{
    // 레포트 생성 위젯을 종료한다.

    this->close();
}

void Report_create::set_report()
{
    // 서버로 입력받은 레포트의 정보를 저장한다.

    QString parameters;
    QString header;

    header.append(test.token);

    parameters.append("title/");
    parameters.append(ui->report_name->text());
    parameters.append("/");
    parameters.append("fk_class/");
    parameters.append(test.classNum);
    parameters.append("/");
    parameters.append("start/");
    parameters.append(ui->start_date->dateTime().toString());
    parameters.append("/");
    parameters.append("deadline/");
    parameters.append(ui->end_date->dateTime().toString());
    parameters.append("/");
    api_http->post_url(DONCARE,POST_REGISTER_REPORT,parameters,header,8,HEADER_INCLUDE);
}
