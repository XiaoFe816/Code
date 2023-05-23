#include "showmydata.h"
#include "ui_showmydata.h"
#include <QDebug>

ShowMyData::ShowMyData(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShowMyData)
{
    ui->setupUi(this);

    // 创建表格并初始化
    tableWidgetInit();
    // 将Mysql的数据展示在程序的表格窗口上
    showData(item);

    // 此处使用Lambda表达式是因为不想添加多余且简单的槽函数，偷个懒^3^
    connect(ui->menu, &QMenu::triggered, this, [=]() {
        QMessageBox::information(this, "帮助文档", "@@@数据格式：表格数据默认居中，无序号排序且只按照学号或UID排序，总成绩不属于MYSQL的数据。\n\n"
                                               "@@@添加数据：填写新数据时需检查学号是否与原数据冲突，以及除总成绩外的数据是否填写完成且不为空，负责保存时会弹出告警。\n\n"
                                               "@@@删除数据：默认只能按学号删除指定数据，删除后需显示最新数据查看数据是否已删除。\n\n"
                                               "@@@修改数据：默认只修改第一行的数据，因此想删除某行数据需和删除一样，找出指定学号才能修改信息。\n\n"
                                               "@@@查找数据；可根据下拉框和输入栏找出指定条件的数据，并于进行后续操作。\n");
    });
    connect(ui->menu_2, &QMenu::triggered, this, [=]() {
        QMessageBox::about(this, "关于", "作者：廖铁钢\n开发日期：2023-05-22-21:45\n版本：1.0\n其他：本软件数据展示功能很简单");
    });
}

ShowMyData::~ShowMyData()
{
    delete ui;
}

// 将MYSQL的数据同步显示在表格窗口中
void ShowMyData::showData(QTableWidgetItem *item[])
{
    QSqlDatabase db;
     rowSql = mySqlInit(db,"demo");
     QSqlQuery query(db);
     query.exec("select * from studentdata");
     ui->tableWidget->verticalHeader()->clearFocus();
     ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
     ui->tableWidget->setRowCount(rowSql);

     int i = 0;
     while (query.next()) {
         qDebug() << query.value(0).toInt()
                  << query.value(1).toString()
                  << query.value("性别").toString()
                  << query.value("年龄").toInt()
                  << query.value("语文成绩").toInt()
                  << query.value("数学成绩").toInt()
                  << query.value("英语成绩").toInt();

         // 将数据库一行的数据拷贝给表格控件
         item[0] = new QTableWidgetItem(query.value(0).toString());
         item[1] = new QTableWidgetItem(query.value(1).toString());
         item[2] = new QTableWidgetItem(query.value(2).toString());
         item[3] = new QTableWidgetItem(query.value(3).toString());
         item[4] = new QTableWidgetItem(query.value(4).toString());
         item[5] = new QTableWidgetItem(query.value(5).toString());
         item[6] = new QTableWidgetItem(query.value(6).toString());

         // 将控件添加到tableWidget并居中显示
         item[0] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 0, item[0]);
         item[1] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 1, item[1]);
         item[2] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 2, item[2]);
         item[3] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 3, item[3]);
         item[4] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 4, item[4]);
         item[5] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 5, item[5]);
         item[6] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 6, item[6]);

         // 总成绩一列的数据，此数据不在Mysql数据库内，属于自定义的部分数据的求和的结果
         int sum = query.value(4).toInt() + query.value(5).toInt() + query.value(6).toInt();
         item[7] = new QTableWidgetItem(QString::number(sum));
         item[7] ->setTextAlignment(Qt::AlignCenter);
         ui->tableWidget->setItem(i, 7, item[7]);

         i++;
     }
     db.close();
     qDebug() << "数据库数据加载完毕" << endl;
}

