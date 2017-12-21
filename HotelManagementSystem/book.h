#ifndef BOOK_H
#define BOOK_H

#include <QWidget>

namespace Ui {
class Book;
}

class Book : public QWidget
{
    Q_OBJECT

public:
    explicit Book(QWidget *parent = 0);
    ~Book();
signals:
    void SendData(QString);

private:
    Ui::Book *ui;

private slots:
    void on_buttonBox_accepted();
    void QueryRoom(QString roomType,int *array);
    void SetRoomTypeBtn();
    void UpdateRoomTypeBtn(QAction* act);
    void SetNumBtn();
    void UpdateRoomNumBtn(QAction *roomNumberGroup);
    bool isEmpty(QString name,QString phone,QString id,QString type,QString roomId);

};

#endif // BOOK_H
