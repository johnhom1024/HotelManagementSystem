#include "takeinwidget.h"
#include "ui_takeinwidget.h"
#include "staff.h"
#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QtSql>
#include <iostream>
#include <QActionGroup>
#include <QMessageBox>


takeinWidget::takeinWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::takeinWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确认入住");
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
    SetRoomTypeBtn();

}

takeinWidget::~takeinWidget()
{
    delete ui;
}

void takeinWidget::on_buttonBox_accepted()
{

    QString Name =  ui->name->text();
    QString Phone = ui->phoneNum->text();
    QString IDNum = ui->IDNum->text();
    QString RoomType = ui->roomSize->text();
    int RoomNum = ui->roomNum->text().toInt();

    if(Name == NULL || Phone == NULL || IDNum == NULL || RoomType == NULL || RoomNum == 0)        //判断录入的数据是否为空，为空则弹窗提醒并结束执行
    {
        QMessageBox::information(this,"失败","输入信息不能为空");
        return;
    }


    QSqlQuery query;
    QString sqlInsert;
    QString sqlUpdate;
    sqlInsert = QString("insert into takeIn(Cname,Cphone,CidNum,roomType,roomNum)"
                     "values('%1','%2','%3','%4',%5)").arg(Name).arg(Phone).arg(IDNum).arg(RoomType).arg(RoomNum);

    sqlUpdate = QString("update room set roomState = '%1' where roomNum = %2").arg("已入住").arg(RoomNum);

    if(query.exec(sqlInsert) && query.exec(sqlUpdate))
        {//判断插入信息和更新房间状态是否成功
        QMessageBox::information(this,"成功","登记成功");
        emit SendData("更新页面");
        }
     else
        QMessageBox::information(this,"失败","登记失败");
}

void takeinWidget::CheckRoomState(QString roomtype,int *array)
{
    QSqlQuery query;
    int i = 0;
    QString state = "空";
    query.exec("select * from room");
    while (query.next()) {
       if( roomtype == query.value(1).toString() && state == query.value(3).toString())
       {
           array[i] = query.value(0).toInt();
           i++;
       }
    }

}

void takeinWidget::SetRoomTypeBtn(){
    int Length = 20;
    int i = 0;

    QSqlQuery queryRoomType;
    QMenu *RoomTypeBtn = new QMenu;
    QString QueryToString;          //存储查询后的数据的值
    QAction *roomTypeAct[Length];
    QActionGroup *typeGroup = new QActionGroup(this);

    queryRoomType.exec("select distinct roomType from room");
    while (queryRoomType.next()) {
        QueryToString = queryRoomType.value(0).toString(); //将查询到的这一行的第一列转换成QString
        roomTypeAct[i] = new QAction(QueryToString,this);  //将Qtring存到QAction对象数组中
        RoomTypeBtn->addAction(roomTypeAct[i]);
        typeGroup->addAction(roomTypeAct[i]);
        i++;
    }
    ui->roomSize->setMenu(RoomTypeBtn);
    connect(typeGroup,SIGNAL(triggered(QAction*)),this,SLOT(UpdateRoomTypeBtn(QAction*)));            //点击执行设置房间类型按钮函数

}

//更新房间类型按钮
void takeinWidget::UpdateRoomTypeBtn(QAction* act)
{
    ui->roomSize->setText(act->text());
    ui->roomNum->setText("待选");         //重置房间号的按钮选项
    SetRoomNumBtn();
}




//设置房间号按钮
void takeinWidget::SetRoomNumBtn()
{
    int length;         //房间数
    QString type = ui->roomSize->text();    //获取按钮上的字符串
    int array[100] = {0};
    CheckRoomState(type,array);
    length = sizeof(array)/sizeof(array[0]);

    QString RoomNumArray;
    QAction *roomNumact[100];      //储存array数组中的房间号
    QMenu *RoomNumBtn = new QMenu;
    QActionGroup *group = new QActionGroup(this);

    for(int i = 0; array[i] != 0; i++)
    {
        RoomNumArray = QString::number(array[i],10);    //将array转成QString
        roomNumact[i] = new QAction(RoomNumArray,this);
        RoomNumBtn->addAction(roomNumact[i]);
        group->addAction(roomNumact[i]);
    }


    ui->roomNum->setMenu(RoomNumBtn);
    connect(group,SIGNAL(triggered(QAction*)),this,SLOT(UpdateRoomNumBtn(QAction*)));

}

//更新房间号按钮
void takeinWidget::UpdateRoomNumBtn(QAction* act)
{
    ui->roomNum->setText(act->text());
}


