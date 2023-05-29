#ifndef SHOWMYDATA_H
#define SHOWMYDATA_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSqlDatabase>
#include <QMessageBox>
#include <QDialog>
#include <QSqlError>
#include <QSqlQuery>
#include <QVariantList>

namespace Ui {
class ShowMyData;
}

class ShowMyData : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShowMyData(QWidget *parent = 0);
    ~ShowMyData();

private slots:

    void on_pushButton_del_clicked();
    void on_pushButton_update_clicked();
    void on_pushButton_add_clicked();
    void on_pushButton_data_clicked();
    void on_pushButton_find_clicked();
    void on_pushButton_clear_clicked();

    void showData(QTableWidgetItem *item[]);
    void showFindData(int count,QSqlQuery &query, const QString &sql, QTableWidgetItem *item[]);
    void tableWidgetInit();
    int mySqlInit(QSqlDatabase &db, QString sqlName);
    void sqlCheck(QSqlQuery &query, const QString &sql, const char fun[]);

    void on_pushButton_back_clicked();
    void on_pushButton_save_clicked();

private:
    Ui::ShowMyData *ui;
    QTableWidgetItem *item[7];
    int rowSql = 0;
};

#endif // SHOWMYDATA_H
