#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"page_login1.h"
#include"stusql.h"
#include"dld_add.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_btn_moni_clicked();

    void on_pushButton_add_clicked();

    void on_btn_clear_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

    void on_btn_search_clicked();

private:
    Ui::MainWindow *ui;
    page_login1 mylogin;
    stusql *m_ptrstusql;
    QStringList m_lname;
    dld_add m_dlgaddstu;
    void updatetable();
};
#endif // MAINWINDOW_H
