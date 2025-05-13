#include "tcpsocket.h"

#include "sequentialIdprovider.h"

#include <QThread>

using namespace Connection;

TcpSocket::TcpSocket(QObject *parent)
    : QObject(parent)
    , m_socket(new QTcpSocket())
{
    connect(m_socket,
            &QTcpSocket::readyRead,
            this,
            &TcpSocket::handleReadyRead);
}

void TcpSocket::handleReadyRead()
{
    auto socket = qobject_cast<QTcpSocket *>(sender());
    Header header;
    QByteArray header_bytes;
    QByteArray msg_bytes;

    while(socket->bytesAvailable() >= m_headerSize) {
        header_bytes = socket->read(m_headerSize);
        header = deserializeHeader(header_bytes);
        msg_bytes = socket->read(header.countBytes);

        auto &provider = SequentialIdProvider::get();
        long long id = provider.next();
        Packet packet(header, msg_bytes, id);

        emit msgReceived(packet);
    }
}

void TcpSocket::connectToHost(const QUrl& url)
{
    if (m_socket->isOpen())
        m_socket->close();

    m_url = url;
    m_socket->connectToHost(m_url.host(), m_url.port(9999));
}

void TcpSocket::send(const QByteArray& header, const QByteArray& msg)
{
    m_socket->write(header);
    m_socket->write(msg);
}

void TcpSocket::disconnectFromHost()
{
    m_socket->close();
}

bool TcpSocket::isConnected() const
{
    return m_socket->state() == QAbstractSocket::SocketState::ConnectedState;
}

QAbstractSocket::SocketState TcpSocket::state() const
{
    return m_socket->state();
}

Header TcpSocket::deserializeHeader(const QByteArray& data) const
{
    Header header;
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> header.version
           >> header.msg_type
           >> header.zero
           >> header.timeCreated
           >> header.countBytes;

    return header;
}
