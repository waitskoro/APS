#pragma once

#include <QDataStream>

namespace Commands {

struct TargetDesignations {
    qint8 channelNumber;
    qint8 directionOfPolarizaion;
    qint16 spacecraftNumber;
    qint32 centerFrequency;
    double planStartTime;
    double planEndTime;
    qint16 count;
    qint16 **coordinates;

    friend QDataStream &operator<<(QDataStream &stream, TargetDesignations cel) {
        stream << cel.channelNumber << cel.directionOfPolarizaion << cel.spacecraftNumber
               << cel.centerFrequency << cel.planStartTime << cel.planEndTime << cel.count;
        cel.coordinates = new qint16*[cel.count];

        for (quint16 i = 0; i < cel.count; i++) {
            cel.coordinates[i] = new qint16[2];
        }

        for (quint16 i = 0; i < cel.count; i++) {
            for(qsizetype j = 0; j < 2; j++) {
                stream << cel.coordinates[i][j];
            }
        }
        return stream;
    }
};

}
