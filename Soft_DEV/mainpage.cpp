#include "mainpage.h"
#include "ui_mainpage.h"


mainPage::mainPage(QString stdNum, QString loginData, QWidget *parent) :
    QWidget(0),
    ui(new Ui::mainPage)
{
    Q_UNUSED(parent);

    ui->setupUi(this);
    initConnect();
    setStudentNumber(stdNum);
    setClassInfo(loginData);
    setMainpage(1);
    setStudentInfo("정영문","2009011086");
    http_api = new Api_http();
    connect(http_api,SIGNAL(getReply(QNetworkReply*)),this,SLOT(slotGetReply(QNetworkReply*)));
    QString parameter;
    parameter.append(studentNum+" ");
    parameter.append("Bearer ");
    parameter.append(token);


    http_api->get_url(STUDENT,POST_USER,parameter,3);
}

mainPage::~mainPage()
{
    delete ui;
}

void mainPage::setStudentNumber(QString stnm)
{
    studentNum = stnm;
    // 메인위젯 채팅버튼 액티브 초기화
    ui->chat_btn->setStyleSheet(QStringLiteral("QPushButton#chat_btn{border-image: url(:/res/res/chat_c.png);}"));
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
    ui->chat_btn->setStyleSheet(QStringLiteral("QPushButton#chat_btn{border-image: url(:/res/res/chat_c.png);}"));
    ui->report_btn->setStyleSheet(QStringLiteral("QPushButton#report_btn{border-image: url(:/res/res/report_o.png);}"));
    ui->set_btn->setStyleSheet(QStringLiteral("QPushButton#set_btn{border-image: url(:/res/res/set_o.png);}"));
}

void mainPage::slotClickReport()
{
    setMainpage(2);
    ui->chat_btn->setStyleSheet(QStringLiteral("QPushButton#chat_btn{border-image: url(:/res/res/chat_o.png);}"));
    ui->report_btn->setStyleSheet(QStringLiteral("QPushButton#report_btn{border-image: url(:/res/res/report_c.png);}"));
    ui->set_btn->setStyleSheet(QStringLiteral("QPushButton#set_btn{border-image: url(:/res/res/set_o.png);}"));
}

void mainPage::slotClickSet()
{
    setMainpage(3);
    ui->chat_btn->setStyleSheet(QStringLiteral("QPushButton#chat_btn{border-image: url(:/res/res/chat_o.png);}"));
    ui->report_btn->setStyleSheet(QStringLiteral("QPushButton#report_btn{border-image: url(:/res/res/report_o.png);}"));
    ui->set_btn->setStyleSheet(QStringLiteral("QPushButton#set_btn{border-image: url(:/res/res/set_c.png);}"));
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
    static int item_idx=0;

    subject->setIcon(QIcon(":/res/res/subject.png"));
    subject->setText(className);

    item_idx++;

    ui->chat_list->addItem(subject);

    // 짝수번 인덱스 아이템은 배경 변경
    if(item_idx%2==1)
        ui->chat_list->item(item_idx-1)->setBackgroundColor(QColor(226,233,246));
}

void mainPage::addReportList(QString className)
{
    QListWidgetItem *subject = new QListWidgetItem();
    static int item_idx=0;

    item_idx++;

    subject->setIcon(QIcon(":/res/res/subject.png"));
    subject->setText(className);

    ui->report_list->addItem(subject);

    // 짝수번 인덱스 아이템은 배경 변경
    if(item_idx%2==1)
        ui->report_list->item(item_idx-1)->setBackgroundColor(QColor(226,233,246));
}

void mainPage::setToken(QString tk)
{
   token = tk;
}

void mainPage::slotClickChatList(QModelIndex idx)
{
    /*
     * 클릭된 리스트의 위치를 획득 후 해당 리스트 아이템의 이름을
     * 얻는 함수
     */
    int clicked_idx = idx.row();
    QString subject_name = classInfo[clicked_idx].className;

    chatpage = new ChatPage(subject_name, "jym","2009011086");
    chatpage->show();
}

void mainPage::setStudentInfo(QString name, QString stdID)
{
    // 로그인한 학생의 정보를 화면 우측상단에 출력
    ui->stdIDLB->setText(stdID);
    ui->nameLB->setText(name);
}

void mainPage::setClassInfo(QString data)
{
    QStringList para = getParsData(data);
    int i = 0;
    classCnt = 0;

    // 서버에서 받아온 토근 저장
    if(para.at(0)=="jwt")
        setToken(para.at(1));

    for(i=2;i<para.size();)
    {
        if(para.at(i)==PK_CLASS)
        {classInfo[classCnt].classNum = para.at(++i);}

        else if(para.at(i)==NAME)
        {classInfo[classCnt].className = para.at(++i);}

        else if(para.at(i)==GROUP)
        {classInfo[classCnt].classRoomNum = para.at(++i);}

        else if(para.at(i)==CLASSTIME)
        {
            if(para.at(++i) == NON_CLASSTIME)
                classInfo[classCnt++].classTime = " ";
            else
                classInfo[classCnt++].classTime = para.at(i);
        }

        i++ ;
    }

    showClassList();
}

QStringList mainPage::getParsData(QString data)
{
    QRegExp parseType("("+QRegExp::escape(":[{")+"|"+
                      QRegExp::escape("}]}")+"|"+
                      QRegExp::escape("\",\"")+"|"+
                      QRegExp::escape("\":")+"|"+
                      QRegExp::escape("},{")+"|"+
                      QRegExp::escape(",\"")+"|"+
                      QRegExp::escape("\”")+"|"+
                      QRegExp::escape("\"")+"|"+
                      QRegExp::escape("{")+"|"+
                      QRegExp::escape("}")+")");

     QStringList parameter;
     parameter=data.split(parseType,QString::SkipEmptyParts);

     return parameter;
}

void mainPage::showClassList()
{
    int i=0;
    QString class_info;

    for(i=0;i<classCnt;i++)
    {
        class_info = makeListString(i);
        addChatList(class_info);

        addReportList(class_info);
    }

}

QString mainPage::makeListString(int idx)
{
    QString classIF = classInfo[idx].className+"\n"+"     "+classInfo[idx].classTime;
    return classIF;
}

void mainPage::slotGetReply(QNetworkReply *re)
{

    QString getData;

    if(re->error()==QNetworkReply::NoError)
    {
        // 에러가 없을경우
        getData = QString(re->readAll());
        qDebug()<<getData;

    }

    else
    {
        // 에러가 있을경우
        qDebug()<<"Reply Error!";
        getData = QString(re->readAll());
        qDebug()<<getData;
    }
}