// 展示执行查找语句后的数据
void ShowMyData::showFindData(int count,QSqlQuery &query, const QString &sql,QTableWidgetItem *item[])
{
    query.exec(sql);
    // 清空表格内容
    ui->tableWidget->verticalHeader()->clearFocus();
    //设置表格为双击编辑模式
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    for (int i = 0; i < count; i++) {
        if (query.next()) {
            int row_count = ui->tableWidget->rowCount();
            ui->tableWidget->insertRow(row_count);

            item[0] = new QTableWidgetItem(query.value(0).toString());
            item[0] ->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 0, item[0]);
            item[1] = new QTableWidgetItem(query.value(1).toString());
            item[1] ->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 1, item[1]);
            item[2] = new QTableWidgetItem(query.value(2).toString());
            item[2] ->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 2, item[2]);
            item[3] = new QTableWidgetItem(query.value(3).toString());
            item[3] ->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 3, item[3]);
            item[4] = new QTableWidgetItem(query.value(4).toString());
            item[4] ->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 4, item[4]);
            item[5] = new QTableWidgetItem(query.value(5).toString());
            item[5] ->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 5, item[5]);
            item[6] = new QTableWidgetItem(query.value(6).toString());
            item[6] ->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 6, item[6]);
            int sum = query.value(4).toInt() + query.value(5).toInt() + query.value(6).toInt();
            item[7] = new QTableWidgetItem(QString::number(sum));
            item[7] ->setTextAlignment(Qt::AlignCenter);
            ui->tableWidget->setItem(i, 7, item[7]);
        }
    }
}

// 表格窗口控件初始化
void ShowMyData::tableWidgetInit()
{
    // 设置表格为不可编辑模式
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QStringList headList;
    headList << "编    号" << "姓    名" << "性别" << "年龄" <<  "语文成绩" << "数学成绩" << "英语成绩" << "总成绩";
    // 设置列数
    ui->tableWidget->setColumnCount(8);
    // 初始化水平表头数据
    ui->tableWidget->setHorizontalHeaderLabels(headList);
    // 设置表格成员大小
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableWidget->setColumnWidth(0,100);
    ui->tableWidget->setColumnWidth(1,150);
    ui->tableWidget->setColumnWidth(2,80);
    ui->tableWidget->setColumnWidth(3,40);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(7, QHeaderView::Stretch);
    // 设置竖直表头不可见
    ui->tableWidget->verticalHeader()->setVisible(false);

}

// 数据库初始化操作，并返回sqlName数据表的行数
int ShowMyData::mySqlInit(QSqlDatabase &db, QString sqlName)
{
    // 打印Qt支持的数据库驱动
    qDebug() << QSqlDatabase::drivers() << endl;
    // 获取数据库对象
    db = QSqlDatabase::addDatabase("QMYSQL");
    // 配置数据库
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("990816AA");
    db.setDatabaseName(sqlName);

    // 打开数据库，打开失败会弹窗警告，成功则打印提示
    if (db.open() == false) {
        QMessageBox::warning(this, "失败", db.lastError().text());
        return -1;
    } else {
        qDebug() << "成功打开本地的数据库" << endl;
    }

    int row = 0;
    QSqlQuery query(db);
    // 执行查找语句，找出studentdata数据表的所有数据
    query.exec("select * from studentdata");
    while(query.next()) {
        // 行数自增
        row++;
    }
    return row;

#if 0
    //QSqlQuery query(db);
    //query.exec("insert into studentdata(学号,姓名,性别,年龄,语文成绩,数学成绩,英语成绩) values(2023051806,'骨傲天','男',26,74,63,81);");
    //query.exec("create table student(uid int primary key auto_increment,  name varchar(255),  age int,  score int);");
    //query.exec("insert into student(name, age, score) values( '安兹乌尔恭', 23, 77);");

    // 批量插入ODBC
    // 预处理语句
    // 占位符 ?

    query.prepare("insert into student(name, age, score) values( ?, ?, ?);");
    // 给字段设置值
    QVariantList nameList;
    QVariantList ageList;
    QVariantList scoreList;
    nameList << "雅儿贝德" << "亚乌拉" << "夏提雅";
    ageList << 19 << 231 << 64;
    scoreList << 56 << 34 << 29;
    // 给字段绑定值,按顺序绑定
    query.addBindValue(nameList);
    query.addBindValue(ageList);
    query.addBindValue(scoreList);
    // 执行预处理语句
    query.execBatch();
#endif

#if 0
    // Oracle
    // 预处理语句
    // 占位符 :aa
    query.prepare("insert into student(name, age, score) values( :nam, :age, :sco);");
    // 给字段设置值
    QVariantList nameList;
    QVariantList ageList;
    QVariantList scoreList;
    nameList << "王启年" << "范思则" << "范闲";
    ageList << 19 << 16 << 17;
    scoreList << 66 << 64 << 89;
    // 给字段绑定值
    query.bindValue(":nam", nameList);
    query.bindValue(":age", ageList);
    query.bindValue(":sco", scoreList);
    // 执行预处理语句
    query.execBatch();
#endif

}

