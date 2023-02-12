#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("串口通讯&TCP服务器");

    //串口是否打开标志位
    is_open = false;
    //客户端是否连接标志位
    is_link = false;

    //串口对象申请空间
    SerialPort = new QSerialPort;
    //Tcp服务器申请空间
    TcpServer = new QTcpServer;
    //遍历本地的有效串口端口号
    QList<QSerialPortInfo> SerialPortInfoList = QSerialPortInfo::availablePorts();
    for(int i=0 ; i<SerialPortInfoList.count() ; i++)
    {
        //获取本地的串口号
        QSerialPortInfo SerialPortInfo = SerialPortInfoList.at(i);
        QString name = SerialPortInfo.portName();
        //将有效的串口号加入到复选栏组件中去
        ui->comboBox_port->addItem(name);
    }

    //Tcp绑定IP地址和端口号的按钮处理
    connect(ui->pushButton_bind,SIGNAL(clicked(bool)),this,SLOT(slot_button_bind()));
    //串口连接
    connect(ui->pushButton_connect,SIGNAL(clicked(bool)),this,SLOT(slot_button_openPort()));
    //发送数据
    connect(ui->pushButton_send,SIGNAL(clicked(bool)),this,SLOT(slot_button_send()));
    //串口接收讯息后
    connect(SerialPort,SIGNAL(readyRead()),this,SLOT(slot_SerialPort_read()));
    //清空发送信息
    connect(ui->pushButton_clearSend,SIGNAL(clicked(bool)),this,SLOT(slot_button_clearSend()));
    //清空接收信息
    connect(ui->pushButton_clearRead,SIGNAL(clicked(bool)),this,SLOT(slot_button_clearRead()));
}

void Widget::slot_button_bind()
{
    //字符转数字判断标志位
    bool ok = false;
    //获取填写的IP和端口号
    QString ip = ui->lineEdit_ip->text();
    //&OK判断填写的端口号是否可用，已被占用则ok为false，端口号可用ok则为true
    int port = ui->lineEdit_port->text().toInt(&ok);
    if(ok == true && ip.isEmpty() == false)
    {
        //绑定并监听
        if((TcpServer->listen(QHostAddress(ip),port) == true))
        {
            //客户端连接成功TCP连接标志位为真
            is_link = true;
            //绑定按钮置灰，避免重复绑定
            ui->pushButton_bind->setEnabled(false);
            //服务器有新的客户端连接后进行处理的槽函数
            connect(TcpServer,SIGNAL(newConnection()),this,SLOT(slot_tcp_newConncet()));
        }
    }
}

void Widget::slot_tcp_newConncet()
{
    //将挂起的客户端连接的套接字获取
    TcpSocket = TcpServer->nextPendingConnection();
    //将挂起的客户端的套接字数据的对应的信号连接到槽函数
    connect(TcpSocket,SIGNAL(readyRead()),this,SLOT(slot_tcp_readReady()));
}

void Widget::slot_tcp_readReady()
{
    //通过套接字获取客户端发来的信息
    QByteArray ReadBuf = TcpSocket->readAll();
    //获取转换格式
    QTextCodec *TextCodec = QTextCodec::codecForName(ui->comboBox_read->currentText().toUtf8());
    //再次转换信息格式为指定的格式
    QString readData = TextCodec->toUnicode(ReadBuf);
    //追加显示信息内容
    ui->textEdit_read->append(readData);
}

void Widget::slot_SerialPort_read()
{
    //获取串口接收的字节数据
    QByteArray ReadBuf = SerialPort->readAll();
    //获取转换格式
    QTextCodec *TextCodec = QTextCodec::codecForName(ui->comboBox_read->currentText().toUtf8());
    //将字节数据转换为字符串格式
    QString readData = TextCodec->toUnicode(ReadBuf);
    //追加显示转换后的信息
    ui->textEdit_read->append(readData);
}

void Widget::slot_button_clearSend()
{
    //清空要发送消息的数据
    ui->lineEdit_send->clear();
}

void Widget::slot_button_clearRead()
{
    //清空接收到的数据
    ui->textEdit_read->clear();
}

