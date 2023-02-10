#include "minescene.h"

QPoint m_around[8] =
{
    QPoint(-1,-1),
    QPoint(-1,0),
    QPoint(-1,1),
    QPoint(0,-1),
    QPoint(0,1),
    QPoint(1,-1),
    QPoint(1,0),
    QPoint(1,1)
};


//功能:主场景的构造函数
MineScene::MineScene(QObject *parent) : QGraphicsScene(parent)
{
    m_signedMineNum = 0;
    m_rightMineNum = 0;
    m_isGameOver = false;
    m_soundOpen = false;
}


//功能:初始化游戏场景，主要创建方块和随机布雷及连接信号
void MineScene::initscene()
{
    qDebug() << __func__ << endl;
    this->m_remainNoMines = m_sceneRow*m_sceneCol - m_mineSum; //初始化非雷数＝方块总数 - 总雷数
    for(int i=0; i<m_sceneRow ; i++)  //布置方块
    {
        QVector<MineItem *> t_Vec;
        for(int j=0; j<m_sceneCol; j++)
        {
            MineItem *t_item = new MineItem(i,j,QPixmap("://images/cover1.png")); //设置雷的图片
            t_item->setPos(j * COMMON::MAPWIDTH,i * COMMON::MAPHEIGHT);
            this->addItem(t_item);
            t_Vec.push_back(t_item);
        }
        this->m_itemVec.push_back(t_Vec);
    }

    srand(time(NULL));              //随机布雷。
    for(int i=0 ; i<m_mineSum ; i++)
    {
        int t_rows = rand() % m_sceneRow;
        int t_cols = rand() % m_sceneCol;   //随机产生一个坐标
        if(!this->m_itemVec[t_rows][t_cols]->m_isMine) //如果该方块不是雷，则设置其为雷，并将周围八个方块上的周围雷数加1
        {
            this->m_itemVec[t_rows][t_cols]->m_isMine = true;
            this->countAroundMines(this->m_itemVec[t_rows][t_cols]);
        }
        else
            i--;
    }

    for(int i = 0; i<m_sceneRow; i++)
    {
        for(int j=0 ; j < m_sceneCol ; j++)
        {
            this->connect(this->m_itemVec[i][j],SIGNAL(sig_restartGame()),this,SIGNAL(sig_scenenewGame()));
                    //将所有方块的重新开始游戏信号连接到场景的重新开始游戏信号
            this->connect(this->m_itemVec[i][j],SIGNAL(sig_resetMineNum(int)),this,SIGNAL(sig_scenedisplayMineNum(int)));
                    //将所有方块的重新设置雷数信号连接到场景的重新显示雷数信号
        }
    }
}


//功能:统计该方块周围的雷数
void MineScene::countAroundMines(MineItem *t_item)  //如果为空或者不是雷，则返回
{
    qDebug() << __func__ << endl;
    if(NULL == t_item || !t_item->m_isMine)
        return ;

    for(int i=0 ; i<8 ; i++)        //循环查找 8 个方位
    {
        int t_x = t_item->m_X + m_around[i].x();    //计算所找方块在容器中的行
        int t_y = t_item->m_Y + m_around[i].y();    //计算所找方块在容器中的列

        if(t_x < 0 || t_x >= this->m_sceneRow || t_y < 0 || t_y >= this->m_sceneCol) //如果越界,则重新下一次循环
            continue;

        if(m_itemVec[t_x][t_y]->m_isMine)       //如果所找方块是雷，则重新下一次循环
            continue;
        m_itemVec[t_x][t_y]->m_aroundMineNum++; //所找方块的周围雷数加 1
    }
}


//功能:打开所有的方块
void MineScene::openAllItems()
{
    qDebug() << __func__ << endl;
    if(this->m_isGameOver)
        return ;
    for(int i=0 ; i<m_sceneRow ; i++) //循环遍历所有方块
    {
        for(int j=0 ; j<m_sceneCol ; j++)
        {
            m_itemVec[i][j]->m_isOpened = true; //将方块设置为打开
            if(m_itemVec[i][j]->m_isMine)       //如果是雷则将方块图片设置为雷图片
                m_itemVec[i][j]->setPixmap(QPixmap("://images/blast1.png"));

            else                 //如果不是雷则将方块图片设置为方块周围雷数所对应图片
            {
                QString path = tr("://images/") + QString::number(m_itemVec[i][j]->m_aroundMineNum) + tr(".png");
                m_itemVec[i][j]->setPixmap(path);
            }
        }
    }
}


//功能:扩散函数，查找周围 8 个方位方块的周围雷数是否为 0,如果是则递归，如果不是则设置方块图片为方块周围雷数对应图片
void MineScene::expendWater(MineItem *t_item)
{
    qDebug() << __func__ << endl;
    if(NULL == t_item || t_item->m_isMine) //如果为空，如果是雷则返回
        return ;

    for(int i=0 ; i<8 ;i++)                //循环查找 8 个方位
    {
        int t_x = t_item->m_X + m_around[i].x(); //计算所找方块在容器中的行
        int t_y = t_item->m_Y + m_around[i].y(); //计算所找方块在容器中的列

        if(t_x < 0 || t_x >= m_sceneRow || t_y < 0 || t_y >= m_sceneCol)
            continue;
        else if(m_itemVec[t_x][t_y]->m_isMine || m_itemVec[t_x][t_y]->m_isOpened)
            continue;
        else if(m_itemVec[t_x][t_y]->m_rMouseKeyNum > 0)
            continue;

        m_itemVec[t_x][t_y]->m_isOpened = true;
        this->m_remainNoMines--;

        int itemVecNum = m_itemVec[t_x][t_y]->m_aroundMineNum;
        if(itemVecNum == 0)
        {
            expendWater(m_itemVec[t_x][t_y]);
        }

        QString path = tr("://images/") + QString::number(m_itemVec[t_x][t_y]->m_aroundMineNum) + tr(".png");
        m_itemVec[t_x][t_y]->setPixmap(QPixmap(path));      //显示点击的非雷方块的数字
    }

    if(m_remainNoMines == 0)                    //如果剩余非雷数为0，则游戏通关
    {
        m_isGameOver = true;
        if(m_soundOpen)
            QSound::play("://images/win.wav");
        this->openAllItems();                   //打开所有方块
        emit sig_successPassGame();             //发送通关信号
    }
}
