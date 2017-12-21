#ifndef ARRIVAL_H
#define ARRIVAL_H

#include <QWidget>

namespace Ui {
class Arrival;
}

class Arrival : public QWidget
{
    Q_OBJECT

public:
    explicit Arrival(QWidget *parent = 0);
    ~Arrival();

private:
    Ui::Arrival *ui;
private slots:
    void on_queryBookBtn_clicked();
    void on_confirmBtn_clicked();

signals:
    void SendData(QString);
};

#endif // ARRIVAL_H
