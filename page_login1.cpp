#include "page_login1.h"
#include "ui_page_login1.h"

page_login1::page_login1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::page_login1)
{
    ui->setupUi(this);
}

page_login1::~page_login1()
{
    delete ui;
}

void page_login1::on_pushButton_clicked()
{
    //数据库查找用户名和密码

    //失败就提示


    //成功进入主界面
    emit sendloginsuccess();
}

void page_login1::on_pushButton_2_clicked()
{
    exit(0);
}
