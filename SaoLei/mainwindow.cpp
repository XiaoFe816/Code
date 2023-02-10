#include "mainwindow.h"


//功能:主窗口构造函数
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),centralget(0),mineView(0),mineScene(0),mineNumLcd(0),timeLcd(0)
    ,smile_button(0),m_timer(0)

{
    this->resize(900,600);
    this->setWindowTitle(tr("排雷行动"));       //设置窗口标题
    this->setWindowIcon(QIcon(":/images/picture1.ico")); //设置窗口标题图片
    this->create_action();  //创建行为
    this->create_menu();    //创建行为菜单
    this->slot_newgame();   //开始新游戏

}


//功能:创建行为
void MainWindow::create_action()
{

    qDebug() << __func__ << endl;
    newaction = new QAction("重新开始",this);
    this->connect(newaction,SIGNAL(triggered(bool)),this,SLOT(slot_newgame())); //连接到开始新游戏槽函数
    lowleveaction = new QAction("低端局",this);
    lowleveaction->setCheckable(true);      //设置可选选项
    lowleveaction->setChecked(true);        //默认选中该行为

    midleveaction = new QAction("一般局",this);
    midleveaction->setCheckable(true);
    highleveaction = new QAction("高端局",this);
    highleveaction->setCheckable(true);
    customaction = new QAction("自定义局",this);
    customaction->setCheckable(true);

    QActionGroup *actionGroup = new QActionGroup(this); //添加行为组
    actionGroup->addAction(lowleveaction);      //将游戏级别添加到行为组
    actionGroup->addAction(midleveaction);
    actionGroup->addAction(highleveaction);
    actionGroup->addAction(customaction);
    this->connect(actionGroup,SIGNAL(triggered(QAction*)),this,SLOT(slot_newgamebyleve(QAction*))); //连接到级别游戏的槽函数

    coloraction = new QAction("颜 色",this);
    coloraction->setCheckable(true);
    coloraction->setChecked(true);      //默认选中颜色行为
    this->connect(coloraction,SIGNAL(triggered(bool)),this,SLOT(slot_colorchanged())); //连接到修改颜色的槽函数
    soundaction = new QAction("声音",this);
    soundaction->setCheckable(true);
    soundaction->setChecked(true);      //默认选中声音行为
    this->connect(soundaction,SIGNAL(triggered(bool)),this,SLOT(slot_soundchanged())); //连接到声音开关的槽函数

    heroaction = new QAction("排行榜",this);
    this->connect(heroaction,SIGNAL(triggered(bool)),this,SLOT(slot_herochecked())); //连接到显示排行榜的槽函数
    aboutaction = new QAction("关 于",this);
    this->connect(aboutaction,SIGNAL(triggered(bool)),this,SLOT(slot_about()));  //连接到关于的槽函数

    exitaction = new QAction("退 出",this);
    this->connect(exitaction,SIGNAL(triggered(bool)),this,SLOT(close()));   //退出游戏
}


//功能:创建菜单
void MainWindow::create_menu()
{
    qDebug() << __func__ << endl;
    QMenuBar *mbr = this->menuBar();    //创建菜单对象
    QMenu *gameMenu = mbr->addMenu("游戏(Game)"); //添加游戏菜单
    QMenu *helpMenu = mbr->addMenu("帮助(Help)"); //添加帮助菜单

    gameMenu->addAction(newaction);
    gameMenu->addSeparator();
    gameMenu->addAction(lowleveaction);
    gameMenu->addAction(midleveaction);
    gameMenu->addAction(highleveaction);
    gameMenu->addAction(customaction);
    gameMenu->addSeparator();
    gameMenu->addAction(soundaction);
    gameMenu->addAction(coloraction);
    gameMenu->addSeparator();
    gameMenu->addAction(heroaction);
    gameMenu->addAction(exitaction);

    helpMenu->addAction(aboutaction);
}


//功能:读当前游戏设置，并设置到场景的行，列，雷数，级别
void MainWindow::readsettings()
{
    qDebug() << __func__ << endl;
    QSettings *settings = new QSettings("MineData","leve");     //创建注册表对象
    settings->beginGroup("currentGame");
    this->mineScene->m_sceneRow = settings->value("current_row").toInt();
    this->mineScene->m_sceneCol = settings->value("current_col").toInt();
    this->mineScene->m_mineSum = settings->value("current_mine").toInt();
    this->mineScene->m_currentLeve = settings->value("current_leve").toInt();
    settings->endGroup();
}


