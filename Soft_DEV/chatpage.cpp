#include "chatpage.h"
#include "ui_chatpage.h"

ChatPage::ChatPage(struct chatArr chatInfo, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatPage)
{
    ui->setupUi(this);

    http_api = new Api_http();
    msgSeq = 0;

    initHachCombo();
    initConnect();
    setChatInfo(chatInfo);


    getStudentInfo(chatInfo.name, chatInfo.stdID);
    setSubjectName(chatInfo.className);
    qDebug()<<"Request date ";
    requestBeforeData(0);

    //timer.start(1000);

}


ChatPage::~ChatPage()
{
    delete ui;
}

void ChatPage::setChatInfo(chatArr chIf)
{
    chatIf = chIf;
}

void ChatPage::getStudentInfo(QString name, QString id)
{
    // 로그인후 사용자의 정보를 저장
    studentName = name;
    studentID   = id;
}

void ChatPage::requestBeforeData(int seq)
{
    QString parameter;
    QString sq;
    parameter.append(chatIf.fkClass+" ");
    parameter.append(chatIf.token+" ");
    parameter.append(sq.setNum(seq));

    http_api->get_url(DONCARE,GET_CHAT,parameter,3);
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
     connect(this, SIGNAL(sendMessage(QString)), this, SLOT(slotSendMessage(QString)));
     connect(http_api,SIGNAL(getReply(QNetworkReply*)),this,SLOT(slotGetMessage(QNetworkReply*)));
     connect(&timer,SIGNAL(timeout()),this,SLOT(slotTimeout()));
     //connect(ui->get_test,SIGNAL(clicked()),this,SLOT(slotGetMessage()));
 }

 void ChatPage::slotTimeout()
 {
     requestBeforeData(msgSeq);
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
     emit sendMessage(msg);
 }

 void ChatPage::slotSendMessage(QString message)
 {
     // TCP를 통한 데이터 전송 부분
     QString header;
     QString msg;
     QString seq;

     header.append(chatIf.token);

     msg.append("msg ");
     msg.append(message);
     msg.append(" ");

     msg.append("fk_class ");
     msg.append(chatIf.fkClass);
     msg.append(" ");

     msg.append("seq ");
     msg.append(seq.setNum(++msgSeq));

     http_api->post_url(DONCARE,POST_CHAT,msg,header,6,HEADER_INCLUDE);
 }

 void ChatPage::slotGetMessage(QNetworkReply *re)
 {
     QString data;

     if(re->error()==QNetworkReply::NoError)
     {
         // 에러가 없을경우
         data = QString(re->readAll());
         getDate(data);
         qDebug()<<data;
     }

     else
     {
         // 에러가 있을경우
         qDebug()<<"Reply Error!";
     }
 }

 void ChatPage::setMessage(msgArr msg, int isMine)
 {
     ui->write_chat->clear();
     QListWidgetItem *list = new QListWidgetItem();



     if(isMine==MINE)
     {
         Chatcontectlistitem_s *item = new Chatcontectlistitem_s();
         list->setSizeHint(QSize(0,30));
         item->setContextInfo(msg.msg,ui->hash_combo->currentText(),ui->hash_combo->currentIndex());
         ui->veiw_chat->addItem(list);
         ui->veiw_chat->setItemWidget(list,item);
     }

     else if(isMine==ANOTHER_PERSON)
     {
         ChatcontextlistItem *item = new ChatcontextlistItem();
         list->setSizeHint(QSize(0,95));
         item->setContextInfo(msg.time,"더미",msg.fkStudent,msg.msg,ui->hash_combo->currentText(),ui->hash_combo->currentIndex());
         ui->veiw_chat->addItem(list);
         ui->veiw_chat->setItemWidget(list,item);
     }

     // 자동 스크롤바 내리
     ui->veiw_chat->scrollToBottom();
 }

 void ChatPage::getDate(QString data)
 {
     QStringList para = http_api->getParsData(data);
     struct msgArr message;


     int i = 0;
     int getFlag=-1;

     for(i=0;i<para.size();)
     {
         if(para.at(i)==PK_CHAT)
         {
             message.pkChat = para.at(++i);
             msgSeq = message.pkChat.toInt();
         }

         else if(para.at(i)==FK_CLASS)
         {message.fkClass = para.at(++i);}

         else if(para.at(i)==FK_STUDENT)
         {message.fkStudent = para.at(++i);}

         else if(para.at(i)==TIME)
         {message.time = para.at(++i);}

         else if(para.at(i)==MESSAGE)
         {
             message.msg = para.at(++i);

             //내가 보낸 메시지일경우
             if(message.fkStudent == chatIf.stdID)
                 getFlag = MINE;
             // 다른사람이 보낸 메시지인경우
             else if(message.fkStudent != chatIf.stdID)
                getFlag = ANOTHER_PERSON;

             setMessage(message,getFlag);
         }

         i++ ;
     }
 }


 void ChatPage::keyPressEvent(QKeyEvent *event)
 {
     if(event->key() == ENTERKEY)
         emit pressEnterkey();
 }
