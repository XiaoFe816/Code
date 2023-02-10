#ifndef MINEITEM_H
#define MINEITEM_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QPixmap>
#include <QMessageBox>
#include <QSound>
#include <QSettings>

#include <stdlib.h>
#include <time.h>

class MineItem : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    explicit MineItem(int t_x,int t_y,QPixmap pixmap,QGraphicsItem *parent=0);

    int m_X;            //在容器中的行数
    int m_Y;            //在容器中的列数
    bool m_isMine;      //是否为雷
    bool m_isOpened;    //是否打开
    int m_aroundMineNum;//周围雷数
    int m_rMouseKeyNum; //右键点击的次数
    bool m_isRightMouse;//是否为右键

    //功能:鼠标点击事件函数
    //参数:场景鼠标事件对象e
    //返回值:无
    void mousePressEvent(QGraphicsSceneMouseEvent *e);


    //功能:鼠标释放事件函数
    //参数:场景鼠标事件对象e
    //返回值:无
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);

signals:
    //重新开始游戏的信号
    void sig_restartGame();


    //重设雷数的信号
    //int:标记的雷数
    void sig_resetMineNum(int t_signedMineNum);

public slots:
};

#endif // MINEITEM_H
