#pragma once

#include <QObject>

namespace Commands {

class TcpTargetDesignations;

class TcpTargetDesignations : public QObject
{
public:
    explicit TcpTargetDesignations(QObject *parent = nullptr);

    void sendTargetDesignations(TcpTargetDesignations *target);
};

}
