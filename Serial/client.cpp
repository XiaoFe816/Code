#include "client.h"
#include "ui_client.h"

Client::Client(QWidget *parent) :
    QWidget(parent) ,
    ui(new Ui::Client)
{
    ui->setupUi(this);
    //修改界面标题
    this->setWindowTitle("TCP客户端");

    //客户端套接字对象申请空间
    TcpSocket = new QTcpSocket;
    //连接服务器的登录验证
    connect(ui->pushButton_link,  SIGNAL(clicked(bool)),  this,  SLOT(slot_tcp_connect()));
    //断开连接后的处理
    connect(ui->pushButton_disconnect,  SIGNAL(clicked(bool)),  this,  SLOT(slot_tcp_disconnect()));
    //发送信息给服务器
    connect(ui->pushButton_send,  SIGNAL(clicked(bool)),  this,  SLOT(slot_tcp_send()));
    //清空未发出的信息
    connect(ui->pushButton_clear,  SIGNAL(clicked(bool)),  this,  SLOT(slot_tcp_clearSend()));
    //清空接收到的信息
    connect(ui->pushButton_clearRead,  SIGNAL(clicked(bool)),  this,  SLOT(slot_tcp_clearRead()));
}

void Client:: slot_tcp_connect()
{
    //端口号有效标志位初始化
    bool ok = false;
    //获取填写的IP和端口号的内容
    QString ip = ui->lineEdit_ip->text();
    int port = ui->lineEdit_port->text().toInt(&ok);
    //判断IP和端口号是否有效
    if (ok == true && ip.isEmpty() == false) {
        //连接服务器
        TcpSocket->connectToHost(QHostAddress(ip), port);
        //连接成功后处理
        connect(TcpSocket, SIGNAL(connected()), this, SLOT(slot_TcpSocket_connect()));
        //断开连接后的处理
        connect(TcpSocket, SIGNAL(disconnected()), this, SLOT(slot_tcp_disconnect()));
        //客户端套接字接收信息后的处理
        connect(TcpSocket, SIGNAL(readyRead()), this, SLOT(slot_TcpSocket_read()));
    } else {
        //断开连接
        TcpSocket->disconnectFromHost();
    }
}

void Client:: slot_tcp_disconnect()
{
    //断开连接
    TcpSocket->disconnectFromHost();
    //断开按钮置灰
    ui->pushButton_disconnect->setEnabled(false);
    //显示连接按钮
    ui->pushButton_link->setEnabled(true);
}

void Client::slot_tcp_clearSend()
{
    //清空未发出的信息
    ui->lineEdit_send->clear();
}

void Client::slot_tcp_clearRead()
{
    //清空接收的信息
    ui->textEdit->clear();
}

void Client:: slot_tcp_send()
{
    //获取发送信息的内容
    QString sendBuf = ui->lineEdit_send->text();
    //获取转换格式
    QTextCodec *TextCodec = QTextCodec::codecForName(ui->comboBox_send->currentText().toUtf8());
    //再次转换为所需要的格式
    QByteArray sendData = TextCodec->fromUnicode(sendBuf.toUtf8());
    //套接字发送数据
    TcpSocket->write(sendData);
    //清空发送栏
    ui->lineEdit_send->clear();
}


void Client:: slot_TcpSocket_read()
{
    //获取接收信息
    QByteArray readBuf = TcpSocket->readAll();
    //获取转换格式
    QTextCodec *TextCodec = QTextCodec::codecForName(ui->comboBox_read->currentText().toUtf8());
    //再次转换为所需要的格式
    QString readData = TextCodec->toUnicode(readBuf);
    //追加显示接收的信息
    ui->textEdit->append(readData);
}

void Client::slot_TcpSocket_connect()
{
    //连接按钮置灰
    ui->pushButton_link->setEnabled(false);
    //显示断开连接的按钮
    ui->pushButton_disconnect->setEnabled(true);
    //显示发送信息的按钮
    ui->pushButton_send->setEnabled(true);
}

Client::~Client()
{
    delete ui;
}
