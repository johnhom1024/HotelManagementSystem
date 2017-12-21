#include "checkaccount.h"
#include "ui_checkaccount.h"
#include <QSqlQueryModel>

CheckAccount::CheckAccount(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckAccount)
{
    ui->setupUi(this);
    QSqlQueryModel *model = new QSqlQueryModel;
    model->setQuery("select * from accountInf");



    model->setHeaderData(0,Qt::Horizontal,"账号");
    model->setHeaderData(1,Qt::Horizontal,"密码");
    model->setHeaderData(2,Qt::Horizontal,"姓名");
    model->setHeaderData(3,Qt::Horizontal,"账号类型");

    ui->tableView->setModel(model);
    ui->tableView->setAlternatingRowColors(true);               //隔行自动变色
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//列设置成自动延伸
    //ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);      //不许编辑
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);     //选中整行
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);    //只允许选中一行
}

CheckAccount::~CheckAccount()
{
    delete ui;
}
