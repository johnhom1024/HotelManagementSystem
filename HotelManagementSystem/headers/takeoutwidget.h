#ifndef TAKEOUTWIDGET_H
#define TAKEOUTWIDGET_H

#include <QWidget>

namespace Ui {
class takeoutWidget;
}

class takeoutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit takeoutWidget(QWidget *parent = 0);
    ~takeoutWidget();
signals:
    void SendData(QString);

private slots:
    void UpdateRoomNumBtn(QAction* act);
    void on_buttonBox_accepted();

private:
    Ui::takeoutWidget *ui;
    void CheckRoomState();
};

#endif // TAKEOUTWIDGET_H
