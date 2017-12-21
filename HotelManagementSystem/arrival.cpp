#include "arrival.h"
#include "ui_arrival.h"
#include <QtSql>
#include <QTableView>
#include <QSqlQueryModel>
#include <QMessageBox>

Arrival::Arrival(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Arrival)
{
    ui->setupUi(this);
}

Arrival::~Arrival()
{
    delete ui;
}
//查询预订信息
void Arrival::on_queryBookBtn_clicked()
{
    QString phone = ui->phoneText->text();
    QSqlQueryModel *model = new QSqlQueryModel(ui->tableView);
    model->setQuery("SELECT * FROM book where Cphone = " + phone);

    model->setHeaderData(0,Qt::Horizontal,"序号");
    model->setHeaderData(1,Qt::Horizontal,"姓名");
    model->setHeaderData(2,Qt::Horizontal,"电话");
    model->setHeaderData(3,Qt::Horizontal,"身份证");
    model->setHeaderData(4,Qt::Horizontal,"房间号");
    model->setHeaderData(5,Qt::Horizontal,"房间类型");
    model->setHeaderData(6,Qt::Horizontal,"预订时间");
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列设置成自动延伸
    qDebug()<<"执行了"<<endl;
}

//将预订状态更改为入住状态
void Arrival::on_confirmBtn_clicked()
{
    int roomId;
    QString phone = ui->phoneText->text();
    QString roomUpdate;
    QSqlQuery queryRoomId;
    QSqlQuery deleteBook;
    QSqlQuery InsertSql;
    QString InsertStr;
    queryRoomId.exec("SELECT * FROM book where Cphone = " + phone);



    if(queryRoomId.next())
    {
        QString Name = queryRoomId.value(1).toString();
        QString Phone = queryRoomId.value(2).toString();
        QString IDNum = queryRoomId.value(3).toString();
        int RoomNum = queryRoomId.value(4).toInt();
        QString RoomType = queryRoomId.value(5).toString();

        InsertStr = QString("insert into takeIn(Cname,Cphone,CidNum,roomType,roomNum)"
                         "values('%1','%2','%3','%4',%5)").arg(Name).arg(Phone).arg(IDNum).arg(RoomType).arg(RoomNum);






        qDebug()<<roomId<<endl;
        roomUpdate = QString("update room set roomState='%1' where roomNum=%2").arg("已入住").arg(RoomNum);
        bool isUpdate = queryRoomId.exec(roomUpdate);
        if(isUpdate)
        {
            QMessageBox::information(this,"提示","入住成功");
            deleteBook.exec("DELETE FROM book WHERE Cphone = " + phone);
            InsertSql.exec(InsertStr);
            emit SendData("更新页面");

        }
        else
            QMessageBox::information(this,"提示","入住失败");

    }
    else
        QMessageBox::information(this,"提示","没有该预订信息");

}