// 按下拉栏的指定条件删除数据并同步MYSQL
void ShowMyData::on_pushButton_del_clicked()
{
    QSqlDatabase db;
    mySqlInit(db,"demo");
    QSqlQuery query(db);
    // 获取筛选条件栏当前的索引
    int findFiler = ui->comboBox->currentIndex();
    // 获取筛选条件栏的文本内容
    QString curText= ui->lineEdit->text();
    qDebug() << "findFiler = " << findFiler << endl;

    if (0 == findFiler) {
        QString sql_0 = QString("delete from studentdata where 学号 = '%1';").arg(curText);
        qDebug() << sql_0 << endl;
        query.exec(sql_0);
    } else if (1 == findFiler) {
        QString sql_1 = QString("delete from studentdata where 姓名 = '%1';").arg(curText);
        qDebug() << sql_1 << endl;
        query.exec(sql_1);
    } else if (2 == findFiler) {
        QString sql_2 = QString("delete from studentdata where 性别 = '%1';").arg(curText);
        qDebug() << sql_2 << endl;
        query.exec(sql_2);
    } else if (3 == findFiler) {
        QString sql_3 = QString("delete from studentdata where 年龄 = '%1';").arg(curText);
        qDebug() << sql_3 << endl;
        query.exec(sql_3);
    }
    db.close();
}

// 修改表格数据，默认只修改第一行，需执行按学号查找的操作
void ShowMyData::on_pushButton_update_clicked()
{
    QSqlDatabase db1;
    mySqlInit(db1, "demo");
    QSqlQuery query(db1);

    // 判断表格首个单元格是否有数据，或是否执行了按学号查找操作
    if (ui->tableWidget->item(0, 0)->text() == NULL || ui->comboBox->currentIndex()) {
        db1.close();
        return;
    }

    // 将表格一行的数据存储到字符串类型的Vector容器里
    QVector<QString> v;
    for (int i = 0; i < 7; i++) {
        v.push_back(ui->tableWidget->item(0, i)->text());
    }

    // 将容器的数据写入到Mysql执行语句的字符串中，为判断语句是否正确便打印出来看看
    QString sql = QString("update studentdata set 姓名 = '%1',性别 = '%2',年龄 = %3,语文成绩 = %4,数学成绩 = %5,"
                          "英语成绩 = %6 where 学号 = %7").arg(v.at(1)).arg(v.at(2)).arg(v.at(3)).arg(v.at(4)).arg(v.at(5)).arg(v.at(6)).arg(v.at(0));
    qDebug() << sql << endl;
    query.exec(sql);
    db1.close();
}

// 在原表格上添加一空行，设置为双击可编辑模式，使能保存按钮
void ShowMyData::on_pushButton_add_clicked()
{
    QSqlDatabase db;
    int count = 0;
    count = mySqlInit(db,"demo");
    ui->tableWidget->setRowCount(count + 1);
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->pushButton_save->setEnabled(true);
    db.close();
    qDebug() << __func__ << endl;
}

