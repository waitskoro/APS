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

struct DataChannelSession {
    quint8 channelNumber;
    quint8 sectorNumber;
    quint8 physicalChannelNumber;
    quint8 polarizationDirection;
    quint16 spacecraftNumber;
    quint32 centerFrequency; // in kHz (1544-1545 MHz range)
    double startTime;        // OADate format
    double endTime;          // OADate format
    qint16 targetCoordinates[2]; // [0] - azimuth ×0.1 deg, [1] - elevation ×0.1 deg

    friend QDataStream &operator>>(QDataStream &stream, DataChannelSession &session) {
        stream >> session.channelNumber >> session.sectorNumber
            >> session.physicalChannelNumber >> session.polarizationDirection
            >> session.spacecraftNumber >> session.centerFrequency
            >> session.startTime >> session.endTime
            >> session.targetCoordinates[0] >> session.targetCoordinates[1];
        return stream;
    }
};

struct DataChannelSegment {
    quint8 sectorNumber;
    quint8 physicalChannelNumber;
    quint8 polarizationDirection;
    quint16 spacecraftNumber;
    quint32 centerFrequency;
    double startTime;
    double endTime;
    quint16 targetCount;
    DataChannelSession* targets;

    DataChannelSegment() : targets(nullptr) {}
    ~DataChannelSegment() { delete[] targets; }

    friend QDataStream &operator>>(QDataStream &stream, DataChannelSegment &segment) {
        stream >> segment.sectorNumber >> segment.physicalChannelNumber
            >> segment.polarizationDirection >> segment.spacecraftNumber
            >> segment.centerFrequency >> segment.startTime >> segment.endTime
            >> segment.targetCount;

        segment.targets = new DataChannelSession[segment.targetCount];
        for (quint16 i = 0; i < segment.targetCount; ++i) {
            stream >> segment.targets[i];
        }
        return stream;
    }
};

struct DataChannelInfo {
    quint8 channelNumber;
    quint8 segmentCount;
    DataChannelSegment* segments;

    DataChannelInfo() : segments(nullptr) {}
    ~DataChannelInfo() { delete[] segments; }

    friend QDataStream &operator>>(QDataStream &stream, DataChannelInfo &channel) {
        stream >> channel.channelNumber >> channel.segmentCount;

        channel.segments = new DataChannelSegment[channel.segmentCount];
        for (quint8 i = 0; i < channel.segmentCount; ++i) {
            stream >> channel.segments[i];
        }
        return stream;
    }
};

struct DataChannelMessage {
    quint8 activeChannelsCount;
    DataChannelInfo* channels;

    DataChannelMessage() : channels(nullptr) {}
    ~DataChannelMessage() { delete[] channels; }

    friend QDataStream &operator>>(QDataStream &stream, DataChannelMessage &msg) {
        stream >> msg.activeChannelsCount;

        msg.channels = new DataChannelInfo[msg.activeChannelsCount];
        for (quint8 i = 0; i < msg.activeChannelsCount; ++i) {
            stream >> msg.channels[i];
        }
        return stream;
    }
};

}
