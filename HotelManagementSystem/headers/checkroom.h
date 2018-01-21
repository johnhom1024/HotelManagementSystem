#ifndef CHECKROOM_H
#define CHECKROOM_H

#include <QWidget>

namespace Ui {
class CheckRoom;
}

class CheckRoom : public QWidget
{
    Q_OBJECT

public:
    explicit CheckRoom(QWidget *parent = 0);
    ~CheckRoom();

private:
    Ui::CheckRoom *ui;
};

#endif // CHECKROOM_H