//功能:写当前游戏设置，将当前场景的行，列，雷数，级别写入到注册表
void MainWindow::writesettings()
{
    qDebug() << __func__ << endl;
    QSettings *settings = new QSettings("MineData","leve");      //创建注册表对象
    settings->beginGroup("currentGame");
    settings->setValue("current_row",this->mineScene->m_sceneRow);
    settings->setValue("current_col",this->mineScene->m_sceneCol);
    settings->setValue("current_mine",this->mineScene->m_mineSum);
    settings->setValue("current_leve",this->mineScene->m_currentLeve);
    settings->endGroup();
}


//功能:开始新游戏
void MainWindow::slot_newgame()
{
    qDebug() << __func__ << endl;
    centralget->deleteLater();
    mineView->deleteLater();
    mineScene->deleteLater();
    mineNumLcd->deleteLater();
    timeLcd->deleteLater();
    smile_button->deleteLater();
    m_timer->deleteLater();     //清理旧对象 deleteLater();

    centralget = new QWidget(this); //创建主界面对象

    QPalette lcdPale;       //创建调色板对象
    lcdPale.setColor(QPalette::Normal,QPalette::WindowText,Qt::red); //默认调色板的颜色为红色
    mineNumLcd = new QLCDNumber(centralget);    //创建显示雷数的数码管
    mineNumLcd->setPalette(lcdPale);       //设置数字的颜色
    mineNumLcd->setDigitCount(3);          //设置数字的大小

    timeLcd = new QLCDNumber(centralget);   //创建显示当前用时的数码管
    timeLcd->setPalette(lcdPale);
    timeLcd->setDigitCount(3);

    smile_button = new QPushButton(centralget);  //创建笑脸按钮
    smile_button->setIcon(QIcon("://images/smile.png"));    //设置按钮图片
    this->connect(smile_button,SIGNAL(clicked(bool)),this,SLOT(slot_newgame())); //连接到开始新游戏槽


    QHBoxLayout *hlayout = new QHBoxLayout;  //创建水平布局
    hlayout->addWidget(mineNumLcd);     //将雷数数码管添加到水平布局
    hlayout->addStretch();      //填充
    hlayout->addWidget(smile_button);   //将笑脸按钮添加到水平布局
    hlayout->addStretch();
    hlayout->addWidget(timeLcd);        //将当前用时数码管添加到水平布局

    mineView = new QGraphicsView(centralget);   //创建主视图
    mineScene = new MineScene(mineView);    //创建主场景
    mineView->setScene(mineScene);  //将场景加入到视图
    this->readsettings();  //并读取游戏当前设置

    this->connect(mineScene,SIGNAL(sig_scenenewGame()),this,SLOT(slot_newgame()));  //接收开始新游戏的信号,连接到新游戏的槽函数
    this->connect(mineScene,SIGNAL(sig_scenedisplayMineNum(int)),this,SLOT(slot_displayMineNum(int))); //接收标记的数据,连接到雷数显示的槽函数
    this->connect(mineScene,SIGNAL(sig_successPassGame()),this,SLOT(slot_updatehero())); //接收游戏通关的信号,连接到更新排行榜的槽函数函数

    QVBoxLayout *vlayout = new QVBoxLayout(centralget); //创建竖直布局
    vlayout->addLayout(hlayout);    //将水平布加入到竖直布局
    vlayout->addWidget(mineView);   //将主视图加入到竖直布局
    this->setCentralWidget(centralget); //将主界面设置应用程序主界面

    mineScene->setSceneRect(0,0,mineScene->m_sceneCol * COMMON::MAPWIDTH,mineScene->m_sceneRow * COMMON::MAPHEIGHT); //设置主场景大小
    mineView->setFixedSize(mineScene->m_sceneCol * COMMON::MAPWIDTH + 5,mineScene->m_sceneRow * COMMON::MAPHEIGHT + 5);//设置主视图大小
    this->setFixedSize(mineScene->m_sceneCol * COMMON::MAPWIDTH + 25,mineScene->m_sceneRow * COMMON::MAPHEIGHT + 75);//设置主窗口大小

    if(mineScene->m_currentLeve == COMMON::LOWLEVE) //判断当前游戏级别
        lowleveaction->setChecked(true);
    else if(mineScene->m_currentLeve == COMMON::MIDDLELEVE)
        midleveaction->setChecked(true);
    else if(mineScene->m_currentLeve == COMMON::HIGHLEVE)
        highleveaction->setChecked(true);
    else if(mineScene->m_currentLeve == COMMON::CUSOMLEVE)
        customaction->setChecked(true);

    this->mineScene->initscene();      //场景初始化

    mineNumLcd->display(mineScene->m_mineSum);  //当前场景雷数显示
//    this->connect(mineView,SIGNAL(sig_resetMineNum(int)),this,SLOT(slot_displayMineNum(int)));

    m_time = 0;
    timeLcd->display(m_time);       //显示用时数码管
    m_timer = new QTimer(this);     //创建定时器对象
    this->connect(m_timer,SIGNAL(timeout()),this,SLOT(slot_displayTime())); //将超时信号连接到显示时间的槽函数
    m_timer->start(1000);           //将计数时间间隔设置为1秒

    if(soundaction->isCheckable()) //判断声音开关
        mineScene->m_soundOpen = true;
    else
        mineScene->m_soundOpen = false;
}


