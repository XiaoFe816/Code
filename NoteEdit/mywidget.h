#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QLabel> // 标签
#include <QPushButton> // 按键
#include <QGridLayout> // 网格布局
#include <QVBoxLayout> // 竖直布局

#include "centerwidget.h"

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);
    // 标签声明
    QLabel *lableUp;
    QLabel *lableDown;
    QLabel *lableLeft;
    QLabel *lableRight;

    // 按键声明
    QPushButton *buttonUp;
    QPushButton *buttonDown;
    QPushButton *buttonLeft;
    QPushButton *buttonRight;
    QPushButton *buttonCloseCur;
    QPushButton *buttonOnlyCur;
    QPushButton *buttonCloseAll;

signals:

public slots:
};

#endif // MYWIDGET_H
