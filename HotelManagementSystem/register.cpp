#include "register.h"
#include "ui_register.h"
#include <QDebug>
#include <QButtonGroup>
#include <QMessageBox>
#include <QSqlQuery>
#include <iostream>
#include <QPushButton>
#define SECRET 8888             //密钥
using namespace std;

Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
    setWindowTitle("注册界面");
    setAttribute(Qt::WA_DeleteOnClose);

    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("注册");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");

    ui->password->setPlaceholderText("不少于8位");
    ui->password1->setPlaceholderText("不少于8位");

    ui->password->setEchoMode(QLineEdit::Password);
    ui->password1->setEchoMode(QLineEdit::Password);
    ui->secretKey->setEchoMode(QLineEdit::Password);
    ui->secretKey->hide();
    ui->secretKeyLabel->hide();

    this->ui->staffBtn->setChecked(true);       //默认员工按钮被选中
}

Register::~Register()
{
    delete ui;
}

void Register::on_manageBtn_clicked()
{
    ui->secretKey->show();
    ui->secretKeyLabel->show();
}

void Register::on_staffBtn_clicked()
{
    ui->secretKey->hide();
    ui->secretKeyLabel->hide();
}

void Register::on_buttonBox_accepted()
{
    int secretkey = ui->secretKey->text().toInt();

    QButtonGroup *Btn = new QButtonGroup;
    Btn->addButton(ui->staffBtn,0);
    Btn->addButton(ui->manageBtn,1);

    int a =  Btn->checkedId();

    if(!Judge())    //如果发现输入的不符合要求
    {
        return;
    }

    switch (a) {
    case 0:
            UpdateStaffAccount();
        break;
    case 1:
        if(secretkey == SECRET )
            UpdateManageAccount();
        else
            QMessageBox::information(this,"提示","密钥错误！");
        break;
    }


}

bool Register::Judge()
{
    QString accountName = ui->name->text();
    QString account = ui->account->text();
    QString password = ui->password->text();
    QString password1 = ui->password1->text();

    QSqlQuery checkquery;
    QString checkStr;

    checkStr = QString("select account from accountInf");
    checkquery.exec(checkStr);

    if(accountName == NULL || account == NULL || password == NULL || password1 == NULL)     //判断输入是否为空
    {
        QMessageBox::information(this,"提示","信息未填写完整！");
        return false;
    }

    while(checkquery.next())              //判断数据库中是否有存在的账号
    {
        if(account == checkquery.value(0).toString())
        {
            QMessageBox::information(this,"提示","账号已存在");
            return false;
        }
    }

    if(password1 != password1)          //判断密码是否匹配
    {
        QMessageBox::information(this,"提示","两次输入的密码不相同");
        return false;
    }

    if(password.length() < 8)           //判断密码长度是否达到8位
    {
        QMessageBox::information(this,"","密码长度不够8位");
        return false;
    }

    return true;
}



void Register::UpdateStaffAccount()
{
    QString accountName = ui->name->text();
    QString account = ui->account->text();
    QString password = ui->password->text();

    QSqlQuery updateStaff;
    QString updateStr;

    updateStr = QString("insert into accountInf(account,password,name,accountType)"
                        "values('%1','%2','%3','%4')").arg(account).arg(password).arg(accountName).arg("员工");

    if(updateStaff.exec(updateStr))     //插入账号信息到数据库中
    {
        QMessageBox::information(this,"提示","注册成功！");
        accept();           //关闭窗口
    }
    else
        QMessageBox::information(this,"提示","注册失败！");

}

void Register::UpdateManageAccount()
{
    QString accountName = ui->name->text();
    QString account = ui->account->text();
    QString password = ui->password->text();

    QSqlQuery updateManage;
    QString updateStr;

    updateStr = QString("insert into accountInf(account,password,name,accountType)"
                        "value('%1','%2','%3','%4')").arg(account).arg(password).arg(accountName).arg("管理员");
    if(updateManage.exec(updateStr))
    {
        QMessageBox::information(this,"提示","注册成功！");
        accept();           //关闭注册窗口
    }
    else
        QMessageBox::information(this,"提示","注册失败！");
}

void Register::on_buttonBox_rejected()          //取消按钮关闭注册窗口
{
    accept();
}
