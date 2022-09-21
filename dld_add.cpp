#include "dld_add.h"
#include "ui_dld_add.h"
#include"stusql.h"
#include<QMessageBox>

dld_add::dld_add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dld_add)
{
    ui->setupUi(this);
}

dld_add::~dld_add()
{
    delete ui;
}

void dld_add::settype(bool isadd,stuinfo info)
{
    m_isadd=isadd;
    m_info=info;
    ui->le_name->setText(info.name);
    ui->spinBox->setValue(info.age);
    ui->le_class->setText(QString::number(info.uiclass));
    ui->le_grae->setText(QString::number(info.grade));
    ui->le_phone->setText(info.phone);
    ui->le_wechat->setText(info.wechat);
}

void dld_add::on_pushButton_6_clicked()
{
    stuinfo info;
    auto ptr=stusql::getinstance();
    info.name=ui->le_name->text();
    info.age=ui->spinBox->text().toUInt();
    info.uiclass=ui->le_class->text().toUInt();
    info.grade=ui->le_grae->text().toUInt();
    info.phone=ui->le_phone->text();
    info.wechat=ui->le_wechat->text();
   if(m_isadd)
   {    ptr->addstu(info);

   }
   else

   {

       ptr->updatestuinfo(info);


   }
    QMessageBox::information(nullptr,"信息","存储成功");
    this->hide();

}

void dld_add::on_pushButton_5_clicked()
{
    this->hide();
}
