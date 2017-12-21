#include "staff.h"
#include "ui_staff.h"

#include "checkroom.h"
#include "login.h"
#include "arrival.h"
#include "book.h"
#include "takeinwidget.h"
#include "takeoutwidget.h"

#include <QFile>
#include <iostream>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QSystemTrayIcon>
#include <iostream>
using namespace std;

Staff::Staff(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Staff)
{
    ui->setupUi(this);
    QAction *openAction  = new QAction("注销",this);


    file = ui->menuBar->addMenu("选项");
    file->addAction(openAction);
    file->addAction("退出");
    connect(openAction,SIGNAL(triggered()),this,SLOT(LogOut()));

    FreshTakeIn();
}

Staff::~Staff()
{
    delete ui;
}


void Staff::ReceiveTakeIn(QString str)
{
    if(str == "更新页面")
    {
        cout<<"入住页面刷新"<<endl;
        FreshTakeIn();

    }
    else
        cout<<"匹配失败"<<endl;
}

void Staff::ReceiveTakeOut(QString str)
{
    if(str == "更新页面")
    {
        cout<<"退房页面刷新"<<endl;
        FreshTakeOut();
    }
    else
        cout<<"匹配失败"<<endl;
}

void Staff::ReceiveBook(QString str)
{
    if(str == "更新页面")
    {
        cout<<"预定页面刷新"<<endl;
        FreshBook();
    }
    else
        cout<<"匹配失败"<<endl;
}

void Staff::ReceiveArrival(QString str)
{
    if(str == "更新页面")
    {
        cout<<"预定入住页面刷新"<<endl;
        FreshArrival();
    }
    else
        cout<<"匹配失败"<<endl;
}

void Staff::FreshTakeIn()              //刷新入住标签
{
    Fresh(0);
}

void Staff::FreshTakeOut()             //刷新退房标签
{
    Fresh(1);
}

void Staff::FreshBook()
{
    Fresh(3);
}

void Staff::FreshArrival()
{

    Fresh(4);
    cout<<"更新了页面"<<endl;
}

void Staff::Fresh(int i)
{
    takeinWidget *takein = new takeinWidget;
    takeoutWidget *takeout = new takeoutWidget;
    CheckRoom *checkroom = new CheckRoom;
    Book *book = new Book;
    Arrival *arrival = new Arrival;

    ui->tabWidget->removeTab(4);
    ui->tabWidget->removeTab(3);
    ui->tabWidget->removeTab(2);
    ui->tabWidget->removeTab(1);
    ui->tabWidget->removeTab(0);

    ui->tabWidget->insertTab(0,takein,"信息录入");
    ui->tabWidget->insertTab(1,takeout,"退房");
    ui->tabWidget->insertTab(2,checkroom,"入住信息");
    ui->tabWidget->insertTab(3,book,"预定");
    ui->tabWidget->insertTab(4,arrival,"预定入住");

    ui->tabWidget->setCurrentIndex(i);
    connect(takein,SIGNAL(SendData(QString)),this,SLOT(ReceiveTakeIn(QString)));
    connect(takeout,SIGNAL(SendData(QString)),this,SLOT(ReceiveTakeOut(QString)));
    connect(book,SIGNAL(SendData(QString)),this,SLOT(ReceiveBook(QString)));
    connect(arrival,SIGNAL(SendData(QString)),this,SLOT(ReceiveArrival(QString)));
}

void Staff::LogOut(){
    file->menuAction()->setVisible(false);
    this->close();
    login *login1 = new login;
    login1->show();
}
