#pragma once

#include <QUrl>
#include <QTcpSocket>

#include "socketinfo.h"

namespace Connection {

class ITcpSocket : public QObject
{
    Q_OBJECT

public:
    virtual void readyRead() = 0;
    virtual void disconnect() = 0;
    virtual void connectToHost(const QUrl url) = 0;

    virtual void send(QByteArray header, QByteArray msg) = 0;

    virtual QAbstractSocket::SocketState state() = 0;

    virtual bool isConnected() = 0;

signals:
    void dataRecevied(Packet);
    void stateChanged();
    void errorOccured(QAbstractSocket::SocketError);
};

}
