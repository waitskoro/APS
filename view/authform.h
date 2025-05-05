#pragma once

#include <QUrl>
#include <QWidget>
#include <QTcpSocket>

#include "connection/connectionlist.h"
#include "connection/connectioninfo.h"
#include "connection/enums.h"
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

    void onConnectionChanged(ConnectionStatus status);

signals:
    void cancel();
    void connectToHost(const QUrl ac, const QUrl p2);

private:
    Ui::AuthForm *ui;

    Connection::ConnectionsList *m_connectionList;

    void onSelectedItemChanged(qint32 id);
    void setConnectionInfo(const ConnectionInfo info);


    ConnectionInfo m_selectedInfo;

    bool validateInput(const QString &text) const;

    Loader *m_loader;
};

}
