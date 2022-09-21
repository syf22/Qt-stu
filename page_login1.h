#ifndef PAGE_LOGIN1_H
#define PAGE_LOGIN1_H

#include <QWidget>

namespace Ui {
class page_login1;
}

class page_login1 : public QWidget
{
    Q_OBJECT

public:
    explicit page_login1(QWidget *parent = nullptr);
    ~page_login1();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
 signals:
    void sendloginsuccess();
private:
    Ui::page_login1 *ui;
};

#endif // PAGE_LOGIN1_H
