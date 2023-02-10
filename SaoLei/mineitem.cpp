#include "mineitem.h"
#include "minescene.h"

//功能:主视图的构造函数
MineItem::MineItem(int t_x,int t_y,QPixmap pixmap,QGraphicsItem *parent):
    QGraphicsPixmapItem(pixmap,parent),m_X(t_x),m_Y(t_y)
{
    m_isMine = false;
    m_isOpened = false;
    m_aroundMineNum = 0;
    m_rMouseKeyNum = 0;
    m_isRightMouse = false;
}


//功能:鼠标点击事件
void MineItem::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    qDebug() << __func__ << endl;
    MineScene *minescene = (MineScene *)this->scene();
    if(minescene->m_isGameOver || this->m_isOpened)
        return ;

    if(e->button() == Qt::LeftButton && !m_isRightMouse)        //左键点击
    {
        this->setPixmap(QPixmap("://images/press.png"));        //设置左键点击的图片
    }
    else if(e->button() == Qt::RightButton) //右键点击
    {
        m_rMouseKeyNum++;
        if(m_rMouseKeyNum == 1)         //右键点击1次
        {
            m_isRightMouse = true;
            minescene->m_signedMineNum++;
            this->setPixmap(QPixmap("://images/flag1.png"));        //设置右键点击1次标记雷的图片
            emit sig_resetMineNum(minescene->m_signedMineNum);

            if(this->m_isMine)
                minescene->m_rightMineNum++;           
        }
        else if(m_rMouseKeyNum == 2)    //右键点击两次
        {
            m_isRightMouse = true;
            minescene->m_signedMineNum--;
            this->setPixmap(QPixmap("://images/flag2.png"));        //设置右键点击2次标记雷的图片
            emit sig_resetMineNum(minescene->m_signedMineNum);

            if(this->m_isMine)
                minescene->m_rightMineNum--;
        }
        else if(m_rMouseKeyNum == 3)  //右键点击三次，右键点击次数置0
        {
            m_isRightMouse = false;
            this->setPixmap(QPixmap("://images/cover1.png"));       //还原图片
            m_rMouseKeyNum = 0;
        }

        if(minescene->m_rightMineNum) //右键标记正确则游戏通关
        {
            QSettings *setting = new QSettings("MineData","leve");
            setting->beginGroup("currentGame");
            int mine = setting->value("current_mine").toInt();
            setting->endGroup();
            if(mine == minescene->m_rightMineNum && minescene->m_signedMineNum == mine)  //刚好全标记雷数
            {
                minescene->m_isGameOver = true;
                emit minescene->sig_successPassGame(); //发送游戏通关信号
            }
        }
    }
}


//功能鼠标释放事件
void MineItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
    qDebug() << __func__ << endl;
    MineScene *minescene = (MineScene *)this->scene();

    if(minescene->m_isGameOver || this->m_isOpened || this->m_isRightMouse) //游戏结束、方块已经被打开和被右键标记后返回
        return ;

    if(e->button() == Qt::LeftButton)
    {
        m_isOpened = true;
        if(m_isMine)                                            //释放后的方块是雷
        {
            this->setPixmap(QPixmap("://iamges/mine1.png"));    //布置雷的图片
            if(minescene->m_soundOpen)
                QSound::play("://images/fail.wav");

            minescene->openAllItems();
            minescene->m_isGameOver = true;

            QMessageBox::information((QWidget*)minescene->parent(),tr("排雷失败"),"很遗憾，您踩到雷了");
            emit this->sig_restartGame();
            return ;
        }
        else
        {
            if(!m_aroundMineNum)
            {
                this->setPixmap(QPixmap("://images/0.png"));    //布置空白图片
                minescene->expendWater(this);
            }
            else
            {
                QString path = tr("://images/") + QString::number(m_aroundMineNum) + tr(".png"); //布置数字图片
                this->setPixmap(QPixmap(path));
            }
        }

        minescene->m_remainNoMines--;
        if(!minescene->m_remainNoMines)         //剩余非雷数为0后，游戏结束
        {
            minescene->m_isGameOver = true;
            if(minescene->m_soundOpen)
                QSound::play("://iamges/win.wav");

            minescene->openAllItems();
            minescene->sig_successPassGame();       //发送游戏通关信号
        }
    }

}
