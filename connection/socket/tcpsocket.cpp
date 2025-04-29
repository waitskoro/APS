#include "tcpsocket.h"

#include <QThread>

#include "socketinfo.h"

namespace {
    qint32 headerSize = 12;
}

using namespace Connection::Socket;

TcpSocket::TcpSocket()
    : ITcpSocket()
{
    connect(&m_socket,
            &QTcpSocket::readyRead,
            this,
            &TcpSocket::readyRead);

    connect(&m_socket,
            &QTcpSocket::stateChanged,
            this,
            [this](QAbstractSocket::SocketState state){
                qDebug() << "Socket state:" << state;
                emit ITcpSocket::stateChanged();
            });

    connect(&m_socket,
            &QTcpSocket::errorOccurred,
            this,
            &ITcpSocket::errorOccured);
}

void TcpSocket::readyRead()
{
    while(m_socket.bytesAvailable() >= headerSize) {
        QByteArray headerBytes = m_socket.read(headerSize);
        Header header = deserializeHeader(headerBytes);

        QByteArray dataBytes = m_socket.read(header.countBytes);
        Packet packet(header, dataBytes);

        emit dataRecevied(packet);
    }
}

void TcpSocket::connectToHost(const QUrl url)
{
    if (m_socket.isOpen())
        m_socket.close();

    m_url = url;
    m_socket.connectToHost(m_url.host(), m_url.port(9999));
}

void TcpSocket::send(QByteArray header, QByteArray msg)
{
    m_socket.write(header);
    m_socket.write(msg);
}

void TcpSocket::disconnect()
{
    m_socket.close();
}

bool TcpSocket::isConnected()
{
    return m_socket.state() == QAbstractSocket::SocketState::ConnectedState;
}

QAbstractSocket::SocketState TcpSocket::state()
{
    return m_socket.state();
}

Header TcpSocket::deserializeHeader(QByteArray& data)
{
    Header header;
    QDataStream stream(data);
    stream.setByteOrder(QDataStream::LittleEndian);

    stream >> header.version >> header.msg_type >> header.zero >> header.timeCreated >> header.countBytes;

    return header;
}
