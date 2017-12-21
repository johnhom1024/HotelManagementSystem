#include "checkroom.h"
#include "ui_checkroom.h"
#include <QStandardItemModel>
#include <QSqlQuery>
#include <iostream>
#include <QSqlQueryModel>

using namespace std;

CheckRoom::CheckRoom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckRoom)
{
    ui->setupUi(this);

    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select Cname,Cphone,roomType,roomNum,takeTime from takeIn order by Cno desc");



    model->setHeaderData(0,Qt::Horizontal,"顾客姓名");
    model->setHeaderData(1,Qt::Horizontal,"电话");
    model->setHeaderData(2,Qt::Horizontal,"房间类型");
    model->setHeaderData(3,Qt::Horizontal,"房间号");
    model->setHeaderData(4,Qt::Horizontal,"入住时间");




    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);               //隔行自动变色
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列设置成自动延伸
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);      //不许编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);    //只允许选中一行



}

CheckRoom::~CheckRoom()
{
    delete ui;
}
