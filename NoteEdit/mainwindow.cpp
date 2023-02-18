#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setMinimumSize(1000, 700);
    this->setWindowTitle("Fe编辑器");
    this->setWindowIcon(QIcon(":/image/image/头像 (12).ico")); // 程序图标
    notes = "普通文件(*.txt);;C语言 (*.c);;C++(*cpp);;头文件(*.h);;ALL(*.*)"; //文件格式
    dockEnable = true;

    dockWidget = new QDockWidget("导航窗口"); // 浮动窗口申请空间
    dockEnable = dockWidget->isHidden(); // 获取当前窗口状态
    //qDebug() << "浮动窗口：" << dockEnable << endl;
    // 浮动窗口加入到主窗口来并限制附着区域
    this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);

    myWidget = new MyWidget; // 为自定义窗口申请空间
    dockWidget->setWidget(myWidget); // 设置浮动窗口为自定义的界面

    centerWidget = new CenterWidget; // 为中央窗口申请空间
    this->setCentralWidget(centerWidget); // 设置程序的中央窗口

    QStatusBar *StatusBar = statusBar(); // 获取当前窗口状态
    lableStatu = new QLabel("状态栏：");
    lineEditStatu = new QLineEdit("随便");
    StatusBar->addWidget(lableStatu); // 将标签加入状态栏
    StatusBar->addWidget(lineEditStatu, 1); // 将单行文本框加入状态栏

    ActionInit(); //各动作初始化
    AddMyActions(); //各菜单栏配置对应的动作
    ActionConnect(); //将动作连接到槽函数
    ButtonEnable(); // 部分按键初始化，避免程序崩溃

    // 根据浮动窗口的状态连接到槽函数
    connect(dockWidget, SIGNAL(visibilityChanged(bool)), this, SLOT(slot_dockWidgetClose(bool)));
    // 根据浮动窗口上的按钮连接到对应的槽函数
    connect(myWidget->buttonLeft, SIGNAL(clicked(bool)), this, SLOT(slot_ButtonLeft_clicked()));
    connect(myWidget->buttonRight, SIGNAL(clicked(bool)), this, SLOT(slot_ButtonRight_clicked()));
    connect(myWidget->buttonCloseAll, SIGNAL(clicked(bool)), this, SLOT(slot_ButtonCloseAll()));
    connect(myWidget->buttonCloseCur, SIGNAL(clicked(bool)), this, SLOT(slot_QuitFileAction_triggered()));
    connect(myWidget->buttonOnlyCur, SIGNAL(clicked(bool)), this, SLOT(slot_ButtonOnlyOne()));
}

// 析构函数
MainWindow::~MainWindow()
{
}

void MainWindow:: slot_dockWidgetClose(bool temp)
{
    // 窗口刚创建时也会连接该槽函数，默认temp为true，后面再关闭或展开窗口都不影响该标志位
    static bool checked = temp;
    // 设置是否选中窗口可视化动作
    DockEnableAction->setChecked(checked);
    // 获取浮动窗口的显示状态（隐藏或展开）
    dockEnable = dockWidget->isVisible();
    // 窗口状态标志位取反，同步可视化操作
    checked = ! checked;
}

void MainWindow:: slot_DockWidgetEnable()
{
    dockEnable = dockWidget->isVisible(); // 获取浮动窗口的显示状态（隐藏或展开）

    if (dockEnable) { // 根据浮动窗口的状态来配置可选操作
        DockEnableAction->setChecked(false);
        dockWidget->setHidden(true);
    } else {
        DockEnableAction->setChecked(true);
        dockWidget->setHidden(false);
        //this->addDockWidget(Qt::LeftDockWidgetArea, dockWidget);
    }

    dockEnable = !dockEnable; // 窗口状态标志位取反，同步可视化操作
}

