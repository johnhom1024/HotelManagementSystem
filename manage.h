#ifndef MANAGE_H
#define MANAGE_H

#include <QMainWindow>
#include <QMenu>
namespace Ui {
class Manage;
}

class Manage : public QMainWindow
{
    Q_OBJECT

public:
    explicit Manage(QWidget *parent = 0);
    ~Manage();

private slots:
    void LogOut();

private:
    Ui::Manage *ui;
    QMenu *file;
};

#endif // MANAGE_H
