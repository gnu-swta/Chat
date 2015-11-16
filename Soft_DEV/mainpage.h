#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

namespace Ui {
class mainPage;
}

class mainPage : public QWidget
{
    Q_OBJECT

public:
    explicit mainPage(QWidget *parent = 0);
    ~mainPage();

private:
    Ui::mainPage *ui;
    void setMainpage(int number);
    void initConnect();

private slots:
    void slotClickReport();
    void slotClickSet();
    void slotClickChat();
};

#endif // MAINPAGE_H