void MainWindow::ActionInit()
{
    NewFileAction = new QAction(QIcon(":/image/image/08_新建文件.png"), "新建", this);
    OpenFileAction = new QAction(QIcon(":/image/image/03_打开文件.png"), "打开", this);
    AsSaveFileAction = new QAction(QIcon(":/image/image/11_白帽图标.ico"), "另存为", this);
    SaveFileAction = new QAction(QIcon(":/image/image/07_保存文件.png"), "保存", this);
    QuitFileAction = new QAction(QIcon(":/image/image/11_关闭文件.png"), "退出", this);
    CloseALLFileAction = new QAction("关闭所有文件", this);

    UndoEditAction = new QAction(QIcon(":/image/image/02_撤销.png"), "撤销", this);
    RedoEditAction = new QAction(QIcon(":/image/image/12_复原.png"), "恢复", this);
    CutEditAction = new QAction(QIcon(":/image/image/05_剪切.png"), "剪切", this);
    PasteEditAction = new QAction(QIcon(":/image/image/01_粘贴.png"), "粘贴", this);

    DockEnableAction = new QAction("导航窗口", this);
    DockEnableAction->setCheckable(true);
    DockEnableAction->setChecked(true);
    AboutAction = new QAction("关于", this);
    HelpAction = new QAction(QIcon(":/image/image/09_三点.png"), "帮助", this);
}

void MainWindow::AddMyActions()
{
    QMenuBar *menuBarPtr;
    menuBarPtr = this->menuBar();

    // 添加‘文件’的栏目到菜单栏中
    QMenu *menuFile = menuBarPtr->addMenu("文件");
    menuFile->addAction(NewFileAction);
    menuFile->addAction(OpenFileAction);
    menuFile->addAction(SaveFileAction);
    menuFile->addSeparator();
    menuFile->addAction(QuitFileAction);
    menuFile->addAction(CloseALLFileAction);

    // 添加‘编辑’的栏目到菜单栏中
    QMenu *menuEdit = menuBarPtr->addMenu("编辑");
    menuEdit->addAction(UndoEditAction);
    menuEdit->addAction(RedoEditAction);
    menuEdit->addSeparator();
    menuEdit->addAction(CutEditAction);
    menuEdit->addAction(PasteEditAction);

    // 添加‘帮助’的栏目到菜单栏中
    QMenu *menuHelp = menuBarPtr->addMenu("帮助");
    menuHelp->addAction(DockEnableAction);
    menuEdit->addSeparator();
    menuHelp->addAction(AboutAction);
    menuHelp->addAction(HelpAction);

    // 添加‘文件’的工具栏
    QToolBar *fileToolBar = addToolBar("文件");
    fileToolBar->addAction(NewFileAction);
    fileToolBar->addAction(OpenFileAction);
    fileToolBar->addAction(SaveFileAction);
    fileToolBar->addSeparator();
    fileToolBar->addAction(QuitFileAction);

    // 添加‘编辑’的工具栏
    QToolBar *editToolBar = addToolBar("编辑");
    addToolBar(Qt::RightToolBarArea, editToolBar);
    editToolBar->addAction(UndoEditAction);
    editToolBar->addAction(RedoEditAction);
    editToolBar->addSeparator();
    editToolBar->addAction(CutEditAction);
    editToolBar->addAction(PasteEditAction);
    editToolBar->addSeparator();
}

// 各动作连接对应的槽函数
void MainWindow::ActionConnect()
{
    connect(DockEnableAction, SIGNAL(triggered(bool)), this, SLOT(slot_DockWidgetEnable()));
    connect(AboutAction, SIGNAL(triggered(bool)), this, SLOT(slot_AboutAction_triggered()));
    connect(HelpAction, SIGNAL(triggered(bool)), this, SLOT(slot_HelpAction_triggered()));
    connect(NewFileAction, SIGNAL(triggered(bool)), this, SLOT(slot_NewFileAction_triggered()));
    connect(OpenFileAction, SIGNAL(triggered(bool)), this, SLOT(slot_OpenFileAction_triggered()));
    connect(SaveFileAction, SIGNAL(triggered(bool)), this, SLOT(slot_SaveFileAction_triggered()));
    connect(QuitFileAction, SIGNAL(triggered(bool)), this, SLOT(slot_QuitFileAction_triggered()));
    connect(CloseALLFileAction, SIGNAL(triggered(bool)), this, SLOT(slot_ButtonCloseAll()));
    connect(UndoEditAction, SIGNAL(triggered(bool)), this, SLOT(slot_UndoEditAction_triggered()));
    connect(RedoEditAction, SIGNAL(triggered(bool)), this, SLOT(slot_RedoEditAction_triggered()));
    connect(CutEditAction, SIGNAL(triggered(bool)), this, SLOT(slot_CutEditAction_triggered()));
    connect(PasteEditAction, SIGNAL(triggered(bool)), this, SLOT(slot_PasteEditAction_triggered()));
}

