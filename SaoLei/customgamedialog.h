#ifndef CUSTOMGAMEDIALOG_H
#define CUSTOMGAMEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QSpinBox>
#include <QDebug>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QSettings>

#include "common.h"

class CustomGameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CustomGameDialog(QWidget *parent = 0);

    QSpinBox *colSpinbox;       //列分量框
    QSpinBox *rowSpinbox;       //行分量框
    QSpinBox *mineNumSpinbox;   //雷数分量框

    //功能:读自定义游戏设置文件
    //参数:无
    //返回值:无
    void readSettings();

    //功能:写自定义游戏设置文件
    //参数:无
    //返回值:无
    void writeSettings();

signals:
    //功能: 发送自定义游戏行，列，雷数的数据的信号函数(只声明，不实现)
    //参数:int:自定义的行、列、雷数
    void signal_sendCustomSet(int,int,int);

public slots:
    //功能:接收"重新设置"按钮的槽函数
    //参数:无
    //返回值:无
    void slotAccepetok();
};

#endif // CUSTOMGAMEDIALOG_H
