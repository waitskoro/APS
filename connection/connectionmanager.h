#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>
#include "socket/tcpsocket.h"

#include "connection/enums.h"

namespace Connection {

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = nullptr);
    ~ConnectionManager();

    void connectToHost(const QUrl &ac, const QUrl &p2);
    void disconnect();

    void cancel();

private slots:
    void attemptConnect();
    void attemptReconnect();
    void stopReconnecting();

signals:
    void stateChanged(ConnectionStatus status);

private:
    void setupThread();
    void doConnect(const QUrl &ac, const QUrl &p2);

    Socket::TcpSocket *m_socketAc;
    Socket::TcpSocket *m_socketP2;
    QThread *m_thread;
    QTimer *m_timeoutTimer;
    QTimer *m_reconnectTimer;
    QUrl m_acUrl;
    QUrl m_p2Url;
    int m_attemptCount;
    bool m_threadInitialized;
};

}