// 保存新增行的数据
void ShowMyData::on_pushButton_save_clicked()
{
    QSqlDatabase db;
    int count = 0;
    count = mySqlInit(db,"demo");
    QSqlQuery query(db);
    QVector<QString> v;

    // 判断新增行的数据有除总成绩一列之外的的单元格是否有数据
    for (int i = 0; i < 7; i++) {
        QTableWidgetItem *itemTemp = ui->tableWidget->item(count, i);
        if (itemTemp == nullptr) {
            QMessageBox::warning(this, "警告", "某项数据未填写,请检查再保存");
            db.close();
            return;
        }
        QString temp = ui->tableWidget->item(count, i)->text();
        v.push_back(temp);
    }

    query.exec("select * from studentdata");
    qDebug() << __func__ << endl;

    // 判断新增数据的学号是否已存在
    while(query.next()) {
        if (query.value(0).toString() == v.at(0)) {
            QMessageBox::warning(this, "警告", "要保存的学号已存在,请程序输入新的学号保存");
            db.close();
            return;
        }
    }

    QString sql = QString("insert into studentdata (学号, 姓名, 性别, 年龄, 语文成绩, 数学成绩,"
                          "英语成绩) values(%1, '%2', '%3', %4, %5, %6, %7);").arg(v.at(0)).arg(v.at(1)).arg(v.at(2)).arg(v.at(3)).arg(v.at(4)).arg(v.at(5)).arg(v.at(6));
    query.exec(sql);

    // 保存后设置表格不可编辑并置灰保存按钮
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    QMessageBox::information(this, "保存成功", "恭喜你，保存数据成功");
    ui->pushButton_save->setEnabled(false);
    qDebug() << sql << endl;
    qDebug() << __func__ << endl;
    db.close();
}

// 实时更新并显示数据到表格中
void ShowMyData::on_pushButton_data_clicked()
{
    showData(item);
}

// 按指定条件查找数据
void ShowMyData::on_pushButton_find_clicked()
{
    QSqlDatabase db;
    mySqlInit(db,"demo");
    QSqlQuery query(db);
    // 获取筛选条件栏当前的索引
    int findFiler = ui->comboBox->currentIndex();
    // 获取筛选条件栏的文本内容
    QString curText= ui->lineEdit->text();
    qDebug() << "findFiler = " << findFiler << endl;

    int count = 0;
    if (0 == findFiler) {
        QString sql_0 = QString("select * from studentdata where 学号 = '%1';").arg(curText);
        qDebug() << sql_0 << endl;
        query.exec(sql_0);
        while (query.next()) {
            count++;
        }
        showFindData(count, query, sql_0, item);
    } else if (1 == findFiler) {
        QString sql_1 = QString("select * from studentdata where 姓名 = '%1';").arg(curText);
        qDebug() << sql_1 << endl;
        query.exec(sql_1);
        while (query.next()) {
            count++;
        }
        showFindData(count, query, sql_1, item);
    } else if (2 == findFiler) {
        QString sql_2 = QString("select * from studentdata where 性别 = '%1';").arg(curText);
        qDebug() << sql_2 << endl;
        query.exec(sql_2);
        while (query.next()) {
            count++;
        }
        showFindData(count, query, sql_2, item);
    } else if (3 == findFiler) {
        QString sql_3 = QString("select * from studentdata where 年龄 = '%1';").arg(curText);
        qDebug() << sql_3 << endl;
        query.exec(sql_3);
        while (query.next()) {
            count++;
        }
        showFindData(count, query, sql_3, item);
    }
    db.close();
}

// 清空输入栏
void ShowMyData::on_pushButton_clear_clicked()
{
    ui->lineEdit->clear();
}

// 回到上一级界面
void ShowMyData::on_pushButton_back_clicked()
{
    this->parentWidget()->show();
    this->close();
}
