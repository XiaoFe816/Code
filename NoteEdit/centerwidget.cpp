#include "centerwidget.h"

CenterWidget::CenterWidget(QWidget *parent) : QWidget(parent)
{
    // 申请空间
    tabWidget = new QTabWidget;
    // 设置竖直布局
    QVBoxLayout *vbox_1 = new QVBoxLayout;
    vbox_1->addWidget(tabWidget);
    this->setLayout(vbox_1);
}

void CenterWidget::addTextEdit(QString fileName)
{
    // 创建文本框并命名
    QTextEdit *textEdit = new QTextEdit;
    tabWidget->addTab(textEdit, QFileInfo(fileName).fileName());

    //  设置新增文件的打开方式，读写模式+普通文本模式
    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        return;
    }

    // 同步文本框与文件的内容
    textEdit->setText(file.readAll());
    file.close();
}
