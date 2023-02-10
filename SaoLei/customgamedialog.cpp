#include "customgamedialog.h"

CustomGameDialog::CustomGameDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("自定义游戏"));  //设置标题

    QLabel *label_1 = new QLabel("行 数:"); //建立行数标签对象
    QLabel *label_2 = new QLabel("列 数:"); //建立列数标签对象
    QLabel *label_3 = new QLabel("雷 数:"); //建立雷数标签对象

    rowSpinbox = new QSpinBox;      //创建行数分量框对象
    rowSpinbox->setRange(5,50);     //行数设置范围
    rowSpinbox->setSingleStep(1);   //行数单步跳跃值
    rowSpinbox->setValue(10);       //行分量框初始值

    colSpinbox = new QSpinBox;      //列数分量框
    colSpinbox->setRange(10,80);    //列数设置范围
    colSpinbox->setSingleStep(2);   //列数单步跳跃值
    colSpinbox->setValue(10);       //列分量框初始值

    mineNumSpinbox = new QSpinBox;  //雷数分量框
    mineNumSpinbox->setRange(1,90); //雷数设置范围
    mineNumSpinbox->setSingleStep(1);//雷数单步跳跃值
    mineNumSpinbox->setValue(10);   //雷分量框初始值

    QPushButton *ok_button = new QPushButton("确 定");        //创建按钮对象
    QPushButton *cancel_button = new QPushButton("取 消");

    QGridLayout *glayout = new QGridLayout(this);       //创建网格布局
    glayout->addWidget(label_1,0,0);
    glayout->addWidget(rowSpinbox,0,1);
    glayout->addWidget(label_2,1,0);
    glayout->addWidget(colSpinbox,1,1);

    glayout->addWidget(label_3,2,0);
    glayout->addWidget(mineNumSpinbox,2,1);
    glayout->addWidget(ok_button);
    glayout->addWidget(cancel_button);

    this->connect(ok_button,SIGNAL(clicked(bool)),this,SLOT(slotAccepetok())); //连接信号槽函数
    this->connect(cancel_button,SIGNAL(clicked(bool)),this,SLOT(close()));
    this->readSettings();       //读取注册表的设置的数据
}

void CustomGameDialog::readSettings()
{
    qDebug() << __func__ << endl;
    QSettings *settings = new QSettings("MineData","leve"); //创建注册表对象
    settings->beginGroup("currentGame");
    int row = settings->value("current_row").toInt();
    int col = settings->value("current_col").toInt();
    int mine = settings->value("current_mine").toInt();
    settings->endGroup();

    this->rowSpinbox->setValue(row);      //设置行数分量框的注册表的值
    this->colSpinbox->setValue(col);      //设置列数分量框的注册表的值
    this->mineNumSpinbox->setValue(mine); //设置雷数分量框的注册表的值
}

void CustomGameDialog::writeSettings()
{
    qDebug() << __func__ << endl;
    QSettings *settings = new QSettings("MineData","leve");     //创建注册表对象
    settings->beginGroup("currentGame");
    settings->setValue("current_row",rowSpinbox->value());      //把当前行数分量框的值写入注册表
    settings->setValue("current_col",colSpinbox->value());      //把当前列数分量框的值写入注册表
    settings->setValue("current_mine",mineNumSpinbox->value()); //把当前雷数分量框的值写入注册表
    settings->setValue("current_leve",COMMON::CUSOMLEVE);       //把当前级别的值写入注册表
    settings->endGroup();
}

void CustomGameDialog::slotAccepetok()
{
    qDebug() << __func__ << endl;
    int row = this->rowSpinbox->value();
    int col = this->colSpinbox->value();
    int count = this->mineNumSpinbox->value();

    emit this->signal_sendCustomSet(row,col,count);  //发送信号，并将行、列、雷数的数据一并发送
    this->writeSettings();
    this->close();
}
