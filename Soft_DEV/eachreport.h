#ifndef EACHREPORT_H
#define EACHREPORT_H

#include <QWidget>
#include "loading.h"
#include <QTimer>

namespace Ui {
class EachReport;
}

class EachReport : public QWidget
{
    Q_OBJECT

public:
    explicit EachReport(int num, QString subject, QString time, QString id, QWidget *parent = 0);
    ~EachReport();
    QString ConvertKor(char *str);

private:
    Ui::EachReport *ui;
    QString id;
    Loading *load;
    QTimer timer;

private slots:
    void on_Button_FileUpload_clicked();
    void slotTimeout();
};

#endif // EACHREPORT_H
