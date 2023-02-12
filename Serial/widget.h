#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort> //串口对象遇到的头文件
#include <QSerialPortInfo> //串口信息
#include <QTextCodec> //编码格式转换

#include <QTcpServer> //TCP服务器
#include <QTcpSocket> //TCP套接字
#include <QHostAddress> //本地字节序转换

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
    QSerialPort *SerialPort; //声明串口对象
    bool is_open; //声明串口连接状态标志位
    bool is_link; //声明客户端连接状态标志位

    QTcpServer *TcpServer; //声明TCP服务器对象
    QTcpSocket *TcpSocket;//声明TCP套接字对象

public slots:
    void slot_button_openPort(); //打开串口的槽函数
    void slot_button_send(); //发送信息的槽函数
    void slot_SerialPort_read(); //串口接收信息的槽函数
    void slot_button_clearSend(); //清空发送数据的槽函数
    void slot_button_clearRead(); //清空接收数据的槽函数

    void slot_button_bind(); //绑定IP和端口号的槽函数
    void slot_tcp_newConncet(); //客户端连接的槽函数
    void slot_tcp_readReady(); //客户端套接字处理数据的槽函数
};

#endif // WIDGET_H
