#include "connectionmanager.h"

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

    connect(this, &ConnectionManager::cancel, this,
            [this]() {
                if (m_reconnectTimer) m_reconnectTimer->stop();
                if (m_timeoutTimer) m_timeoutTimer->stop();
            },
            Qt::QueuedConnection);
}

ConnectionManager::~ConnectionManager()
{
    m_thread->quit();
    m_thread->wait();
}

void ConnectionManager::setupThread()
{
    m_socketAc = new Socket::TcpSocket();
    m_socketP2 = new Socket::TcpSocket();

    m_timeoutTimer = new QTimer();
    m_reconnectTimer = new QTimer();

    m_reconnectTimer->setInterval(2000);
    m_timeoutTimer->setInterval(10000);

    connect(m_reconnectTimer, &QTimer::timeout, this, &ConnectionManager::attemptReconnect);
    connect(m_timeoutTimer, &QTimer::timeout, this, &ConnectionManager::stopReconnecting);

    m_threadInitialized = true;
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

        emit connecting();
    });
}

void ConnectionManager::attemptConnect()
{
    m_attemptCount++;

    m_socketAc->connectToHost(m_acUrl);
    m_socketP2->connectToHost(m_p2Url);

    if (m_socketAc->isConnected() && m_socketP2->isConnected()) {
        stopReconnecting();
        emit connected();
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
        emit connected();
    }
}

void ConnectionManager::stopReconnecting()
{
    m_reconnectTimer->stop();
    m_timeoutTimer->stop();

    if (!m_socketAc->isConnected() || !m_socketP2->isConnected()) {
        emit connectionFailed();
    }
}

void ConnectionManager::disconnect()
{
    QMetaObject::invokeMethod(this, [this]() {
        m_socketAc->disconnect();
        m_socketP2->disconnect();
        emit disconnected();
    });
}
