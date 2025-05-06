#include "connectionmanager.h"

using namespace Commands;
using namespace Connection;

ConnectionManager::ConnectionManager(QObject *parent)
    : QObject(parent),
    m_socketAc(nullptr),
    m_socketP2(nullptr),
    m_thread(new QThread(this)),
    m_timeoutTimer(nullptr),
    m_reconnectTimer(nullptr),
    m_attemptCount(0),
    m_threadInitialized(false)
{
    this->moveToThread(m_thread);
    QMetaObject::invokeMethod(this, &ConnectionManager::setupThread, Qt::QueuedConnection);

    m_thread->start();
}

void ConnectionManager::cancel()
{
    m_socketAc->disconnect();
    m_socketP2->disconnect();

    if (m_reconnectTimer) m_reconnectTimer->stop();
    if (m_timeoutTimer) m_timeoutTimer->stop();
}

ConnectionManager::~ConnectionManager()
{
    m_thread->quit();
    m_thread->wait();
}

void ConnectionManager::setupThread()
{
    m_socketAc = new TcpSocket();
    m_socketP2 = new TcpSocket();

    m_timeoutTimer = new QTimer();
    m_reconnectTimer = new QTimer();

    m_reconnectTimer->setInterval(2000);
    m_timeoutTimer->setInterval(10000);

    connect(m_reconnectTimer, &QTimer::timeout, this, &ConnectionManager::attemptReconnect);
    connect(m_timeoutTimer, &QTimer::timeout, this, &ConnectionManager::stopReconnecting);

    m_threadInitialized = true;
}

void ConnectionManager::sendTargetDesign(TargetDesignations target)
{
    Header header;
    header.msg_type = 0x01;
    header.countBytes = No_alignment_size::cel + 4 * target.count;

    QByteArray header_bytes;
    QByteArray message_bytes;

    header_bytes = header.serializeStruct();
    qDebug() << target.planStartTime;
    qDebug() << target.planEndTime;
    QDataStream stream(&message_bytes, QIODevice::WriteOnly);
    stream.setByteOrder(QDataStream::LittleEndian);
    stream << target;
    qDebug() << "Message data size";
    qDebug() << message_bytes.size();

    m_socketAc->send(header_bytes, message_bytes);
}

void ConnectionManager::connectToHost(const QUrl &ac, const QUrl &p2)
{
    if (!m_threadInitialized) {
        qWarning() << "Thread not initialized yet";
        return;
    }

    QMetaObject::invokeMethod(this, [this, ac, p2]() {
        m_acUrl = ac;
        m_p2Url = p2;
        m_attemptCount = 0;

        attemptConnect();

        m_reconnectTimer->start();
        m_timeoutTimer->start();

        emit stateChanged(Connecting);
    });
}

void ConnectionManager::attemptConnect()
{
    m_attemptCount++;

    m_socketAc->connectToHost(m_acUrl);
    m_socketP2->connectToHost(m_p2Url);

    if (m_socketAc->isConnected() && m_socketP2->isConnected()) {
        stopReconnecting();
        emit stateChanged(Connected);
    }
}

void ConnectionManager::attemptReconnect()
{
    if (!m_timeoutTimer->isActive()) {
        return;
    }

    if (!m_socketAc->isConnected() || !m_socketP2->isConnected()) {
        attemptConnect();
    } else {
        stopReconnecting();
        emit stateChanged(Connected);
    }
}

void ConnectionManager::stopReconnecting()
{
    m_reconnectTimer->stop();
    m_timeoutTimer->stop();

    if (!m_socketAc->isConnected() || !m_socketP2->isConnected()) {
        emit stateChanged(Unconnected);
    }
}

void ConnectionManager::disconnect()
{
    QMetaObject::invokeMethod(this, [this]() {
        m_socketAc->disconnect();
        m_socketP2->disconnect();
        emit stateChanged(Disconnected);
    });
}
