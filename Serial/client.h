#ifndef CLIENT_H
#define CLIENT_H

#include <QWidget>
#include <QTcpServer> //TCP服务器
#include <QTcpSocket> //TCP套接字
#include <QTextCodec> //编码格式转换
#include <QHostAddress> //本地字节序转换


namespace Ui {
class Client;
}

class Client : public QWidget
{
    Q_OBJECT
public:
    explicit Client(QWidget *parent = 0);
    ~Client();

    QTcpSocket *TcpSocket; //声明TCP套接字对象

private:
    Ui::Client *ui;

signals:

public slots:
    void slot_tcp_connect(); //客户端登录服务器验证的槽函数
    void slot_tcp_disconnect(); //客户端断开与服务器的连接的槽函数
    void slot_tcp_clearSend(); //清空发送信息的槽函数
    void slot_tcp_clearRead(); //清空接收信息的槽函数
    void slot_tcp_send(); //发送信息的槽函数

    void slot_TcpSocket_read(); //服务器套接字处理数据的槽函数
    void slot_TcpSocket_connect(); //客户端套接字连接成功后的槽函数
};

#endif // CLIENT_H
