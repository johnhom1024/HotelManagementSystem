#include "takeoutwidget.h"
#include "ui_takeoutwidget.h"
#include <QSqlQuery>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QMessageBox>


takeoutWidget::takeoutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::takeoutWidget)
{
    ui->setupUi(this);
   ui->buttonBox->button(QDialogButtonBox::Ok)->setText("确认退房");
   ui->buttonBox->button(QDialogButtonBox::Cancel)->setText("取消");
    CheckRoomState();
}

takeoutWidget::~takeoutWidget()
{
    delete ui;
}


void takeoutWidget::CheckRoomState()
{
    //TODO：需要改动
    QSqlQuery query;
    QString state = "已入住";
    QString roomNumArray;
    QActionGroup *roomNumGroup = new QActionGroup(this);
    QAction *roomNumAct[100];
    QMenu *roomNumMenu = new QMenu;
    query.exec("select * from room");
    while (query.next())
    {
        int i = 0;
       if(state == query.value(3).toString())
       {
           roomNumArray = query.value(0).toString();
           roomNumAct[i] = new QAction(roomNumArray,this);
           roomNumGroup->addAction(roomNumAct[i]);
           roomNumMenu->addAction(roomNumAct[i]);
           i++;
       }
    }

    ui->roomNumBtn->setMenu(roomNumMenu);
    connect(roomNumGroup,SIGNAL(triggered(QAction*)),this,SLOT(UpdateRoomNumBtn(QAction*)));

}


void takeoutWidget::UpdateRoomNumBtn(QAction* act){
    ui->roomNumBtn->setText(act->text());
}




void takeoutWidget::on_buttonBox_accepted()
{
    QSqlQuery takeOutQuery;
    QString RoomNum;
    RoomNum = ui->roomNumBtn->text();
    QString sqlUpdate;
    sqlUpdate = QString("update room set roomState = '%1' where roomNum = %2").arg("空").arg(RoomNum);

    if(takeOutQuery.exec(sqlUpdate))
    {
        QMessageBox::information(this,"成功","退房成功！");
        emit SendData("更新页面");
    }
    else
        QMessageBox::information(this,"失败","退房失败！");


}
