#pragma once

#include <QDataStream>

namespace Connection {

struct ExecutedTheCommand {
    double date;
    quint8 id;
    quint8 result;

    friend QDataStream &operator >> (QDataStream &stream, ExecutedTheCommand &ex) {
        stream >> ex.date >> ex.id >> ex.result;
        return stream;
    }
};

}
