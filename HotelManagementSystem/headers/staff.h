#ifndef STAFF_H
#define STAFF_H

#include <QMainWindow>
#include <QMenu>

namespace Ui {
class Staff;
}

class Staff : public QMainWindow
{
    Q_OBJECT

public:
    explicit Staff(QWidget *parent = 0);
    ~Staff();

private slots:
   // void on_takeInBtn_clicked();
   //void on_takeOutBtn_clicked();
    void LogOut();
    void ReceiveTakeIn(QString str);  //实现刷新标签页的功能
    void ReceiveTakeOut(QString str);
    void ReceiveBook(QString str);
    void ReceiveArrival(QString str);

private:
    Ui::Staff *ui;

    void FreshTakeIn();
    void FreshTakeOut();
    void FreshBook();
    void FreshArrival();
    //void closeEvent(QCloseEvent *event);        //隐藏窗口
    void Fresh(int i);
    QMenu *file;
};






#endif // STAFF_H
