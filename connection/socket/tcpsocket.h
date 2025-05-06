#pragma once

#include <QObject>

#include "itcpsocket.h"
#include "socketinfo.h"

namespace Connection {

class TcpSocket : public ITcpSocket
{
    Q_OBJECT

public:
    TcpSocket();

    void readyRead() override;
    void disconnect() override;
    void connectToHost(const QUrl url) override;

    void send(QByteArray header, QByteArray msg) override;

    bool isConnected() override;
    QAbstractSocket::SocketState state() override;

private:
    QUrl m_url;
    QTcpSocket m_socket;

    Header deserializeHeader(QByteArray& data);

    void stateChanged(QAbstractSocket::SocketState);
};

}
