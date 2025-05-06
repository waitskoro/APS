#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>
#include "socket/tcpsocket.h"

#include "connection/enums.h"
#include "view/commands/targetdesignationsinfo.h"

namespace Connection {

class ConnectionManager : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionManager(QObject *parent = nullptr);
    ~ConnectionManager();

    void cancel();
    void disconnect();
    void connectToHost(const QUrl &ac, const QUrl &p2);
    void sendTargetDesign(Commands::TargetDesignations info);

private slots:
    void attemptConnect();
    void attemptReconnect();
    void stopReconnecting();

signals:
    void messageReady(QByteArray, QByteArray);
    void stateChanged(ConnectionStatus status);

private:
    void setupThread();
    void doConnect(const QUrl &ac, const QUrl &p2);

    TcpSocket *m_socketAc;
    TcpSocket *m_socketP2;
    QThread *m_thread;
    QTimer *m_timeoutTimer;
    QTimer *m_reconnectTimer;
    QUrl m_acUrl;
    QUrl m_p2Url;
    int m_attemptCount;
    bool m_threadInitialized;
};

}
