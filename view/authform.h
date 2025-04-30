#pragma once

#include <QUrl>
#include <QWidget>
#include <QTcpSocket>

#include "connection/connectionlist.h"
#include "connection/connectioninfo.h"
#include "connection/socket/socketinfo.h"

namespace Connection {
class ConnectionManager;
class IConnectionParameters;
}

namespace Ui {
class AuthForm;
}

namespace Connection::Socket {
class ITcpSocket;
}

namespace Connection::View {

class Loader;

class AuthForm : public QWidget
{
    Q_OBJECT

public:
    explicit AuthForm(QWidget *parent = nullptr);

    ~AuthForm();

public slots:
    void on_save_clicked();
    void on_remove_clicked();
    void on_connect_clicked();
    void on_clearInputs_clicked();

signals:
    void cancel();
    void connected();
    void connecting();
    void unconnected();
    void disconnected();

    void connectToHost(const QUrl ac, const QUrl p2);

private:
    Ui::AuthForm *ui;

    Connection::ConnectionsList *m_connectionList;

    void onSelectedItemChanged(qint32 id);
    void setConnectionInfo(const ConnectionInfo info);
    void onConnectionStateChanged(Socket::SocketType, QAbstractSocket::SocketState);

    ConnectionInfo m_selectedInfo;

    bool validateInput(const QString &text) const;
    void setEnabled(bool enable);

    ConnectionManager *m_connectionManager;

    Loader *m_loader;
};

}
