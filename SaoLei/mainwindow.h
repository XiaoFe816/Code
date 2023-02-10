#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include <QLCDNumber>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QAction>
#include <QActionGroup>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>
#include <QColorDialog>
#include <QDebug>
#include <QSettings>
#include <QInputDialog>
#include <QGraphicsView>
#include <QLineEdit>

#include "minescene.h"
#include "common.h"
#include "customgamedialog.h"
#include "herodialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    QAction *newaction;         //新游戏行为
    QAction *lowleveaction;     //低端局行为
    QAction *midleveaction;     //一般局行为
    QAction *highleveaction;    //高端局行为
    QAction *customaction;      //自定义行为
    QAction *coloraction;       //颜色行为
    QAction *soundaction;       //声音行为
    QAction *heroaction;        //排行榜行为
    QAction *aboutaction;       //关于行为
    QAction *exitaction;        //退出行为

    QWidget *centralget;        //主程序界面
    QGraphicsView *mineView;    //主场景试图
    MineScene *mineScene;       //主程序场景

    QLCDNumber *mineNumLcd;     //数码管显示的雷数
    QLCDNumber *timeLcd;        //数码管显示的时间
    QPushButton *smile_button;  //笑脸(新游戏)按钮
    int m_time;                 //当前用时数
    QTimer *m_timer;            //定时器

    //功能:创建行为
    //参数:无
    //返回值:无
    void create_action();


    //功能:创建菜单
    //参数:无
    //返回值:无
    void create_menu();


    //功能:读当前游戏设置
    //参数:无
    //返回值:无
    void readsettings();


    //功能:写当前游戏设置
    //参数:无
    //返回值:无
    void writesettings();

signals:

public slots:
    //功能:开始新游戏槽
    //参数:无
    //返回值:无
    void slot_newgame();


    //功能:点击游戏级别行为开始新游戏槽
    //参数:行为对象
    //返回值:无
    void slot_newgamebyleve(QAction*);


    //功能:接收自定义游戏设置槽
    //参数:接收到到的行、列、雷数
    //返回值:无
    void slot_acceptCutsomvale(int,int,int);


    //功能:设置数码管颜色的槽
    //参数:无
    //返回值:无
    void slot_colorchanged();


    //功能:设置声音的槽
    //参数:无
    //返回值:无
    void slot_soundchanged();


    //功能:显示排行榜的槽
    //参数:无
    //返回值:无
    void slot_herochecked();


    //功能:显示关于"排雷行动"的槽
    //参数:无
    //返回值:无
    void slot_about();


    //功能:更新英雄榜的槽
    //参数:无
    //返回值:无
    void slot_updatehero();


    //功能:显示雷数的槽
    //参数:接收到的标记的雷数
    //返回值:无
    void slot_displayMineNum(int);


    //功能:显示时间的槽
    //参数:无
    //返回值:无
    void slot_displayTime();
};

#endif // MAINWINDOW_H
