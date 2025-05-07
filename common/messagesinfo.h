#pragma once

#include <vector>
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

namespace Receiving{

struct ReceivingMessage {
    quint32 centerFrequency;
    quint16 spacecraftNumber;
    qint16 **coordinates;
    quint8 channelNumber;
    qint8 directionOfPolarizaion;
    float levelOfSignal;
    quint8 receivingSectorNumber;
    qint8 state;
    qint16 azimutStartSector;
    qint16 azimutEndSector;
};

struct ReceivingMessages {
    quint8 countActiveChannel;
    std::vector<ReceivingMessage> messages;
};

}
