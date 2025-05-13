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

    void connectToHost(const QUrl& url);
    void disconnectFromHost();
    void send(const QByteArray& header, const QByteArray& msg);

    bool isConnected() const;
    QAbstractSocket::SocketState state() const;

private slots:
    void handleReadyRead();

signals:
    void msgReceived(const Packet& packet);
    void errorOccurred(QAbstractSocket::SocketError error);
    void connected();
    void disconnected();

private:
    QUrl m_url;
    QTcpSocket *m_socket;

    Header deserializeHeader(const QByteArray& data) const;

    void stateChanged(QAbstractSocket::SocketState);

    qint32 m_headerSize = 16;
};

}
