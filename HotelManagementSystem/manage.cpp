#include "manage.h"
#include "ui_manage.h"
#include "checkaccount.h"
#include "login.h"
#include "addroom.h"
#include "roomstate.h"

Manage::Manage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Manage)
{
    ui->setupUi(this);
    setWindowTitle("管理员界面");
    CheckAccount  *checkaccount = new CheckAccount;
    AddRoom *addroom1 = new AddRoom;
    RoomState *roomstate = new RoomState;

    ui->tabWidget->insertTab(0,addroom1,"新增房间");
    ui->tabWidget->insertTab(1,checkaccount,"账号信息");
    ui->tabWidget->insertTab(2,roomstate,"房间信息");

    QAction *openAction  = new QAction("注销",this);


    file = ui->menuBar->addMenu("选项");
    file->addAction(openAction);
    file->addAction("退出");

    connect(openAction,SIGNAL(triggered()),this,SLOT(LogOut()));
}

Manage::~Manage()
{
    delete ui;
}


void Manage::LogOut(){
    file->menuAction()->setVisible(false);
    this->close();
    login *login1 = new login;
    login1->show();
}
