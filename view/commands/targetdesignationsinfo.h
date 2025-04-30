#pragma once

#include <QDateTime>
#include <QDataStream>

namespace Commands {

struct TargetDesignations {
    qint8 channelNumber;
    qint8 directionOfPolarizaion;
    qint16 spacecraftNumber;
    qint32 centerFrequency;
    QDateTime planStartTime;
    QDateTime planEndTime;
    qint32 numberOfTargetDesignations;
    std::vector<qint16[2]> coordinates;
};

}
