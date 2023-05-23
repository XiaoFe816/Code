#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include "operator.h"
#include "showmydata.h"

#define ADMINUSER "admin"
#define ADMINPASS "admin"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clearUser_clicked();
    void on_pushButton_clearPass_clicked();
    void on_pushButton_login_clicked();
    void on_pushButton_exit_clicked();
    void on_checkBox_password_clicked(bool checked);
    void mySqlInit(QSqlDatabase &db, QString sqlName);

private:
    Ui::Login *ui;
    Operator *opt1;
    ShowMyData *myData;

};

#endif // LOGIN_H
