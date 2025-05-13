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

struct ReceivingMessage {
    quint32 centerFrequency;
    quint16 spacecraftNumber;
    qint16 coordinates[2];
    quint8 channelNumber;
    qint8 directionOfPolarizaion;
    float levelOfSignal;
    quint8 receivingSectorNumber;
    qint8 state;
    qint16 azimutStartSector;
    qint16 azimutEndSector;

    friend QDataStream &operator >> (QDataStream &stream, ReceivingMessage &ch_i)
    {
        stream >> ch_i.centerFrequency >> ch_i.spacecraftNumber >> ch_i.coordinates[0] >> ch_i.coordinates[1]
            >> ch_i.channelNumber >> ch_i.directionOfPolarizaion >> ch_i.levelOfSignal
            >> ch_i.receivingSectorNumber >> ch_i.state >> ch_i.azimutStartSector
            >> ch_i.azimutEndSector;
        return stream;
    }
};

struct RecieveState {
    RecieveState() {}
    RecieveState(quint8 n)
        : n(n) {
        chanel_mas = new ReceivingMessage[n];
    }

    ~RecieveState() {
        delete[] chanel_mas;
    }

    quint8 n;
    ReceivingMessage * chanel_mas;

    void initializeChanelMas(quint8 n) {
        chanel_mas = new ReceivingMessage[n];
    }

    friend QDataStream &operator >> (QDataStream &stream, RecieveState &rs)
    {
        stream >> rs.n;
        rs.initializeChanelMas(rs.n);
        for (quint8 i = 0; i < rs.n; ++i) {
            stream >> rs.chanel_mas[i];
        }
        return stream;
    }
};

}
