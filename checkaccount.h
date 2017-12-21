#ifndef CHECKACCOUNT_H
#define CHECKACCOUNT_H

#include <QWidget>

namespace Ui {
class CheckAccount;
}

class CheckAccount : public QWidget
{
    Q_OBJECT

public:
    explicit CheckAccount(QWidget *parent = 0);
    ~CheckAccount();

private:
    Ui::CheckAccount *ui;
};

#endif // CHECKACCOUNT_H
