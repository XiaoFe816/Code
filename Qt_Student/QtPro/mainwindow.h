#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include "login.h"

namespace Ui {
class MainWindow;
}

class Student
{
public:
    Student() {}
    int uid;
    QString name;
    QString sex;
    int age;
    double chinese;
    double math;
    double english;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_login_clicked();
    void on_pushButton_close_clicked();

private:
    Ui::MainWindow *ui;
    Login *userLogin;
};

#endif // MAINWINDOW_H
