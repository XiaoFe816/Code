#include "mywidget.h"

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{
    // 限制自定义窗口大小
    this->setMinimumWidth(150);
    this->setMaximumWidth(220);

    // 标签申请空间
    lableUp = new QLabel("↑:头");
    lableDown = new QLabel("↓:尾");
    lableLeft = new QLabel("←:左");
    lableRight = new QLabel("→:右");

    // 按键申请空间
    buttonUp = new QPushButton("↑");
    buttonDown = new QPushButton("↓");
    buttonLeft = new QPushButton("←");
    buttonRight = new QPushButton("→");
    buttonCloseCur = new QPushButton("关闭此文件");
    buttonOnlyCur = new QPushButton("关闭非当前文件");
    buttonCloseAll = new QPushButton("关闭所有");

    // 部分按键竖直布局
    QVBoxLayout *vbox_1 = new QVBoxLayout;
    vbox_1->addWidget(buttonCloseCur);
    vbox_1->addWidget(buttonOnlyCur);
    vbox_1->addWidget(buttonCloseAll);

    // 标签和部分按键网格布局
    QGridLayout *grid_L1 = new QGridLayout;
    grid_L1->addWidget(lableUp, 0, 0);
    grid_L1->addWidget(buttonUp, 0, 1);
    grid_L1->addWidget(lableDown, 0, 2);
    grid_L1->addWidget(buttonLeft, 1, 0);
    grid_L1->addWidget(buttonRight, 1, 2);
    grid_L1->addWidget(lableLeft, 2, 0);
    grid_L1->addWidget(buttonDown, 2, 1);
    grid_L1->addWidget(lableRight, 2, 2);

    // 设置总布局方式为竖直布局
    QVBoxLayout *vbox_2 = new QVBoxLayout;
    vbox_2->addLayout(grid_L1);
    vbox_2->addLayout(vbox_1);
    this->setLayout(vbox_2);
}
