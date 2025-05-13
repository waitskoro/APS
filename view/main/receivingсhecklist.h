#pragma once

#include <QObject>
#include <QListView>
#include "common/messagesinfo.h"

namespace Receiving::View {

class ReceivingChecklist : public QListView
{
    Q_OBJECT

public:
    enum Roles {
        CenterFrequency  = Qt::UserRole + 1,
        SpacecraftNumber,
        CurrentAzimut,
        CurrentBeanAzimut,
        ChannelNumber,
        DirectionOfPolarizaion,
        LevelOfSignal,
        ReceivingSectorNumber,
        State,
        AzimutStartSector,
        AzimutEndSector,
    };

    explicit ReceivingChecklist(QWidget *parent = nullptr);
    void addMessage(Connection::ReceivingMessage);

private:
    bool isNew;
};

}
