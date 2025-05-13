#pragma once

#include <QObject>
#include <QThread>
#include <QTimer>

#include "common/enums.h"
#include "socket/tcpsocket.h"
#include "common/messagesinfo.h"
#include "commands/targetdesignation//targetdesignationsinfo.h"

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
    void receivingMessage(ReceivingMessage);
    void messageReady(QByteArray, QByteArray);
    void stateChanged(ConnectionStatus status);
    void executedTheCommandRecevied(ExecutedTheCommand result);

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
    bool m_threadInitialized;\

    void onSocketAcPacketReceived(Packet packet);
};

}
