#ifndef MINESCENE_H
#define MINESCENE_H

#include <QObject>
#include <QGraphicsScene>
#include <QDebug>
#include <QSound>

#include "mineitem.h"
#include "common.h"

class MineScene :public QGraphicsScene
{
    Q_OBJECT
public:
    explicit MineScene(QObject *parent = 0);

    QVector< QVector< MineItem *> >m_itemVec;
    int m_sceneRow;     //当前场景行数
    int m_sceneCol;     //当前场景列数
    int m_mineSum;      //当前场景雷数
    int m_currentLeve;  //当前场景难度级别

    int m_signedMineNum;//右键标记的雷数
    int m_rightMineNum; //右键标记正确的雷数
    bool m_isGameOver;  //游戏是否结束
    int m_remainNoMines;//剩余非雷数
    bool m_soundOpen;   //声音开关


    //功能:初始化场景
    //参数:无
    //返回值:无
    void initscene();


    //功能:统计周围雷数
    //参数:主场景视图对象t_item
    //返回值:无
    void countAroundMines(MineItem *t_item);


    //功能:打开所有方块
    //参数:无
    //返回值:无
    void openAllItems();


    //功能:扩散对应的方块
    //参数:主场景试图对象t_item
    //返回值:无
    void expendWater(MineItem *t_item);

signals:
    //游戏成功过关信号
    void sig_successPassGame();

    //重新开始游戏信号
    void sig_scenenewGame();

    //显示雷数信号
    void sig_scenedisplayMineNum(int);
public slots:
};

#endif // MINESCENE_H
