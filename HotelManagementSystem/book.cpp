#include "book.h"
#include "ui_book.h"
#include <QMenu>
#include <QAction>
#include <QtSql>
#include <QString>
#include <QMessageBox>


Book::Book(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Book)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose); //用于关闭窗口时清空数据
    SetRoomTypeBtn();
}

Book::~Book()
{
    delete ui;
}

/* 查询选项中的房间类型并且为空的房间*/
void Book::QueryRoom(QString roomType,int *array)
{
    int i = 0;
    QSqlQuery query;//查询
    QString state = "空";
    query.exec("SELECT * FROM room"); // 查询的结果可能不止一条记录，所以我们称之为结果集

    while(query.next())
    {
        if(roomType == query.value(1).toString() && state == query.value(3).toString())
        {
            array[i] = query.value(0).toInt();
            i++;
        }
    }
}

//设置房间类型按钮
void Book::SetRoomTypeBtn()
{
    int Length = 20;
    int i = 0;

    QSqlQuery queryRoomType;
    QMenu *roomTypeMenu = new QMenu;
    QString roomTypeString;          //存储查询后的数据的值
    QAction *roomTypeAct[Length];
    QActionGroup *roomTypeGroup = new QActionGroup(this); //将房间类型的点击事件放入QActionGroup中

    queryRoomType.exec("select distinct roomType from room");
    while (queryRoomType.next()) {
        roomTypeString = queryRoomType.value(0).toString(); //将查询到的这一行的第一列转换成QString
        roomTypeAct[i] = new QAction(roomTypeString,this);  //将Qtring存到QAction对象数组中
        roomTypeMenu->addAction(roomTypeAct[i]);
        roomTypeGroup->addAction(roomTypeAct[i]);
        i++;
    }
    ui->roomTypeBtn->setMenu(roomTypeMenu);
    connect(roomTypeGroup,SIGNAL(triggered(QAction*)),this,SLOT(UpdateRoomTypeBtn(QAction*)));            //点击执行设置房间类型函数
}

//设置房间类型按钮的槽函数
void Book::UpdateRoomTypeBtn(QAction* act)
{
    ui->roomTypeBtn->setText(act->text());
    ui->roomNumBtn->setText("待选");         //重置房间号的按钮选项
    SetNumBtn();
}

//设置房间号按钮
void Book::SetNumBtn()
{
    int array[100] = {0};
    QString roomTypeText = ui->roomTypeBtn->text();
    QueryRoom(roomTypeText,array);
    //创建房间号菜单,并且将房间号菜单放进一个集合里
    QMenu *roomNumberMenu = new QMenu;
    QAction *roomNumberAct[50];
    QString numberArray;
    QActionGroup *roomNumberGroup = new QActionGroup(this);

    for(int i = 0; array[i] != 0; i++)
    {
        numberArray = QString::number(array[i],10);
        roomNumberAct[i] = new QAction(numberArray,this);
        roomNumberMenu->addAction(roomNumberAct[i]);
        roomNumberGroup->addAction(roomNumberAct[i]);
    }
    connect(roomNumberGroup,SIGNAL(triggered(QAction*)),this,SLOT(UpdateRoomNumBtn(QAction*)));
    ui->roomNumBtn->setMenu(roomNumberMenu);
}

//设置房间号按钮槽函数
void Book::UpdateRoomNumBtn(QAction *roomNumberGroup)
{
    //获取房间号
    ui->roomNumBtn->setText(roomNumberGroup->text());
    qDebug()<<"房间号已设置"<<endl;
}

//判断文本框内信息是否为空
bool Book::isEmpty(QString name,QString phone,QString id,QString type,QString roomId)
{
    if(name == "" || phone == "" || id == "" || type == "" || roomId == "待选")
    {
        return false;
    }
    else
    {
        return true;
    }
}

//确认后将数据保存到数据库
void Book::on_buttonBox_accepted()
{
    QSqlQuery query;
    QString sqlInsert;
    QString sqlUpdate;
    QString name = ui->nameText->text();
    QString phone = ui->phoneText->text();
    QString id = ui->idText->text();
    QString type = ui->roomTypeBtn->text();
    int number = ui->roomNumBtn->text().toInt();
    sqlInsert = QString("insert into book(Cname,Cphone,roomId,CidNum,roomType)"
                     "values('%1','%2',%3,'%4','%5')").arg(name).arg(phone).arg(number).arg(id).arg(type);
    sqlUpdate = QString("update room set roomState='%1' where roomNum=%2").arg("已预订").arg(number);

    if(isEmpty(name,phone,id,type,ui->roomNumBtn->text()))
    {

        bool isUpdate = query.exec(sqlUpdate);
        if(isUpdate)
        {
            QMessageBox::information(this,"提示","添加成功");
            //accept();//关闭预订窗口
            bool isInsert = query.exec(sqlInsert);
            if(isInsert)
            {
                qDebug()<<"已将房间状态设置为已预订"<<endl;
                emit SendData("更新页面");
                qDebug()<<"已刷新界面"<<endl;
            }
            else
            {
                qDebug()<<"房间状态设置失败"<<endl;
            }
        }
        else
        {
            QMessageBox::information(this,"提示","添加失败");
        }
    }
    else
    {
        QMessageBox::information(this,"提示","信息不能为空");
    }
}

