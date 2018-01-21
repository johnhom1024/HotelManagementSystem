#ifndef TAKEINWIDGET_H
#define TAKEINWIDGET_H

#include <QWidget>

namespace Ui {
class takeinWidget;
}

class takeinWidget : public QWidget
{
    Q_OBJECT

public:
    explicit takeinWidget(QWidget *parent = 0);
    ~takeinWidget();
signals:
    void SendData(QString);

private slots:
    void CheckRoomState(QString roomtype,int *array);
    void SetRoomNumBtn();
    void SetRoomTypeBtn();
    void UpdateRoomTypeBtn(QAction* act);
    void UpdateRoomNumBtn(QAction* act);       //房间号按钮更新函数
    void on_buttonBox_accepted();

private:
    Ui::takeinWidget *ui;
};

#endif // TAKEINWIDGET_H
