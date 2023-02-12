#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QMouseEvent>
#include <QKeyEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private:
    Ui::Widget *ui;
    QMediaPlayer *MediaPlayer;
    QMediaPlaylist *MediaPlaylist;

    QString play_time;
    QString total_play_time;

public slots:
    void slot_buttton_add();
    void slot_buttton_del();
    void slot_buttton_clear();

    void slot_MediaPlayer_change(int index);

    void slot_MediaPlayer_Duration_change(qint64 duration);
    void slot_MediaPlayer_Postion_change(qint64 postion);
    void slot_progress(int value);

};

#endif // WIDGET_H
