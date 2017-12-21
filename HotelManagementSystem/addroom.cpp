#include "addroom.h"
#include "ui_addroom.h"
#include <QSqlQuery>
#include <QMessageBox>
AddRoom::AddRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddRoom)
{
    ui->setupUi(this);




}

AddRoom::~AddRoom()
{
    delete ui;
}

void AddRoom::on_pushButton_clicked()
{
    QString RoomType = ui->roomType->text();
    int RoomNum = ui->roomNum->text().toInt();
    int RoomPrice = ui->roomPrice->text().toInt();

    QSqlQuery addRoomQuery;
    QSqlQuery checkRoomQuery;
    QString addRoomStr;
    QString checkRoomStr;   //查看是否有重复的房间号



    checkRoomStr = QString("select roomNum from room where roomNum = %1").arg(RoomNum);

    checkRoomQuery.exec(checkRoomStr);
    if(checkRoomQuery.next())
    {
        if(checkRoomQuery.value(0).toInt() == RoomNum)
        {
            QMessageBox::information(this,"title","房间已存在！");
            return;
        }

    }

    addRoomStr = QString("insert into room(roomNum,roomType,roomPrice,roomState)"
                         "values(%1,'%2',%3,'%4')").arg(RoomNum).arg(RoomType).arg(RoomPrice).arg("空");
    bool OK  = addRoomQuery.exec(addRoomStr);
    if(OK)
        QMessageBox::information(this,"title","success");
    else
        QMessageBox::information(this,"title","fail");

    QSqlQuery newRoomQuery;     //在roomType表中添加新类型的房间
    QString newRoomStr;

    checkRoomStr = QString("select roomtype from roomType where roomType = '%1'").arg(RoomType);//查看是否为新的房间类型
    checkRoomQuery.exec(checkRoomStr);

    if(!checkRoomQuery.next())  //新增的房间类型如果在roomType表中不存在 则添加进表中
    {
        newRoomStr = QString("insert into roomType(roomtype)"
                              "values('%1')").arg(RoomType);
        newRoomQuery.exec(newRoomStr);
        QMessageBox::information(this,"title","new roomType!");
    }




}
