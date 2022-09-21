#ifndef DLD_ADD_H
#define DLD_ADD_H

#include <QDialog>
#include"stusql.h"

namespace Ui {
class dld_add;
}

class dld_add : public QDialog
{
    Q_OBJECT

public:
    explicit dld_add(QWidget *parent = nullptr);
    ~dld_add();
    void settype(bool isadd,stuinfo info={});
private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::dld_add *ui;
    bool m_isadd;
    stuinfo m_info;
};

#endif // DLD_ADD_H
