#include "mainpage.h"
#include "ui_mainpage.h"

mainPage::mainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainPage)
{
    ui->setupUi(this);
    setMainpage(1);
}

mainPage::~mainPage()
{
    delete ui;
}

void mainPage::initConnect()
{
    connect(ui->chat_btn,   SIGNAL(clicked()),this, SLOT(slotClickChat()));
    connect(ui->report_btn, SIGNAL(clicked()),this, SLOT(slotClickReport()));
    connect(ui->set_btn,    SIGNAL(clicked()),this, SLOT(slotClickSet()));
}


void mainPage::slotClickChat()
{
    setMainpage(1);
}

void mainPage::slotClickReport()
{
    setMainpage(2);
}

void mainPage::slotClickSet()
{
    setMainpage(3);
}

void mainPage::setMainpage(int number)
{
    // 초기화면 설정 : 채팅 목록 선택하는 화면
    // 나머지는 다 숨김모드
    ui->chat_list->setVisible(!(1==number));
    ui->report_list->setVisible(!(2==number));
    ui->set_list->setVisible(!(3==number));
}
