#ifndef USEROPERATE_H
#define USEROPERATE_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDialog>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>
#include <QDebug>

namespace Ui {
class UserOperate;
}

class UserOperate : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserOperate(QWidget *parent = nullptr);
    ~UserOperate();

private slots:
    void on_pushButton_add_clicked();
    void on_pushButton_del_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_back_clicked();
    void on_pushButton_play_clicked();

    void tableInit();
    void showData(QTableWidgetItem *item[]);
    int mySqlInit(QSqlDatabase &db,const QString &tableName);

private:
    Ui::UserOperate *ui;
    QTableWidgetItem *item[3];
    int rowSql = 0;

};

#endif // USEROPERATE_H
