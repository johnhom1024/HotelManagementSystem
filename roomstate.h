#ifndef ROOMSTATE_H
#define ROOMSTATE_H

#include <QWidget>

namespace Ui {
class RoomState;
}

class RoomState : public QWidget
{
    Q_OBJECT

public:
    explicit RoomState(QWidget *parent = 0);
    ~RoomState();

private:
    Ui::RoomState *ui;
};

#endif // ROOMSTATE_H
