#pragma once

#include <QObject>

namespace Connection {

struct ConnectionInfo {
    qint32 id = -1;
    QString nameConnection;
    QString tcpAC;
    QString tcpP2;
};

}
