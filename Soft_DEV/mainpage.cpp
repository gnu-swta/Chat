#include "mainpage.h"
#include "ui_mainpage.h"


mainPage::mainPage(int type, QString stdNum, QString loginData, QWidget *parent) :
    QWidget(0),
    ui(new Ui::mainPage)
{
    Q_UNUSED(parent);

    // 누가 로그인했는지 판단
    who = type;

    ui->setupUi(this);
    initConnect();
    setStudentNumber(stdNum);
    setClassInfo(loginData);
    requireStudentInfo();
}

mainPage::~mainPage()
{
    qDebug()<<"Bye";
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
    // UI 초기화 ( 채팅화면 출력 )
    setMainpage(1);

    // 통신을 위한 객체 생성
    http_api = new Api_http();

    connect(ui->chat_btn,   SIGNAL(clicked()),this, SLOT(slotClickChat()));
    connect(ui->report_btn, SIGNAL(clicked()),this, SLOT(slotClickReport()));
    connect(ui->set_btn,    SIGNAL(clicked()),this, SLOT(slotClickSet()));
    connect(ui->chat_list,  SIGNAL(doubleClicked(QModelIndex)), this, SLOT(slotClickChatList(QModelIndex)));
    connect((ui->report_list),SIGNAL(doubleClicked(QModelIndex)),this,SLOT(slotClickReportList(QModelIndex)));
    connect(http_api,SIGNAL(getReply(QNetworkReply*)),this,SLOT(slotGetReply(QNetworkReply*)));
}

void mainPage::slotClickReportList(QModelIndex idx)
{
    int current_idx = idx.row();
    classInfo[current_idx].token = token;
    classInfo[current_idx].userName = studentInfo.name;
    classInfo[current_idx].id       = studentInfo.studentID;

    // 학생인경우
    if(who == PRFS)
    {
        SubjectReport *new_window = new SubjectReport(classInfo[current_idx]);
        new_window->show();
    }

    // 교수인 경우
    else
    {
        Report_manager *reg = new Report_manager(classInfo[current_idx]);
        reg->show();
    }
}


void mainPage::slotClickChat()
{
    qDebug()<<"quit";
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

    chatInfo.token      = token;
    chatInfo.className  = classInfo[clicked_idx].className;
    chatInfo.stdID      = studentInfo.studentID;
    chatInfo.name       = studentInfo.name;
    chatInfo.fkClass    = classInfo[clicked_idx].classNum;

    chatpage = new ChatPage(chatInfo);
    connect(chatpage,SIGNAL(successGetdata()),this,SLOT(slotShowChatpage()));

}

void mainPage::slotShowChatpage()
{chatpage->show();}

void mainPage::setStudentInfo(QString name, QString stdID, QString depart)
{
    // 로그인한 학생의 정보를 화면 우측상단에 출력
    ui->stdIDLB->setText(stdID);
    ui->nameLB->setText(name);
    ui->depart->setText(depart);
}

void mainPage::setClassInfo(QString data)
{
    QStringList para = http_api->getParsData(data);
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
// 서버로부터 학생정보 요청
void mainPage::requireStudentInfo()
{
    QString parameter;
    parameter.append(studentNum+"/");
    parameter.append(token);

    http_api->get_url(STUDENT,GET_USER,parameter,2);
}

// 서버로부터 학생 정보를 얻음
void mainPage::getStudentInfo(QString data)
{
    QStringList para = http_api->getParsData(data);
    int i = 0;

    for(i=0;i<para.size();)
    {
        if(para.at(i)==PK_STUDENT)
        {studentInfo.studentID = para.at(++i);}

        // 위와 같은 학번이므로 생략
        else if(para.at(i)==NUMBER)
        {(++i);}

        else if(para.at(i)==NAME)
        {studentInfo.name = para.at(++i);}

        else if(para.at(i)==DEPARTMENT)
        {studentInfo.department = para.at(++i);}
        i++ ;
    }

    // 학생 정보 출력
    setStudentInfo(studentInfo.name,studentInfo.studentID,studentInfo.department);

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
        studentData = getData;
        getStudentInfo(studentData);
    }

    else
    {
        // 에러가 있을경우
        qDebug()<<"Reply Error!";
    }
}
