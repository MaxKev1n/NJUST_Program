#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <headers.h>

class TCPServer : public QMainWindow
{
    Q_OBJECT

public:
    explicit TCPServer(QWidget *parent = nullptr);

private slots:
    void slot_newconnect(); //建立新连接的槽
    //void slot_sendmessage(); //发送消息的槽
    //void slot_recvmessage(); //接收消息的槽
    //void slot_disconnect(); //取消连接的槽

private:

    QTcpServer *TCPserver; //QTcpServer服务器
    QTcpSocket *TCPconnectSocket; //与客户端连接套接字

public:

    QTextBrowser *display;

};
#endif // TCPSERVER_H