// 按键使能的槽函数，避免在没有文件的情况下按下按键导致程序崩溃
void MainWindow::ButtonEnable()
{
    // 判断当前是有文件，有文件则部分按键功能正常，否则使按键置灰
    if (!fileNums) {
        myWidget->buttonCloseCur->setEnabled(false);
        myWidget->buttonOnlyCur->setEnabled(false);
        myWidget->buttonCloseAll->setEnabled(false);
    } else {
        myWidget->buttonCloseCur->setEnabled(true);
        myWidget->buttonOnlyCur->setEnabled(true);
        myWidget->buttonCloseAll->setEnabled(true);
    }
}

// ‘关于’动作的槽函数
void MainWindow::slot_AboutAction_triggered()
{
    QMessageBox::about(this, "Fe的编辑器", "这是由昵称为Fe的帅哥自制的文本编辑器");
}

// ‘帮助’动作的槽函数
void MainWindow::slot_HelpAction_triggered()
{
    QMessageBox::about(this, "此软件的版本", "作者：Fe\nVersion: V1.0\n开发平台：Qt5.8\n设计语言：C++");
}

// 新建文件的槽函数
void MainWindow::slot_NewFileAction_triggered()
{
    // 获取新建文件的路径及名字
    QString files =  QFileDialog::getSaveFileName(this, "新建", ".", notes);
    if (files.isEmpty() == false) { // 判断创建文件是否成功
        centerWidget->addTextEdit(files); // 将创建的文件加入到标签窗口中
        fileList.insert(fileList.count(), files); // 将创建的文件加入到文件列表中
        fileNums++;
    }

    ButtonEnable();
}

// 打开文件的槽函数
void MainWindow::slot_OpenFileAction_triggered()
{
    // 获取当前操作打开的文件列表
    fileList =  QFileDialog::getOpenFileNames(this, "获取打开文件", ".", notes);
    if (fileList.count() < 1) {
        qDebug() << "文件打开错误\n" << endl;
        return;
    }

    //文件列表遍历加入到标签窗口
    for (int i = 0; i < fileList.count(); i++) {
        QString index = fileList.at(i);
        centerWidget->addTextEdit(index);
    }

    // 同步当前打开的文件数
    fileNums += fileList.count();
    ButtonEnable();
}

// 保存文件的槽函数
void MainWindow::slot_SaveFileAction_triggered()
{
    // 获取当前标签窗口位置的索引值
    int index = centerWidget->tabWidget->currentIndex();
    // 获取当前标签窗口位置的文件名及路径
    QString curFile = fileList.at(index);
    qDebug() << "保存文件路径：" << curFile << endl;

    // 获取当前标签窗口的信息
    QTextEdit *textBuf = (QTextEdit *)this->centerWidget->tabWidget->currentWidget();
    QString txtSave = textBuf->toPlainText();

    // 保存当前窗口文本框里的内容
     QFile file(curFile);
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
         return;
     }
     //qDebug() << txtSave << endl;
     file.write(txtSave.toUtf8());
     file.close();
}

// 另存为文件的槽函数
void MainWindow::slot_AsSaveFileAction_triggered()
{
    // 获取当前标签窗口位置的文件名及路径
    QString curFile = QFileDialog::getSaveFileName(this);
    if (curFile.isEmpty() == true) {
        return;
    }

    // 获取当前标签窗口的信息
    QTextEdit *textBuf = (QTextEdit *)this->centerWidget->tabWidget->currentWidget();
    QString txtSave = textBuf->toPlainText();

    // 将当前文件另存至指定路径
     QFile file(curFile);
     if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
         return;
     }
     //qDebug() << txtSave << endl;
     file.write(txtSave.toUtf8());
     file.close();
}

