#include "useroperate.h"
#include "ui_useroperate.h"

UserOperate::UserOperate(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UserOperate)
{
    ui->setupUi(this);
    tableInit();
    showData(item);
}

UserOperate::~UserOperate()
{
    delete ui;
}

// 表格初始化
void UserOperate::tableInit()
{
    QStringList headList;
    headList << "uid" << "userName" << "passWord";
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setHorizontalHeaderLabels(headList);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,150);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setVisible(false);
}

// 将MYSQL的数据同步并显示到表格窗口
void UserOperate::showData(QTableWidgetItem *item[])
{
    QSqlDatabase db;
     rowSql = mySqlInit(db,"demo");
     QSqlQuery query(db);
     query.exec("select * from userdata");
     ui->tableWidget->verticalHeader()->clearFocus();
     ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
     ui->tableWidget->setRowCount(rowSql);

     int i = 0;
     while (query.next()) {
         item[0] = new QTableWidgetItem(query.value(0).toString());
         item[1] = new QTableWidgetItem(query.value(1).toString());
         item[2] = new QTableWidgetItem(query.value(2).toString());

         item[0] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 0, item[0]);
         item[1] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 1, item[1]);
         item[2] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 2, item[2]);
         i++;
     }
     db.close();
     qDebug() << "数据库数据加载完毕" << endl;
}

// 数据库初始化
int UserOperate::mySqlInit(QSqlDatabase &db, const QString &tableName)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    // 配置数据库
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("990816AA");
    db.setDatabaseName(tableName);
    // 打开数据库
    if (db.open() == false) {
        QMessageBox::warning(this, "失败", db.lastError().text());
        return -1;
    } else {
        qDebug() << "成功打开本地的数据库" << endl;
    }

    int count = 0;
    QSqlQuery query(db);
    query.exec("select * from userdata");
    while (query.next()) {
        count++;
        qDebug() << query.value(0).toInt() << query.value(1).toString() << query.value(2).toString();
    }
    return count;
}

// 添加新用户
void UserOperate::on_pushButton_add_clicked()
{
    QSqlDatabase db;
    int count = 0;
    count = mySqlInit(db,"demo");
    QSqlQuery query(db);

    if (ui->pushButton_add->text() == "添加用户") {
        ui->pushButton_add->setText("保存用户");
        ui->tableWidget->setRowCount(count + 1);
        ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    } else if (ui->pushButton_add->text() == "保存用户") {
        QVector<QString> v;
        for (int i = 0; i < 3; i++) {
            QTableWidgetItem *itemTemp = ui->tableWidget->item(count, i);
            if (itemTemp == nullptr) {
                QMessageBox::warning(this, "警告", "某项数据未填写,请检查再保存");
                db.close();
                return;
            }

            QString temp = ui->tableWidget->item(count, i)->text();
            v.push_back(temp);
        }

        query.exec("select * from userdata");
        while(query.next()) {
            if (query.value(0).toString() == v.at(0)) {
                QMessageBox::warning(this, "警告", "要保存的uid已存在,请程序输入新的uid保存");
                db.close();
                return;
            }
        }

        QString sql = QString("insert into userdata (uid, userName, passWord) values(%1, '%2', '%3');").arg(v.at(0)).arg(v.at(1)).arg(v.at(2));
        query.exec(sql);
        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        QMessageBox::information(this, "保存成功", "恭喜你，保存数据成功");
        qDebug() << sql << endl;
        ui->pushButton_add->setText("添加用户");
    }

    db.close();
}

// 删除用户
void UserOperate::on_pushButton_del_clicked()
{
    QSqlDatabase db;
    mySqlInit(db,"demo");
    QSqlQuery query(db);
    QString uid = ui->lineEdit->text();
    QString sql = QString("delete from userdata where uid = %1;").arg(uid);
    qDebug() << sql << endl;
    query.exec(sql);
    db.close();
}

// 修改用户信息
void UserOperate::on_pushButton_update_clicked()
{
    QSqlDatabase db;
    int count = mySqlInit(db, "demo");
    QSqlQuery query(db);

    QVector<QString> vUid;
    QVector<QString> vPass;
    QVector<QString> vSql;
    query.exec("select * from userdata");
    while (query.next()) {
        vUid.push_back(query.value(0).toString());
    }

    for (int i = 0; i < count; i++) {
        vPass.push_back(ui->tableWidget->item(i, 2)->text());
        QString temp = QString("update userdata set passWord = '%1' where uid = %2;").arg(vPass.at(i)).arg(vUid.at(i));
        vSql.push_back(temp);
        query.exec(vSql.at(i));
    }

    db.close();
}

// 回到上一级界面
void UserOperate::on_pushButton_back_clicked()
{
    this->parentWidget()->show();
    this->close();
}

// 显示实时数据
void UserOperate::on_pushButton_play_clicked()
{
    showData(item);
}