//功能:点击游戏级别行为开始新游戏
void MainWindow::slot_newgamebyleve(QAction *act)
{
    qDebug() << __func__ << endl;
    if(act == lowleveaction)  // 如果是初级行为
    {
        this->mineScene->m_sceneRow = COMMON::LOWROWANDCOL;
        this->mineScene->m_sceneCol = COMMON::LOWROWANDCOL;
        this->mineScene->m_mineSum = COMMON::LOWMINENUM;    //设置场景的行，列，雷数，级别为初级
        this->mineScene->m_currentLeve =  COMMON::LOWLEVE;
    }
    else if(act == midleveaction)//如果是中级行为
    {
        this->mineScene->m_sceneRow = COMMON::MIDDLEROWANDCOL;
        this->mineScene->m_sceneCol = COMMON::MIDDLEROWANDCOL;
        this->mineScene->m_mineSum = COMMON::MIDDLEMINENUM; //设置场景的行，列，雷数，级别为中级
        this->mineScene->m_currentLeve = COMMON::MIDDLELEVE;
    }
    else if(act == highleveaction)//如果是高级级行为
    {
        this->mineScene->m_sceneRow = COMMON::HIGHROW;
        this->mineScene->m_sceneCol = COMMON::HIGHCOL;
        this->mineScene->m_mineSum = COMMON::HIGHMINENUM;   //设置场景的行，列，雷数，级别为高级
        this->mineScene->m_currentLeve = COMMON::HIGHLEVE;
    }
    else if(act == customaction)//如果是自定义行为
    {
        CustomGameDialog *custom = new CustomGameDialog(this); //创建自定义游戏对象
        this->connect(custom,SIGNAL(signal_sendCustomSet(int,int,int)),this,SLOT(slot_acceptCutsomvale(int,int,int)));
            //将自定义对话框的发送数据信号连接到接受自定义游戏数据槽
        custom->exec(); //运行自定义对象
    }
    this->writesettings(); //写入到注册表
    this->slot_newgame();   //开始新游戏
}


//功能:接收自定义游戏设置
void MainWindow::slot_acceptCutsomvale(int row,int col,int count)
{
    qDebug() << __func__ << endl;
    this->mineScene->m_currentLeve = COMMON::CUSOMLEVE;
    this->mineScene->m_sceneRow = row;
    this->mineScene->m_sceneCol = col;
    this->mineScene->m_mineSum = count;
    this->writesettings(); //将自定义数据设置到场景的行，列，雷数，级别，将数据写入到注册表的当前游戏设置中
    this->slot_newgame();   //开始新游戏
}


//功能:设置颜色
void MainWindow::slot_colorchanged()
{
    qDebug() << __func__ << endl;
}


//功能:设置声音
void MainWindow::slot_soundchanged()
{
    qDebug() << __func__ << endl;
    if(soundaction->isCheckable())
    {
        soundaction->setCheckable(false);
        soundaction->setChecked(false);
        this->mineScene->m_soundOpen = false; //关闭场景声音
    }
    else
    {
        soundaction->setCheckable(true);
        soundaction->setChecked(true);
        this->mineScene->m_soundOpen = true;    //打开场景声音
    }
    this->update();
}


//功能:显示排行榜
void MainWindow::slot_herochecked()
{
    qDebug() << __func__ << endl;
    HeroDialog *hero = new HeroDialog(this); //创建排行榜对象
    hero->exec(); //运行排行榜对象，将排行榜显示出来
}


