#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = 0);
    ~Register();

private slots:
    void on_manageBtn_clicked();
    void on_staffBtn_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::Register *ui;
    void UpdateStaffAccount();
    void UpdateManageAccount();
    bool Judge();
};

#endif // REGISTER_H
