#include "login.h"
#include "ui_login.h"
#include "staff.h"
#include "manage.h"
#include "register.h"
#include <QSqlQuery>
#include <QMessageBox>
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    setWindowTitle("登陆");       //设置标题栏
    ui->password->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}


void login::on_loginBtn_clicked()
{
    QString account = ui->account->text();
    QString password = ui->password->text();

    if(account == NULL)
    {
        QMessageBox::information(this,"提示","请输入账号");
        return ;
    }

    if(password == NULL)
    {
        QMessageBox::information(this,"提示","请输入密码");
        return ;
    }
    QSqlQuery checkAccount;
    QString checkStr;

    checkStr = QString("select password,accountType from accountInf where account = '%1'").arg(account);
    checkAccount.exec(checkStr);


    if(!checkAccount.next())
    {
        QMessageBox::information(this,"提示","不存在此账户");
        return;
    }


    QString DBpassword = checkAccount.value(0).toString();
    QString DBaccountType = checkAccount.value(1).toString();

    if(DBpassword != password)
    {
        QMessageBox::information(this,"提示","密码错误");
        return;
    }
    else
        if(DBaccountType == "员工")
        {
           Staff *staff = new Staff;
           this->accept();
           staff->show();

        }
        else
        {
            Manage *manage = new Manage;
            this->accept();
            manage->show();
        }



}

void login::on_registerBtn_clicked()
{
    Register *re = new Register(this);
    re->exec();
}
