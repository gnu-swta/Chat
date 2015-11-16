#ifndef CHATCONTEXTLISTITEM_H
#define CHATCONTEXTLISTITEM_H

#include <QWidget>
#include <QDebug>

namespace Ui {
class ChatcontextlistItem;
}

class ChatcontextlistItem : public QWidget
{
    Q_OBJECT

public:
    explicit ChatcontextlistItem(QWidget *parent = 0);
    ~ChatcontextlistItem();

    void setContextInfo(QString name, QString major, QString ID, QString context,
                        QString hash, int hash_type);

private:
    Ui::ChatcontextlistItem *ui;
};

#endif // CHATCONTEXTLISTITEM_H
