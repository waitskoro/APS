#pragma once

#include <QListView>

#include "connection/connectioninfo.h"

namespace Connection {

class IConnectionParameters;

class ConnectionsList : public QListView
{
    Q_OBJECT

public:

    enum Roles {
        Id = Qt::UserRole + 1,
        Name,
        TcpAc,
        TcpP2
    };

    explicit ConnectionsList(QWidget *parent = nullptr);

    void removeConnectionInfo(const qint32 id);
    const ConnectionInfo connectionInfo(const qint32 id) const;

signals:
    void selectedItemChanged(qint32 id);

public slots:
    ConnectionInfo addConnection(const Connection::ConnectionInfo info);
    void changeConnection(const qint32 last_id, const Connection::ConnectionInfo info);

private:
    Connection::IConnectionParameters *m_connectionParameters;
};

}
