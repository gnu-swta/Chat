#include "chatpage.h"
#include "ui_chatpage.h"

ChatPage::ChatPage(QString sub_name, QString name, QString std_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatPage)
{
    ui->setupUi(this);

    initHachCombo();
    initConnect();

    getStudentInfo(name, std_id);
    setSubjectName(sub_name);
}


ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::getStudentInfo(QString name, QString id)
{
    // 로그인후 사용자의 정보를 저장
    studentName = name;
    studentID   = id;
}


 void ChatPage::setSubjectName(QString name)
 {
     ui->subject_name->setText(name);
 }

 void ChatPage::initHachCombo()
 {
     // 학생용 프로그램에서 사용하는 해시콤보박스 데이터를 입력
     ui->hash_combo->addItem(ALL);
     ui->hash_combo->addItem(SECRET);
     ui->hash_combo->addItem(WHISPER);

     // 초기 해시콤포값을 "전체"로 초기
     ui->hash_view->setText(ui->hash_combo->currentText()+" ");
 }

 void ChatPage::initConnect()
 {
     connect(ui->hash_combo,SIGNAL(currentIndexChanged(QString)),this,SLOT(slotChangeHash(QString)));
     connect(ui->send_chat,SIGNAL(clicked()),this,SLOT(slotClickSendBtn()));
     connect(this,SIGNAL(pressEnterkey()),this,SLOT(slotClickSendBtn()));
     connect(this, SIGNAL(sendMessage(QString,QString)), this, SLOT(slotSendMessage(QString,QString)));
     connect(ui->get_test,SIGNAL(clicked()),this,SLOT(slotGetMessage()));
 }

 void ChatPage::slotChangeHash(QString hash)
 {
     QPalette *palette = new QPalette();
     int idx = ui->hash_combo->currentIndex();

     /*
      * 각 해시별 색깔 부여
      * 전체 : 검정
      * 비밀 : 파랑
      * 귓말 : 빨강
      */

     if(idx == 0) // 전체
        palette->setColor(QPalette::WindowText,Qt::black);

     else if(idx == 1) // 비밀
         palette->setColor(QPalette::WindowText,Qt::blue);

     else if(idx == 2) // 귓말
         palette->setColor(QPalette::WindowText,Qt::red);

     ui->hash_view->setPalette(*palette);
     // 사용자가 해시를 변경하면 해시를 변경
     ui->hash_view->setText(hash);
 }

 void ChatPage::slotClickSendBtn()
 {
     QString msg = ui->write_chat->text();

     ui->write_chat->clear();

     QListWidgetItem *list = new QListWidgetItem();

     Chatcontectlistitem_s *item = new Chatcontectlistitem_s();

     list->setSizeHint(QSize(0,30));
     item->setContextInfo(msg,ui->hash_combo->currentText(),ui->hash_combo->currentIndex());
     ui->veiw_chat->addItem(list);
     ui->veiw_chat->setItemWidget(list,item);

     // 자동 스크롤바 내리
     ui->veiw_chat->scrollToBottom();

     emit sendMessage(msg, studentID);
 }

 void ChatPage::slotSendMessage(QString msg, QString stdID)
 {
     // TCP를 통한 데이터 전송 부분
 }

 void ChatPage::slotGetMessage()
 {
     // 서버로부터 채팅내용을 얻어서 출력해주는 부분
     QString msg = "안녕하세요";

     QListWidgetItem *list = new QListWidgetItem();

     ChatcontextlistItem *item = new ChatcontextlistItem();
     list->setSizeHint(QSize(0,95));

     // set dummy data
     item->setContextInfo("정영문","항공우주정보","2009011086",msg,ui->hash_combo->currentText(),ui->hash_combo->currentIndex());
     ui->veiw_chat->addItem(list);
     ui->veiw_chat->setItemWidget(list,item);

     // 자동 스크롤바 내리기
     ui->veiw_chat->scrollToBottom();
 }


 void ChatPage::keyPressEvent(QKeyEvent *event)
 {
     if(event->key() == ENTERKEY)
         emit pressEnterkey();
 }
