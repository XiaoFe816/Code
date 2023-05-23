#ifndef OPERATOR_H
#define OPERATOR_H

#include <QMainWindow>

#include "showmydata.h"
#include "useroperate.h"

namespace Ui {
class Operator;
}

class Operator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Operator(QWidget *parent = 0);
    ~Operator();

private slots:
    void on_pushButton_menu_clicked();
    void on_pushButton_operate_clicked();
    void on_pushButton_user_clicked();

private:
    Ui::Operator *ui;
    ShowMyData *myData;
    UserOperate *optUser;
};

#endif // OPERATOR_H
