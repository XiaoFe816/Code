#include "login.h"
#include "ui_login.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);
}

Login::~Login()
{
    delete ui;
}

// 清空用户输入框
void Login::on_pushButton_clearUser_clicked()
{
    ui->lineEdit_user->clear();
}

// 清空密码输入框
void Login::on_pushButton_clearPass_clicked()
{
    ui->lineEdit_passwd->clear();
}

// 登录验证，登录分为管理员登录与普通用户登录
void Login::on_pushButton_login_clicked()
{
    if (ui->comboBox->currentText() == "管理员登录") {
        if (ui->lineEdit_user->text() == ADMINUSER && ui->lineEdit_passwd->text() == ADMINPASS) {
            opt1 = new Operator(this->parentWidget());
            opt1->show();
            ui->lineEdit_passwd->clear();
            ui->lineEdit_user->clear();
            this->hide();
        } else {
            QMessageBox::warning(this, "验证错误", "    账号或密码错误\n系您的身份信息有疑惑\n    *****T_T*****\n将清空密码信息待重新输入验证\n    请重新输入验证信息!");
            ui->lineEdit_passwd->clear();
            return;
        }
    } else if (ui->comboBox->currentText() == "普通用户") {
        QSqlDatabase db;
        mySqlInit(db, "demo");
        QSqlQuery query(db);
        query.exec("select * from userdata;");

        // 账户栏选择uid或userName验证，密码则单独验证
        while (query.next()) {
            qDebug() << query.value("uid").toString() << query.value("userName").toString() << query.value(2).toString();
            qDebug() << ui->lineEdit_user->text() << endl;
            if (ui->lineEdit_user->text() == query.value("uid").toString() || ui->lineEdit_user->text() == query.value("userName").toString()) {
                if (ui->lineEdit_passwd->text() == query.value("passWord").toString()) {
                    myData = new ShowMyData(this);
                    myData->show();
                    ui->lineEdit_passwd->clear();
                    ui->lineEdit_user->clear();
                    db.close();
                    this->hide();
                } else {
                    QMessageBox::warning(this, "验证错误", "    账号或密码错误\n系您的身份信息有疑惑\n    *****T_T*****\n将清空密码信息待重新输入验证\n    请重新输入验证信息!");
                    ui->lineEdit_passwd->clear();
                    db.close();
                    return;
                }
            }
        }
    }
}

// 回到主界面
void Login::on_pushButton_exit_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

// 判断显示密码是否选中
void Login::on_checkBox_password_clicked(bool checked)
{
    if (!checked) {
        ui->lineEdit_passwd->setEchoMode(QLineEdit::Password);
    } else {
        ui->lineEdit_passwd->setEchoMode(QLineEdit::Normal);
    }
}

// 数据库初始化
void Login::mySqlInit(QSqlDatabase &db, QString sqlName)
{
    // 获取数据库对象
    db = QSqlDatabase::addDatabase("QMYSQL");
    // 配置数据库
    db.setHostName("localhost");
    db.setUserName("root");
    db.setPassword("990816AA");
    db.setDatabaseName(sqlName);

    // 打开数据库
    if (db.open() == false) {
        QMessageBox::warning(this, "失败", db.lastError().text());
        return;
    } else {
        qDebug() << "成功打开本地的数据库" << endl;
    }

//    QSqlQuery query(db);
//    query.exec("select * from userdata;");
//    while (query.next()) {
//        qDebug() << query.value("uid").toString() << query.value("userName").toString() << query.value(2).toString();
//    }
}
