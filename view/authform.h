#pragma once

#include <QUrl>
#include <QWidget>
#include <QTcpSocket>

#include "common/enums.h"
#include "connection/connectionlist.h"
#include "connection/connectioninfo.h"

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

namespace Common::View {
class Loader;
}

namespace Connection::View {

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

    void onSelectedItemChanged(qint32 id);
    bool validateInput(const QString &text) const;
    void setConnectionInfo(const ConnectionInfo info);

    Common::View::Loader *m_loader;
    ConnectionInfo m_selectedInfo;
    Connection::ConnectionsList *m_connectionList;
};

}
