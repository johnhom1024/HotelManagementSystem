#include "login.h"
#include <QApplication>
#include <iostream>
#include <QtSql>
#include <QSqlDatabase>
#include <QMessageBox>
using namespace std;

void connectDB(){                        //连接本地数据库mysql
    QSqlDatabase d = QSqlDatabase::addDatabase("QMYSQL");
       d.setHostName("127.0.0.1");
       d.setDatabaseName("test");
       d.setPort(3306);
       d.setUserName("root");
       d.setPassword("123456");
       if(d.open())
       {
           cout<<"连接mysql成功！"<<endl;
       }
       else
       {
           QMessageBox::information(NULL,"失败","连接数据库失败");
        }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connectDB();

    login l;
    l.show();

    return a.exec();
}
