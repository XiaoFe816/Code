#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("自定义播放器"); //设置程序标题
    this->setWindowIcon(QIcon(":/new/prefix1/QIcon/images/23.ico")); // 设置程序图标

    MediaPlayer = new QMediaPlayer; // 多媒体类申请空间
    MediaPlaylist = new QMediaPlaylist; // 多媒体播放列表申请空间

    MediaPlaylist->setPlaybackMode(QMediaPlaylist::Loop); // 设置播放列表的方式为从头到尾依次播放
    MediaPlayer->setPlaylist(MediaPlaylist); // 将播放列表添加到多媒体对象中
    MediaPlayer->setVolume(ui->horizontalSlider_setSound->value()); // 设置播放音量为水平滑动槽当前的值
    MediaPlayer->setVideoOutput(ui->VideoWidget); // 设置视频播放输出画面到VideoWidget界面中

    // 连接信号槽
    connect(ui->pushButton_add,SIGNAL(clicked(bool)),this,SLOT(slot_buttton_add())); // 添加新文件
    connect(ui->pushButton_del,SIGNAL(clicked(bool)),this,SLOT(slot_buttton_del())); // 移除指定文件
    connect(ui->pushButton_clear,SIGNAL(clicked(bool)),this,SLOT(slot_buttton_clear())); // 清空播放文件列表

    connect(ui->pushButton_play,SIGNAL(clicked(bool)),MediaPlayer,SLOT(play())); // 开始播放
    connect(ui->pushButton_pause,SIGNAL(clicked(bool)),MediaPlayer,SLOT(pause())); // 暂停播放
    connect(ui->pushButton_stop,SIGNAL(clicked(bool)),MediaPlayer,SLOT(stop())); // 终止播放

    connect(ui->pushButton_last,SIGNAL(clicked(bool)),MediaPlaylist,SLOT(previous())); // 切换到当前播放文件上一个文件
    connect(ui->pushButton_next,SIGNAL(clicked(bool)),MediaPlaylist,SLOT(next())); // 切换到当前播放文件下一个文件
    connect(ui->checkBox,SIGNAL(clicked(bool)),MediaPlayer,SLOT(setMuted(bool))); // 选择是否静音

    connect(ui->horizontalSlider_setSound,SIGNAL(valueChanged(int)),MediaPlayer,SLOT(setVolume(int))); // 滑动槽变化设置音量
    connect(MediaPlaylist,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_MediaPlayer_change(int))); // 播放文件显示发送变化

    connect(MediaPlayer,SIGNAL(durationChanged(qint64)),this,SLOT(slot_MediaPlayer_Duration_change(qint64))); // 播放时长发送变化
    connect(MediaPlayer,SIGNAL(positionChanged(qint64)),this,SLOT(slot_MediaPlayer_Postion_change(qint64))); // 播放进度发送变化
    connect(ui->horizontalSlider_pro,SIGNAL(valueChanged(int)),this,SLOT(slot_progress(int))); // 滑动槽位置变化改变播放进度

    connect(ui->listWidget,SIGNAL(currentRowChanged(int)),MediaPlaylist,SLOT(setCurrentIndex(int))); // 改变listWidget的选项时直接改变播放文件

}

// 添加播放文件列表的槽函数
void Widget::slot_buttton_add()
{
    QString files = "音乐文件(*.mp3 *.FLAC *.cda *.wav);;视频文件(*.AVI *.MOV *.mp4);;所有文件(*.*)";
    QStringList fileList;   //获取文件列表
    fileList = QFileDialog::getOpenFileNames(this,"获取播放文件",".",files);

    // 判断是否获取到有效文件
    if(fileList.count() < 1) {
        return ;
    }

    // 有文件则添加进入播放列表中
    for(int i = 0; i < fileList.count() ; i++) {
        QString fileIndex = fileList.at(i); // 获取当前索引
        QFileInfo fileInfo(fileIndex);
        ui->listWidget->addItem(fileInfo.fileName()); // 只将文件名的文本内容添加到listWidget中展示

        QUrl url(fileIndex); // 创建一个超链接对象
        MediaPlaylist->addMedia(QMediaContent(url)); // 将文件名和路径添加到播放列表中
    }

    if(MediaPlayer->state() != QMediaPlayer::PlayingState) {
        MediaPlaylist->setCurrentIndex(0); // 默认播放当前文件列表第一个
        MediaPlayer->play(); // 执行播放
    }
}
#include <QDebug>

