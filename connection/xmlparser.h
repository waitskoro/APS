#pragma once

#include <QFile>
#include <QObject>

#include "connectioninfo.h"

namespace Connection {

class XmlParser : public QObject
{
    Q_OBJECT
public:
    XmlParser();

    void remove(const qint32 id);
    ConnectionInfo save(ConnectionInfo info);
    void change(const qint32 id, ConnectionInfo info);

    QVector<ConnectionInfo> elements();
    ConnectionInfo element(const qint32 id);

private:
    QFile *m_file;
    QString m_path;

    qint32 generateNextId();
    QVector<ConnectionInfo> m_connectionElements;
};

}
