#pragma once

#include <QByteArray>
#include <QDataStream>

namespace Connection::Socket {

struct Header {
    uint16_t version = 0xAC01;
    uint8_t msg_type;
    uint8_t zero = 0x00;
    uint32_t timeCreated;
    uint32_t countBytes;

    QByteArray serializeStruct() {
        QByteArray data;
        QDataStream stream(&data, QDataStream::WriteOnly);

        stream.setByteOrder(QDataStream::LittleEndian);
        stream << version << msg_type << zero << timeCreated << countBytes;

        return data;
    }
};

enum SocketType {
    Ac,
    P2
};

struct Packet {
    explicit Packet(Header header, QByteArray data)
        : header(header)
        , data(data)
    {}

    Header header;
    QByteArray data;
};

}
