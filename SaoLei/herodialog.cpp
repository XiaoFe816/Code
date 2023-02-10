#include "herodialog.h"

HeroDialog::HeroDialog(QWidget *parent) : QDialog(parent)
{
    this->setWindowTitle("排雷英雄榜");
    this->setWindowIcon(QIcon("://images/error0.png"));

    lowRecordTimeLabel = new QLabel("低级记录:");
    midRecordTimeLabel = new QLabel("中级记录:");       //创建级别标签
    highRecordTimeLabel = new QLabel("高级记录:");

    time_1 = new QLabel("999");
    time_2 = new QLabel("999");    //创建时间记录标签
    time_3 = new QLabel("999");

    lowRecordNameLabel = new QLabel("匿名");
    midRecordNameLabel = new QLabel("匿名");      //创建名字记录标签
    highRecordNameLabel = new QLabel("匿名");

    QPushButton *init_button = new QPushButton("重设排行榜");
    QPushButton *exit_button = new QPushButton("确定");        //创建按钮对象
    this->connect(init_button,SIGNAL(clicked(bool)),this,SLOT(slot_reset()));//点击按钮后连接对应槽函数
    this->connect(exit_button,SIGNAL(clicked(bool)),this,SLOT(close()));

    QGridLayout *hlayout = new QGridLayout(this);  //网格布局
    hlayout->addWidget(lowRecordTimeLabel,0,0);
    hlayout->addWidget(time_1,0,1);
    hlayout->addWidget(lowRecordNameLabel,0,2);

    hlayout->addWidget(midRecordTimeLabel,1,0);
    hlayout->addWidget(time_2,1,1);
    hlayout->addWidget(midRecordNameLabel,1,2);

    hlayout->addWidget(highRecordTimeLabel,2,0);
    hlayout->addWidget(time_3,2,1);
    hlayout->addWidget(highRecordNameLabel,2,2);

    hlayout->addWidget(init_button);
    hlayout->addWidget(exit_button);

    this->readSettings();   //读取排行榜的数据
}

void HeroDialog::readSettings()
{
    qDebug() << __func__ << endl;
    QSettings *settings = new QSettings("HeroData","hero");   //创建注册表对象
    settings->beginGroup("heroRecord");
    QString lowTime = settings->value("lowHeroRecord").toString();
    QString lowName = settings->value("lowHeroName").toString();

    QString midTime = settings->value("midHeroRecord").toString();
    QString midName = settings->value("midHeroName").toString();

    QString highTime = settings->value("highHeroRecord").toString();
    QString highName = settings->value("highHeroName").toString();
    settings->endGroup();

    time_1->setText(lowTime);               //将注册表的数据设置到对应的标签
    lowRecordNameLabel->setText(lowName);
    time_2->setText(midTime);
    midRecordNameLabel->setText(midName);
    time_3->setText(highTime);
    highRecordNameLabel->setText(highName);
}

void HeroDialog::init_heroRecord()
{
    qDebug() << __func__ << endl;
    QSettings *settings = new QSettings("HeroData","hero");     //创建注册表对象
    settings->beginGroup("heroRecord");
    settings->setValue("lowHeroRecord",time_1->text());
    settings->setValue("lowHeroName",lowRecordNameLabel->text());  //将标签的文本写入到注册表
    settings->setValue("midHeroRecord",time_2->text());
    settings->setValue("midHeroName",midRecordNameLabel->text());
    settings->setValue("highHeroRecord",time_3->text());
    settings->setValue("highHeroName",highRecordNameLabel->text());
    settings->endGroup();

}

void HeroDialog::slot_reset()
{
    qDebug() << __func__ << endl;
    time_1->setText("999");
    time_2->setText("999");
    time_3->setText("999");
    lowRecordNameLabel->setText("匿名");
    midRecordNameLabel->setText("匿名");
    highRecordNameLabel->setText("匿名");
    this->init_heroRecord();            //将初始化的文本写入注册表
}
