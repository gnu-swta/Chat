#include "mainpage.h"
#include "ui_mainpage.h"


mainPage::mainPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainPage)
{
    ui->setupUi(this);
    initConnect();
    setMainpage(1);
    setStudentInfo("정영문","2009011086");
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
    connect(ui->chat_list,  SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotClickChatList(QModelIndex)));
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
    ui->chat_list->setVisible((CLICK_CHAT==number));
    ui->report_list->setVisible((CLICK_REPORT==number));
    ui->set_list->setVisible((CLICK_SET==number));
}

void mainPage::addChatList(QString className)
{
    QListWidgetItem *subject = new QListWidgetItem();

    subject->setIcon(QIcon(":/res/res/subject.png"));
    subject->setText(className);

    ui->chat_list->addItem(subject);
}

void mainPage::addReportList(QString className)
{
    QListWidgetItem *subject = new QListWidgetItem();

    subject->setIcon(QIcon(":/res/res/subject.png"));
    subject->setText(className);

    ui->report_list->addItem(subject);
}

void mainPage::slotClickChatList(QModelIndex idx)
{
    /*
     * 클릭된 리스트의 위치를 획득 후 해당 리스트 아이템의 이름을
     * 얻는 함수
     */
    int clicked_idx = idx.row();
    QString subject_name = ui->chat_list->item(clicked_idx)->text();

    chatpage = new ChatPage(subject_name, "jym","2009011086");
    chatpage->show();
}

void mainPage::setStudentInfo(QString name, QString stdID)
{
    // 로그인한 학생의 정보를 화면 우측상단에 출력
    ui->stdIDLB->setText(stdID);
    ui->nameLB->setText(name);
}

void mainPage::setClassInfo(classArr csInfo)
{
    classInfo[classCnt].className       = csInfo.className;
    classInfo[classCnt].classNum        = csInfo.classNum;
    classInfo[classCnt].classRoomNum    = csInfo.classRoomNum;
    classInfo[classCnt++].classTime     = csInfo.classTime;
}

void mainPage::showClassList()
{
    int i=0;
    QString class_info;

    qDebug() << classCnt;
    for(i=0;i<classCnt;i++)
    {
        class_info = makeListString(i);
        addChatList(class_info);
        addReportList(class_info);
    }
}

QString mainPage::makeListString(int idx)
{
    QString classIF = classInfo[idx].className+"["+classInfo[idx].classRoomNum+"]-"+classInfo[idx].classTime;;
    return classIF;
}
