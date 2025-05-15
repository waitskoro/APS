#include "receivingсhecklist.h"

#include "receivingdelegate.h"

#include <QTimer>
#include <QStandardItemModel>

using namespace Receiving::View;

ReceivingChecklist::ReceivingChecklist(QWidget *parent)
    : QListView(parent), isNew(false)
{
    auto *delegate = new ReceivingDelegate(this);
    setItemDelegate(delegate);

    setSpacing(5);
    setModel(new QStandardItemModel(this));
    setFixedWidth(700);
    setFixedHeight(450);

    QTimer *refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout, this, [this]() {
        isNew = true;
    });
    refreshTimer->start(1500);
}

void ReceivingChecklist::addMessage(Connection::ReceivingMessage msg)
{
    if (isNew)
        static_cast<QStandardItemModel*>(model())->clear();

    isNew = false;

    qDebug() << msg.spacecraftNumber;

    auto *item = new QStandardItem();
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    item->setData(msg.channelNumber, ChannelNumber);
    item->setData(msg.centerFrequency, CenterFrequency);
    item->setData(msg.spacecraftNumber, SpacecraftNumber);
    item->setData(msg.coordinates[0], CurrentAzimut);
    item->setData(msg.coordinates[1], CurrentBeanAzimut);
    item->setData(msg.directionOfPolarizaion, DirectionOfPolarizaion);
    item->setData(msg.levelOfSignal, LevelOfSignal);
    item->setData(msg.receivingSectorNumber, ReceivingSectorNumber);
    item->setData(msg.state, State);
    item->setData(msg.azimutStartSector, AzimutStartSector);
    item->setData(msg.azimutEndSector, AzimutEndSector);

    static_cast<QStandardItemModel *>(model())->appendRow(item);
}

void ReceivingChecklist::emptyMessages()
{
    static_cast<QStandardItemModel*>(model())->clear();
}
