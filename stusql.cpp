#include "stusql.h"
#include<QSqlDatabase>
#include<QMessageBox>
#include<QSqlQuery>
#include<QValidator>
#include<QDebug>
#include<QCoreApplication>

stusql *stusql::ptrstusql=nullptr;
stusql::stusql(QObject *parent) : QObject(parent)
{

   stuinfo s;

  /* s.name="小爪";
   for(int i=0;i<10;i++)
  { addstu(s);
      }
   userinfo info;
   info.username="xiao";
   info.password="22344";
   info.aut="admin";
   addusre(info);
   addusre(info);*/

}

void stusql::init()
{   if(QSqlDatabase::drivers().isEmpty())
        qDebug()<<"No database drivers found";
    m_db=QSqlDatabase::addDatabase("QSQLITE");
#if 1
    auto str=QCoreApplication::applicationDirPath()+"/data.db";
    qDebug()<<str;
#endif
  // str="E:\\data2.db";
    m_db.setDatabaseName(str);
    if(!m_db.open())
        QMessageBox::warning(nullptr,tr("unable to open database"),tr("an error occurred while"));
}

quint32 stusql::getstucnt()
{
     QSqlQuery q("",m_db);
     q.exec("select count(id) from student;");
     quint32 uicnt=0;
     while(q.next())
     {

         uicnt= q.value(0).toUInt();
     }
     return uicnt;
}

QList<stuinfo> stusql::getpagestu(quint32 page, quint32 uicnt)
{   QList<stuinfo> l;
    QSqlQuery q("",m_db);
    QString strq=QString("select * from student order by id limit %1 offset %2").
            arg(uicnt).arg(page*uicnt);
    q.exec(strq);
    stuinfo info;
    while(q.next())
    {
        info.id=q.value(0).toUInt();
        info.name=q.value(1).toString();
        info.age=q.value(2).toUInt();
        info.grade=q.value(3).toUInt();
        info.uiclass=q.value(4).toUInt();
        info.studentid=q.value(5).toUInt();
        info.phone=q.value(6).toString();
         info.wechat=q.value(7).toString();
        l.push_back(info);

    }
    return l;
}

bool stusql::addstu(stuinfo info)
{
    QSqlQuery q("",m_db);
   QString strq=QString ("insert into student values(null,'%1',%2,%3,%4,%5,'%6','%7')").
            arg(info.name).
            arg(info.age).
            arg(info.grade).
            arg(info.uiclass).
            arg(info.studentid).
            arg(info.phone).
            arg(info.wechat);

    q.exec(strq);
    //QString strq=QString ("INSERT INTO student VALUES (NULL, '张三', 12, 3, 2, 1, 15940224444, 'asdzhang')");
    // q.exec(strq);
}

bool stusql::addstu(QList<stuinfo> l)
{
    QSqlQuery q("",m_db);
    m_db.transaction();
    for(auto info:l)
  { QString strq=QString ("insert into student values(null,'%1',%2,%3,%4,%5,'%6','%7')").
            arg(info.name).
            arg(info.age).
            arg(info.grade).
            arg(info.uiclass).
            arg(info.studentid).
            arg(info.phone).
            arg(info.wechat);

    q.exec(strq);
    }
    m_db.commit();
    return true;
}

bool stusql::delstu(int id)
{
     QSqlQuery q("",m_db);
     return q.exec(QString("delete from student where id = %1").arg(id));
}

bool stusql::clearstutable()
{
    QSqlQuery q("",m_db);
    q.exec("delete from student");
    return q.exec("delete from sqlite_sequence where name='student'");
}

void stusql::updatestuinfo(stuinfo info)
{
    QSqlQuery q(m_db);
    QString strq=QString ("update student set name='%1',age=%2,grade=%3,uiclass=54,studentid =%5"
                          "phone='%6',wechat='%7' where id=%8").
            arg(info.name).
            arg(info.age).
            arg(info.grade).
            arg(info.uiclass).
            arg(info.studentid).
            arg(info.phone).
            arg(info.wechat).arg(info.id);

    q.exec(strq);
}

QList<userinfo> stusql::getAlluser()
{   QList<userinfo> l;
    QSqlQuery q("",m_db);
    q.exec("select * from username");
    userinfo info;
    while(q.next())
    {

        info.username=q.value(0).toString();
        info.password=q.value(1).toString();
        info.aut=q.value(2).toString();
        l.push_back(info);

    }
    return l;

}

bool stusql::isexit(QString struser)
{
    QSqlQuery q(m_db);
    q.exec(QString("select *from username where username='%1'").arg(struser));
    return q.next();
}

void stusql::updatuser(userinfo info)
{
    QSqlQuery q(m_db);
    QString strq=QString ("update username set password='%1',auth='%2' where username='%3'").

            arg(info.password).
            arg(info.aut).arg(info.username);

    q.exec(strq);

}

void stusql::addusre(userinfo info)
{
    QSqlQuery q(m_db);
    QString strq=QString ("insert into username values ('%1','%2','%3');").
            arg(info.username).
            arg(info.password).
            arg(info.aut);

    q.exec(strq);
}

void stusql::deluser(QString strusername)
{
     QSqlQuery q(m_db);
     q.exec(QString("delete from username where username='%1'").arg(strusername));
}
