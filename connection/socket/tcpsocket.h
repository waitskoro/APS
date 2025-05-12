#pragma once

#include <QUrl>
#include <QObject>
#include <QTcpSocket>

#include "socketinfo.h"

namespace Connection {

class TcpSocket : public QObject
{
    Q_OBJECT

public:
    explicit TcpSocket(QObject *parent = nullptr);

    void readyRead();
    void disconnect();
    void connectToHost(const QUrl url);

    void send(QByteArray header, QByteArray msg);

    bool isConnected();
    QAbstractSocket::SocketState state();

signals:
    void stateChanged();
    void dataRecevied(Packet);
    void errorOccured(QAbstractSocket::SocketError);

private:
    QUrl m_url;
    QTcpSocket m_socket;

    Header deserializeHeader(QByteArray& data);

    void stateChanged(QAbstractSocket::SocketState);
};

}