// 移除当前播放列表的列表成员的槽函数
void Widget::slot_buttton_del()
{
    int row = ui->listWidget->currentRow(); // 获取当前播放列表所在的行数
    if(row < 0) {
        return ; // 判断是否有没有文件可删，删了个寂寞直接返回
    }

    delete ui->listWidget->takeItem(row); // 移除当前所在的播放展示列表的成员
    MediaPlaylist->removeMedia(row); // 移除当前所在的多媒体播放列表的成员

    if(ui->listWidget->count() == 2)
    {
        MediaPlaylist->setCurrentIndex(0); // 默认播放当前文件列表第一个
        MediaPlayer->play(); // 执行播放
    }

    if((row != 0) && (row <= ui->listWidget->count()))
    {
        MediaPlaylist->setCurrentIndex(row - 1); // 播放删除当前文件的上一个
        MediaPlayer->play(); // 执行播放

        if(row == ui->listWidget->count())
        {
            QString name = ui->listWidget->item(row - 1)->text(); // 获取自动切换播放的文件的名字
            ui->label_name->setText(name); // 设置播放文件名
        }
    }
    if(0 == row)
    {
        MediaPlaylist->setCurrentIndex(0); // 默认播放当前文件列表第一个
        MediaPlayer->play(); // 执行播放
    }
}

// 清空播放列表的槽函数
// 注意：清空播放文件前要先释放多媒体的资源，先清空listWidget会导致播放进度、时长等异常
void Widget::slot_buttton_clear()
{
    MediaPlaylist->clear(); // 多媒体播放列表清空
    ui->listWidget->clear(); // 展示列表清空
    ui->label_name->setText("文件名"); // 设置播放文件名
}

// 播放器多媒体列表切换当前文件的槽函数
/*
 *
 *###Bug：只剩下两个文件待删除的时候，程序会崩溃
 *
 *
 */
void Widget::slot_MediaPlayer_change(int index)
{
    ui->listWidget->setCurrentRow(index);
    QString name = ui->listWidget->item(index)->text(); // 获取要切换播放的文件的名字
    ui->label_name->setText(name); // 设置播放文件名
}

// 播放器播放文件时长变化的槽函数
void Widget::slot_MediaPlayer_Duration_change(qint64 duration)
{
    ui->horizontalSlider_pro->setMaximum(duration); //设置播放进度为指定滑动槽的位置

    int seconds = duration/1000; // 秒钟值显示，播放时间进度以ms为单位
    int points = seconds/60; // 分钟值显示
    seconds %= 60;

    int hours = points/60; //时钟值显示
    points %= 60;
    // 判断时钟值是否大于0，否则不显示
    if(hours > 0)
    {
        total_play_time = QString::number(hours) + ":" + QString::number(points) + ":" + QString::number(seconds);
    }
    else
    {
        total_play_time =QString::number(points) + ":" + QString::number(seconds);
    }
    ui->label_time->setText(play_time + "/" + total_play_time); // 设置播放时长的显示内容
}

// 播放器播放文件进度变化的槽函数
void Widget::slot_MediaPlayer_Postion_change(qint64 postion)
{
    ui->horizontalSlider_pro->setValue(postion); // 设置播放进度为滑块的位置

    int seconds = postion/1000;
    int points = seconds/60;
    seconds %= 60;

    int hours = points/60;
    points %= 60;
    if(hours > 0)
    {
        play_time = QString::number(hours) + ":" + QString::number(points) + ":" + QString::number(seconds);
    }
    else
    {
        play_time =QString::number(points) + ":" + QString::number(seconds);
    }
    ui->label_time->setText(play_time + "/" + total_play_time);
}

// 播放进度随滑槽位置变化二变化的槽函数
void Widget::slot_progress(int value)
{
    if(ui->horizontalSlider_pro->isSliderDown() == true) // 判断滑槽位置是否被鼠标改变
    {
        MediaPlayer->setPosition(value); // 设置播放进度为滑块的位置
    }
}

Widget::~Widget()
{
    delete ui;
}