// 关闭当前文件动作的槽函数
void MainWindow::slot_QuitFileAction_triggered()
{
    /*
    QTextEdit *textBuf = (QTextEdit *)this->centerWidget->tabWidget->currentWidget();
    textBuf->clear();
    */

    // 获取当前标签窗口位置的索引值
    int index = centerWidget->tabWidget->currentIndex();
    // 关闭指定的标签窗口
    centerWidget->tabWidget->removeTab(index);
    fileNums--;
    ButtonEnable();
}

// 撤销功能的槽函数
void MainWindow::slot_UndoEditAction_triggered()
{
    QTextEdit *textEdit= (QTextEdit *)this->centerWidget->tabWidget->currentWidget();
    textEdit->undo();
}

// 复原上一步功能的槽函数
void MainWindow::slot_RedoEditAction_triggered()
{
    QTextEdit *textEdit= (QTextEdit *)this->centerWidget->tabWidget->currentWidget();
    textEdit->redo();
}

// 剪切功能的槽函数
void MainWindow::slot_CutEditAction_triggered()
{
    QTextEdit *textEdit= (QTextEdit *)this->centerWidget->tabWidget->currentWidget();
    textEdit->cut();
}

// 粘贴功能的槽函数
void MainWindow::slot_PasteEditAction_triggered()
{
    QTextEdit *textEdit= (QTextEdit *)this->centerWidget->tabWidget->currentWidget();
    textEdit->paste();
}

// 标签窗口移动到头部的槽函数
void MainWindow:: slot_ButtonUp_clicked()
{
    centerWidget->tabWidget->setCurrentIndex(0);
}

// 标签窗口移动到尾部的槽函数
void MainWindow:: slot_ButtonDown_clicked()
{
    centerWidget->tabWidget->setCurrentIndex(fileNums - 1);
}

// 标签窗口左移的槽函数
void MainWindow:: slot_ButtonLeft_clicked()
{
    int index = centerWidget->tabWidget->currentIndex();
    // 判断当前位置是否在头部，处于头部位置则下次移动至尾部
    if (!index) {
        centerWidget->tabWidget->setCurrentIndex(fileNums - 1);
    } else {
        centerWidget->tabWidget->setCurrentIndex(index - 1);
    }
}

// 标签窗口左移的槽函数
void MainWindow:: slot_ButtonRight_clicked()
{
    int index = centerWidget->tabWidget->currentIndex();
    // 判断当前位置是否在尾部，处于头部位置则下次移动至头部
    if (index == fileNums - 1) {
        centerWidget->tabWidget->setCurrentIndex(0);
    } else {
        centerWidget->tabWidget->setCurrentIndex(index + 1);
    }
}

// 关闭其他标签窗口只保留当前窗口的槽函数
void MainWindow::slot_ButtonOnlyOne()
{
    int index = centerWidget->tabWidget->currentIndex();
    qDebug() << "只保留的文件的索引值：" << index << endl;
    qDebug() << "当前打开的文件数：" << fileNums << endl;

    /*//BUG:无法只保留指定的文件
    //qDebug() << "剩余文件的数量：" << Num<< endl;
    for (int i = 0; i < fileNums; i++) {
        if  (i == index) {
            continue;
        }
        centerWidget->tabWidget->removeTab(i);
    } */

    // 获取当前窗口的全部信息
    QTextEdit *textBuf = (QTextEdit *)this->centerWidget->tabWidget->currentWidget();
    QString dataBuf = textBuf->toPlainText();

    // 先关闭所有窗口，保存当前窗口文件的内容后再重新打开
    for (QList<QString>::iterator it = fileList.begin(); it != fileList.end(); it++) {
        if  (*it == fileList.at(index)) {
            qDebug() << *it << endl;
            centerWidget->tabWidget->clear();

            QFile file(*it);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                return;
            }

            file.write(dataBuf.toUtf8());
            file.close();
            centerWidget->addTextEdit(*it);
            fileNums = 1;
            break;
        }
    }
}

// 关闭所有标签窗口的槽函数
void MainWindow::slot_ButtonCloseAll()
{
    centerWidget->tabWidget->clear();
    fileNums = 0;
    ButtonEnable();
}
