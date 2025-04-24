#pragma once

#include <QFile>
#include <QObject>

#include "iconnectionparameters.h"

namespace Connection {

class ConnectionParameters : public IConnectionParameters
{
    Q_OBJECT
public:
    ConnectionParameters();

    void remove(const qint32 id) override;
    ConnectionInfo save(ConnectionInfo info) override;
    ConnectionInfo element(const qint32 id) override;
    void changeElement(const qint32 id, ConnectionInfo info) override;
    QVector<ConnectionInfo> elements() override;

private:
    QFile *m_file;
    QString m_path;

    qint32 generateNextId();
    QVector<ConnectionInfo> m_connectionElements;
};

}
