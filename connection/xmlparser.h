#pragma once

#include <QFile>
#include <QObject>

#include "iconnectionparameters.h"

namespace Connection {

class XmlParser : public IConnectionParameters
{
    Q_OBJECT
public:
    XmlParser();

    void remove(const qint32 id) override;
    ConnectionInfo save(ConnectionInfo info) override;
    void change(const qint32 id, ConnectionInfo info) override;

    QVector<ConnectionInfo> elements() override;
    ConnectionInfo element(const qint32 id) override;


private:
    QFile *m_file;
    QString m_path;

    qint32 generateNextId();
    QVector<ConnectionInfo> m_connectionElements;
};

}