//功能:显示"关于"的消息对话框
void MainWindow::slot_about()
{
    qDebug() << __func__ << endl;
    QString text = tr("应用程序名:排雷行动\n") + tr("  版本: v1.0\n") + tr("  作者:廖铁钢\n") + tr("  日期:2020.08.11\n");
    QMessageBox::about(this,"关于游戏",text); //使用消息框中的about函数创建消息框并显示相关信息
}


//功能:更新排行榜的数据
void MainWindow::slot_updatehero()
{
    qDebug() << __func__ << endl;

    QSettings *settings = new QSettings("HeroData","hero"); //创建注册表对象
    settings->beginGroup("heroRecord");
    int lowTime = settings->value("lowHeroRecord").toInt();
    int midTime = settings->value("midHeroRecord").toInt();
    int highTime = settings->value("highHeroRecord").toInt(); //获取不同级别的时间记录
    settings->endGroup();
    if(mineScene->m_currentLeve == COMMON::LOWLEVE) //判断游戏级别
    {
        if(m_time < lowTime)
        {
            bool ok;
            QString name = QInputDialog::getText(this,"新纪录","请输入您的姓名:",QLineEdit::Normal,"匿 名",&ok); //获取单行文本框输入的内容
            QSettings *settings = new QSettings("HeroData","hero"); //将记录写入排行榜的注册表
            settings->beginGroup("heroRecord");
            settings->setValue("lowHeroRecord",m_time);
            settings->setValue("lowHeroName",name);
            settings->endGroup();
        }
    }
    else if(mineScene->m_currentLeve == COMMON::MIDDLELEVE)
    {
        if(m_time < midTime)
        {
            bool ok;
            QString name = QInputDialog::getText(this,"新纪录","请输入您的姓名:",QLineEdit::Normal,"匿 名",&ok);
            QSettings *settings = new QSettings("HeroData","hero");
            settings->beginGroup("heroRecord");
            settings->setValue("midHeroRecord",m_time);
            settings->setValue("midHeroName",name);
            settings->endGroup();
        }
    }
    else if(mineScene->m_currentLeve == COMMON::HIGHLEVE)
    {
        if(m_time < highTime)
        {
            bool ok;
            QString name = QInputDialog::getText(this,"新纪录","请输入您的姓名:",QLineEdit::Normal,"匿 名",&ok);
            QSettings *settings = new QSettings("HeroData","hero");
            settings->beginGroup("heroRecord");
            settings->setValue("highHeroRecord",m_time);
            settings->setValue("highHeroName",name);
            settings->endGroup();
        }
    }

    QMessageBox mess;   //创建信息对话框，如果没破记录则直接显示该对话框
    mess.setWindowTitle("The Game End");
    mess.setText("恭喜你，游戏通关！是否继续游戏?");
    QPushButton *o_button = mess.addButton("继 续",QMessageBox::ActionRole);
    QPushButton *e_button = mess.addButton("退 出",QMessageBox::ActionRole);
    this->connect(o_button,SIGNAL(clicked(bool)),this,SLOT(slot_newgame())); //开始新游戏
    this->connect(e_button,SIGNAL(clicked(bool)),this,SLOT(close()));
    mess.exec(); //运行该消息对话框

}


//功能:显示雷数
void MainWindow::slot_displayMineNum(int mine)
{
    qDebug() << __func__ << endl;
    int num = mineScene->m_mineSum - mine; //获取右键标记的雷数mine,要显示的雷的数目=当前场景的定义的雷数 - 标记的雷数
    if(num >= 0)
        mineNumLcd->display(num);
}


//功能:显示当前用时
void MainWindow::slot_displayTime()
{
    qDebug() << __func__ << endl;

    if(mineScene->m_isGameOver || mineScene->m_remainNoMines == 0) //判断游戏是否结束，结束则停止计时
    {
        QSettings *setting = new QSettings("MineData","leve");
        setting->beginGroup("currentGame");
        int mine = setting->value("current_mine").toInt();
        setting->endGroup();
        if(mineScene->m_rightMineNum == mine)
            m_timer->stop();
        m_timer->stop();
        return ;
    }
    else
    {
        m_time++;
        timeLcd->display(m_time);  //显示用时
        if(mineScene->m_soundOpen)
            QSound::play("://images/time.wav");
    }
}
