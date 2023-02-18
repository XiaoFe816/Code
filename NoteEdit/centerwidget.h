#ifndef CENTERWIDGET_H
#define CENTERWIDGET_H

#include <QWidget>
#include <QTableWidget> // 标签式窗口
#include <QTextEdit> // 单行输入框
#include <QVBoxLayout> // 竖直布局
#include <QFile> // 文件
#include <QFileInfo> // 文件信息

class CenterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CenterWidget(QWidget *parent = 0);
    QTabWidget *tabWidget; // 标签式窗口声明
    void addTextEdit(QString fileName); // 执行新建窗口并命名

signals:

public slots:
};

#endif // CENTERWIDGET_H
