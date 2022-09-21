#ifndef STUSQL_H
#define STUSQL_H

#include <QObject>
#include<QSqlDatabase>
struct stuinfo
{
    int id;
    QString name;
    quint8 age;
    quint16 grade;
    quint16 uiclass;
    quint32 studentid;
    QString phone;
    QString wechat;
};
struct userinfo
{
    QString username;
    QString password;
    QString aut;
};

class stusql : public QObject
{
    Q_OBJECT

public:
    static stusql *ptrstusql;
    static stusql *getinstance()
    {
        if(nullptr==ptrstusql)
        {
            ptrstusql=new stusql;

        }
        return ptrstusql;
    }
    explicit stusql(QObject *parent = nullptr);
    void init();
    //查询所有学生数量
    quint32 getstucnt();
    //查询第几页学生数据
    QList<stuinfo> getpagestu(quint32 page,quint32 uicnt);
    //增加学生
    bool addstu(stuinfo);
     bool addstu(QList<stuinfo> l);

    //删除学生
    bool delstu(int id);
    //清空学生表
    bool clearstutable();
    //修改学生信息
    void updatestuinfo(stuinfo info);
    //查询所有用户
    QList<userinfo> getAlluser();
    //查询用户名是否存在
    bool isexit(QString struser);
    //更新用户信息
    void updatuser(userinfo info);
    //添加单个用户
    void addusre(userinfo info);
    //删除单个用户
    void deluser(QString strusername);
signals:
private:
    QSqlDatabase m_db;

};

#endif // STUSQL_H
