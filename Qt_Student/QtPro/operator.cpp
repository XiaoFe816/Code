#include "operator.h"
#include "ui_operator.h"
#include <QMessageBox>

Operator::Operator(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Operator)
{
    ui->setupUi(this);
}

Operator::~Operator()
{
    delete ui;
}

// 回到主界面
void Operator::on_pushButton_menu_clicked()
{
    this->parentWidget()->show();
    this->hide();
}

// 进入信息操作界面
void Operator::on_pushButton_operate_clicked()
{
    myData = new ShowMyData(this);
    myData->show();
    this->hide();
}

// 进入用户信息操作界面
void Operator::on_pushButton_user_clicked()
{
    optUser = new UserOperate(this);
    optUser->show();
    this->hide();
}
