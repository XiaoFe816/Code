#ifndef HERODIALOG_H
#define HERODIALOG_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QDebug>
#include <QMainWindow>
#include <QSettings>
#include <QPushButton>
#include <QGridLayout>

class HeroDialog : public QDialog
{
    Q_OBJECT
public:
    explicit HeroDialog(QWidget *parent = 0);

    QLabel *lowRecordTimeLabel;     //低端局纪录时间标签
    QLabel *midRecordTimeLabel;     //一般局纪录时间标签
    QLabel *highRecordTimeLabel;    //高端局纪录时间标签
    QLabel *time_1;     //低端局纪录时间
    QLabel *time_2;     //一般局纪录时间
    QLabel *time_3;     //高端局录时间
    QLabel *lowRecordNameLabel;     //低端局纪录姓名
    QLabel *midRecordNameLabel;     //一般局纪录姓名
    QLabel *highRecordNameLabel;    //高端局纪录姓名

    //功能:读取注册表的排行榜数据
    //参数:无
    //返回值:无
    void readSettings();


    //功能:初始化排行榜的数据
    //参数:无
    //返回值:无
    void init_heroRecord();

signals:

public slots:
    //功能:重新设置排行榜的数据槽
    //参数:无
    //返回值:无
    void slot_reset();
};

#endif // HERODIALOG_H
