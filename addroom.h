#ifndef ADDROOM_H
#define ADDROOM_H

#include <QWidget>

namespace Ui {
class AddRoom;
}

class AddRoom : public QWidget
{
    Q_OBJECT

public:
    explicit AddRoom(QWidget *parent = 0);
    ~AddRoom();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddRoom *ui;
};

#endif // ADDROOM_H
