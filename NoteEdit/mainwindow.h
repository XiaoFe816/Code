#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QAction> //动作
#include <QMenu> //主菜单
#include <QMenuBar> //子菜单
#include <QMessageBox> //消息对话框
#include <QDockWidget> //悬浮窗口
#include <QLabel> //标签
#include <QLineEdit> //单行输入框
#include <QStatusBar> //状态栏
#include <QToolBar> //工具栏
#include <QTextEdit> //文本框

#include <QFile> //文件读写
#include <QFileDialog> //文件对话框
#include <QFileInfo> //文件信息

#include "mywidget.h"
#include "centerwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    int fileNums = 0; // 打开的文件数
    CenterWidget *centerWidget; // 中央窗口声明
    QAction *NewFileAction; // 文件相关动作声明
    QAction *OpenFileAction;
    QAction *SaveFileAction;
    QAction *AsSaveFileAction;
    QAction *QuitFileAction;
    QAction *CloseALLFileAction;

    QAction *UndoEditAction; // 编辑相关动作声明
    QAction *RedoEditAction;
    QAction *CutEditAction;
    QAction *PasteEditAction;

    QAction *DockEnableAction; // 其他动作声明
    QAction *AboutAction;
    QAction *HelpAction;

    QLabel *lableStatu; // 标签声明
    QLineEdit *lineEditStatu; // 单行输入框声明

    QString notes; // 文件属性的内容
    QStringList fileList; // 文件列表

    bool dockEnable; // 判断窗口状态
    QDockWidget *dockWidget; // 浮动窗口声明
    MyWidget *myWidget; // 自定义窗口

    void ActionInit(); // 动作初始化
    void ActionConnect(); // 动作连接对应的槽函数
    void AddMyActions(); // 将动作加入到菜单栏中
    void ButtonEnable(); // 按键使能

public slots:
    // 公共的槽函数声明
    void slot_ButtonUp_clicked();
    void slot_ButtonDown_clicked();
    void slot_ButtonLeft_clicked();
    void slot_ButtonRight_clicked();
    void slot_ButtonCloseAll();
    void slot_ButtonOnlyOne();

private slots:
    // 私有的槽函数声明
    void slot_dockWidgetClose(bool);
    void slot_DockWidgetEnable();
    void slot_AboutAction_triggered();
    void slot_HelpAction_triggered();
    void slot_NewFileAction_triggered();
    void slot_OpenFileAction_triggered();
    void slot_SaveFileAction_triggered();
    void slot_AsSaveFileAction_triggered();
    void slot_QuitFileAction_triggered();
    void slot_UndoEditAction_triggered();
    void slot_RedoEditAction_triggered();
    void slot_CutEditAction_triggered();
    void slot_PasteEditAction_triggered();

};

#endif // MAINWINDOW_H
