#pragma once

#include <QObject>

#include "connectioninfo.h"

namespace Connection {

class IConnectionParameters : public QObject
{
    Q_OBJECT

public:
    virtual void remove(const qint32 id) = 0;
    virtual ConnectionInfo save(ConnectionInfo info) = 0;
    virtual ConnectionInfo element(const qint32 id) = 0;
    virtual void changeElement(const qint32 id, ConnectionInfo info) = 0;
    virtual QVector<ConnectionInfo> elements() = 0;
};

}
