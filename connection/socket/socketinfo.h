#pragma once

#include <QByteArray>
#include <QDataStream>

namespace Connection {

struct Header {
    uint16_t version = 0xAC01;
    uint8_t msg_type;
    uint8_t zero = 0x00;
    double timeCreated;
    uint32_t countBytes;

    QByteArray serializeStruct() {
        QByteArray data;
        QDataStream stream(&data, QDataStream::WriteOnly);

        stream.setByteOrder(QDataStream::BigEndian);
        stream << version << msg_type << zero << timeCreated << countBytes;

        return data;
    }
};

namespace No_alignment_size {
const quint8 cel = 26;
};

enum SocketType {
    Ac,
    P2
};

struct  Packet {
    Packet() {}

    explicit Packet(Header header, QByteArray data, long long id)
        : header(header)
        , data(data)
        , id(id)
    {}

    Header header;
    QByteArray data;
    long long id;
};

}
