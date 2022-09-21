#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QStringList>
#include<QRandomGenerator>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_ptrstusql(nullptr)
{
    ui->setupUi(this);
    mylogin.show();
    auto f=[&]()
    {
       this->show();
    };
    connect(&mylogin,&page_login1::sendloginsuccess,this,f);
    ui->treeWidget->clear();
    ui->treeWidget->setColumnCount(1);
    QStringList l;
    l<<"学生管理系统";
    QTreeWidgetItem *pf=new QTreeWidgetItem(ui->treeWidget,l);
    ui->treeWidget->addTopLevelItem(pf);
    l.clear();
    l<<"学生管理";
    QTreeWidgetItem *p1=new QTreeWidgetItem(pf,l);
    l.clear();
   // l<<"管理员管理";
   // QTreeWidgetItem *p2=new QTreeWidgetItem(pf,l);
    pf->addChild(p1);
   // pf->addChild(p2);
    ui->treeWidget->expandAll();
    m_ptrstusql=stusql::getinstance();
    m_ptrstusql->init();
    m_lname<<"张三";
    m_lname<<"李三";
    m_lname<<"小巴";
    m_lname<<"刘五";
    m_lname<<"王二";
    m_lname<<"蒙椰";
    m_lname<<"李四";
    m_lname<<"小红";
    m_lname<<"小敏";
    m_lname<<"明明";
    m_lname<<"红红";
    m_lname<<"玛卡巴卡";
    m_lname<<"李华";
    m_lname<<"李明";
    m_lname<<"王铁柱";
    m_lname<<"田二妞";
    m_lname<<"小哈";
    m_lname<<"王王";
    updatetable();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    exit(0);
}

void MainWindow::on_btn_moni_clicked()
{

    QRandomGenerator g,c;
    g.seed(0);
    c.seed(0);
    QList<stuinfo> l;
    for(int i=0;i<m_lname.size();i++)
    {
        auto grade=g.bounded(7,10);
        auto uiclass=g.bounded(1,8);
        stuinfo info;
        info.name=m_lname[i];
        if(i%3)
        {
            info.age=16;
        }
        if(i%7)
        {
            info.age=17;
        }
        if(i%2)
        {
            info.age=18;

        }
        info.grade=grade;
        info.uiclass=uiclass;
        info.studentid=i;
        info.phone="13812345678";
        info.wechat="13812432";
        l.append(info);

    }
    m_ptrstusql->addstu(l);
    updatetable();
}

void MainWindow::on_pushButton_add_clicked()
{   m_dlgaddstu.settype(true);
    m_dlgaddstu.exec();
    updatetable();
}

void MainWindow::on_btn_clear_clicked()
{
    m_ptrstusql->clearstutable();
    updatetable();
}

void MainWindow::updatetable()
{   ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(9);
    QStringList l;
    l<<"序号"<<"id"<<"姓名"<<"年龄"<<"班级"<<"学号"<<"电话"<<"微信";
    //只选中行
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setHorizontalHeaderLabels(l);
    auto cnt=m_ptrstusql->getstucnt();

    QList<stuinfo> lstudents=m_ptrstusql->getpagestu(0,cnt);
    ui->tableWidget->setRowCount(cnt);
    for(int i=0;i<lstudents.size();i++)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(QString::number(i)));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString::number(lstudents[i].id)));
         ui->tableWidget->setItem(i,2,new QTableWidgetItem(lstudents[i].name));
         ui->tableWidget->setItem(i,3,new QTableWidgetItem(QString::number(lstudents[i].age)));
          ui->tableWidget->setItem(i,4,new QTableWidgetItem(QString::number(lstudents[i].grade)));
          ui->tableWidget->setItem(i,5,new QTableWidgetItem(QString::number(lstudents[i].uiclass)));
          ui->tableWidget->setItem(i,6,new QTableWidgetItem(QString::number(lstudents[i].studentid)));
           ui->tableWidget->setItem(i,7,new QTableWidgetItem(lstudents[i].phone));
            ui->tableWidget->setItem(i,8,new QTableWidgetItem(lstudents[i].wechat));
    }

}

void MainWindow::on_pushButton_5_clicked()
{
    int i=ui->tableWidget->currentRow();
    if(i>=0)
    {
        int id=ui->tableWidget->item(i,1)->text().toUInt();
        m_ptrstusql->delstu(id);
        updatetable();
          QMessageBox::information(nullptr,"信息","删除成功");


    }
}

void MainWindow::on_pushButton_4_clicked()
{   stuinfo info;
    int i=ui->tableWidget->currentRow();
    if(i>=0)
    {
           info.id=ui->tableWidget->item(i,1)->text().toUInt();
            info.name=ui->tableWidget->item(i,2)->text();
        info.age=ui->tableWidget->item(i,3)->text().toUInt();
        info.grade=ui->tableWidget->item(i,4)->text().toUInt();
        info.uiclass=ui->tableWidget->item(i,5)->text().toUInt();
        info.studentid=ui->tableWidget->item(i,6)->text().toUInt();
        info.phone=ui->tableWidget->item(i,7)->text();
        info.wechat=ui->tableWidget->item(i,8)->text();
       m_dlgaddstu.settype(false,info);
    m_dlgaddstu.exec();
    }
    updatetable();
}

void MainWindow::on_btn_search_clicked()
{
    QString strfilter=ui->le_search->text();
    if(strfilter.isEmpty())
    {
        QMessageBox::information(nullptr,"警告","名字筛选为空");
        updatetable();
        return;
    }

    ui->tableWidget->clear();
        ui->tableWidget->setColumnCount(9);
        QStringList l;
        l<<"序号"<<"id"<<"姓名"<<"年龄"<<"班级"<<"学号"<<"电话"<<"微信";

        ui->tableWidget->setHorizontalHeaderLabels(l);
        auto cnt=m_ptrstusql->getstucnt();

        QList<stuinfo> lstudents=m_ptrstusql->getpagestu(0,cnt);


        int index=0;
        for(int i=0;i<lstudents.size();i++)
        {
            if(!lstudents[i].name.contains(strfilter))
            {
                continue;
            }


            ui->tableWidget->setItem(index,0,new QTableWidgetItem(QString::number(index+1)));
            ui->tableWidget->setItem(index,1,new QTableWidgetItem(QString::number(lstudents[i].id)));
             ui->tableWidget->setItem(index,2,new QTableWidgetItem(lstudents[i].name));
             ui->tableWidget->setItem(index,3,new QTableWidgetItem(QString::number(lstudents[i].age)));
              ui->tableWidget->setItem(index,4,new QTableWidgetItem(QString::number(lstudents[i].grade)));
              ui->tableWidget->setItem(index,5,new QTableWidgetItem(QString::number(lstudents[i].uiclass)));
              ui->tableWidget->setItem(index,6,new QTableWidgetItem(QString::number(lstudents[i].studentid)));
               ui->tableWidget->setItem(index,7,new QTableWidgetItem(lstudents[i].phone));
                ui->tableWidget->setItem(index,8,new QTableWidgetItem(lstudents[i].wechat));
        index ++;
        }
     ui->tableWidget->setRowCount(index);
}
