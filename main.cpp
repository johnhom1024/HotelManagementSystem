#include "testinsert.h"
#include "login.h"
#include "checkroom.h"
#include <QApplication>
#include <iostream>
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlDatabase>
using namespace std;

int connectDB(){
    QSqlDatabase d = QSqlDatabase::addDatabase("QMYSQL");
       d.setHostName("127.0.0.1");
       d.setDatabaseName("test");
       d.setPort(3306);
       d.setUserName("root");
       d.setPassword("123456");
       if(d.open())
       {
           cout<<"连接mysql成功！"<<endl;
           return 1;
       }
       else
       {
           QMessageBox::information(NULL,"失败","连接数据库失败");
           return 0;
        }
}

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    connectDB();
    login l;
    l.show();
//      CheckRoom checkroom1;
//      checkroom1.show();

    return a.exec();
}
