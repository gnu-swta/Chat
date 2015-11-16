#ifndef CHATCONTECTLISTITEM_S_H
#define CHATCONTECTLISTITEM_S_H

#include <QWidget>

namespace Ui {
class Chatcontectlistitem_s;
}

class Chatcontectlistitem_s : public QWidget
{
    Q_OBJECT

public:
    explicit Chatcontectlistitem_s(QWidget *parent = 0);
    ~Chatcontectlistitem_s();
    void setContextInfo(QString context, QString hash, int hash_type);

private:
    Ui::Chatcontectlistitem_s *ui;
};

#endif // CHATCONTECTLISTITEM_S_H