void Widget::slot_button_send()
{
    //串口连接并打开后发送数据
    if(is_open == true)
    {
        //获取要发送的信息的内容
        QString sendData = ui->lineEdit_send->text();
        //获取转换发送信息的格式
        QTextCodec *TextCodec = QTextCodec::codecForName(ui->comboBox_send->currentText().toUtf8());
        //再次转换发送信息的格式
        QByteArray sendbuf = TextCodec->fromUnicode(sendData.toUtf8());
        //在串口端发送信息
        SerialPort->write(sendbuf);
        //清空信息发送栏
        ui->lineEdit_send->clear();
    }

    //客户端连接成功后发送数据
    if(is_link == true)
    {
        //获取要发送的信息的内容
        QString sendData = ui->lineEdit_send->text();
        //获取转换发送信息的格式
        QTextCodec *TextCodec = QTextCodec::codecForName(ui->comboBox_send->currentText().toUtf8());
        //再次转换发送信息的格式
        QByteArray sendbuf = TextCodec->fromUnicode(sendData.toUtf8());
        //在服务器端发送信息
        TcpSocket->write(sendbuf);
        //清空信息发送栏
        ui->lineEdit_send->clear();
    }
}

void Widget::slot_button_openPort()
{
    //判断连接的串口是否有效
    if(ui->pushButton_connect->text() == "打开串口")
    {
        //获取串口号
        QString PortName = ui->comboBox_port ->currentText();
        //设置端口号
        SerialPort->setPortName(PortName);

        //获取波特率
        QSerialPort::BaudRate baudRate;
        //选择波特率
        switch(ui->comboBox_baud->currentIndex())
        {
            case 0: baudRate = QSerialPort::Baud9600; break;
            case 1: baudRate = QSerialPort::Baud4800; break;
            case 2: baudRate = QSerialPort::Baud19200; break;
            case 3: baudRate = QSerialPort::Baud115200; break;
        }
        //设置波特率
        SerialPort->setBaudRate(baudRate);

        //获取数据位
        QSerialPort::DataBits dataBits;
        //选择数据位
        switch(ui->comboBox_data->currentIndex())
        {
            case 0: dataBits = QSerialPort::Data8; break;
            case 1: dataBits = QSerialPort::Data5; break;
            case 2: dataBits = QSerialPort::Data6; break;
            case 3: dataBits = QSerialPort::Data7; break;
        }
        //设置数据位
        SerialPort->setDataBits(dataBits);

        //获取校验位
        QSerialPort::Parity parity;
        //选择校验模式
        switch(ui->comboBox_check->currentIndex())
        {
            case 0: parity = QSerialPort::NoParity; break;
            case 1: parity = QSerialPort::EvenParity; break;
            case 2: parity = QSerialPort::OddParity; break;
            case 3: parity = QSerialPort::SpaceParity; break;
            case 4: parity = QSerialPort::MarkParity; break;
        }
        //设置校验模式
        SerialPort->setParity(parity);

        //获取停止位
        QSerialPort::StopBits stopBits;
        //选择停止位
        switch(ui->comboBox_stop->currentIndex())
        {
            case 0: stopBits = QSerialPort::OneStop; break;
            case 1: stopBits = QSerialPort::TwoStop; break;
            case 2: stopBits = QSerialPort::OneAndHalfStop; break;
        }
        //设置停止位
        SerialPort->setStopBits(stopBits);

        //串口设备打开
        if(SerialPort->open(QIODevice::ReadWrite) == true)
        {
            //将串口连接按钮改为关闭，表示再次点击此按钮断开连接
            ui->pushButton_connect->setText("关闭串口");
            //串口打开成功
            is_open = true;
            //发送指定信息表示串口正常使用
            SerialPort->write("2020-2021");
        }
    }
    else
    {
        //串口打开失败
        is_open = false;
        //串口关闭
        SerialPort->close();
        //如串口不小心断开，及时改变按钮提示信息
        ui->pushButton_connect->setText("打开串口");
    }
}

Widget::~Widget()
{
    delete ui;
}

