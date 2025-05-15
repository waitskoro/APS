#include "receivingdelegate.h"

#include <QPainter>
#include "receivingсhecklist.h"

using namespace Receiving::View;

ReceivingDelegate::ReceivingDelegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

void ReceivingDelegate::paint(QPainter *painter,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const
{
    painter->save();
    painter->fillRect(option.rect, "#C6D8DF");
    painter->restore();

    QStyledItemDelegate::paint(painter, option, index);

    QRect innerRect = option.rect.adjusted(0, 0, 0, 0);

    // Draw title
    painter->save();
    QFont font = painter->font();
    font.setPixelSize(20);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->drawText(innerRect.adjusted(20, 10, 0, 0),
                      Qt::AlignLeft | Qt::AlignTop,
                      "Номер космического аппарата: " + index.data(ReceivingChecklist::SpacecraftNumber).toString());
    painter->restore();

    // Define rectangles
    QRect rect1 = innerRect.adjusted(20, 40, -300, -20);
    QRect rect2 = innerRect.adjusted(400, 40, -20, -90);
    QRect rect3 = innerRect.adjusted(400, 140, -20, -20);

    // Draw rectangles
    drawRectangle(painter, QBrush("#F5F0F0", Qt::SolidPattern), rect1);
    drawRectangle(painter, QBrush("#F5F0F0", Qt::SolidPattern), rect2);
    drawRectangle(painter, QBrush("#F5F0F0", Qt::SolidPattern), rect3);

    painter->save();

    int leftLineX = rect1.left() + 250;
    painter->drawLine(leftLineX, rect1.top(),
                      leftLineX, rect1.bottom());

    // Draw content
    font.setPixelSize(14);
    painter->setFont(font);
    drawLeftSide(painter, rect1);
    drawRightSide(painter, rect1, index);
    drawSectorAzimut(painter, rect2, index);
    drawCurrentAzimut(painter, rect3, index);

    painter->restore();
}
void ReceivingDelegate::drawRectangle(QPainter *painter, QBrush color, QRect rect) const
{
    painter->save();
    painter->setPen(color.color());
    painter->setBrush(color);
    painter->drawRect(rect);
    painter->restore();
}

void ReceivingDelegate::drawText(QPainter *painter, QRect rect, QRect textRect, QString &text) const
{
    painter->drawText(textRect, Qt::TextSingleLine, text);

    painter->drawLine(QLine(QPoint(textRect.x() - 5,
                                   textRect.y() + textRect.height() / 2 + 2),
                            QPoint(rect.width() + 25,
                                   textRect.y() + textRect.height() / 2 + 2)));
}

void ReceivingDelegate::drawLeftSide(QPainter *painter, QRect rect) const
{
    //Центральная частота в кГц
    QRect centralFrequency(0, 0, 250, 30);
    centralFrequency.moveTo(rect.left() + 5, rect.top() + 5);
    QString centralFrequencyT = "Центральная частота в кГц";
    drawText(painter, rect, centralFrequency, centralFrequencyT);

    //Номер физического канала
    QRect channelNumber(0, 0, 250, 30);
    channelNumber.moveTo(rect.left() + 5, rect.top() + 25);
    QString channelNumberT = "Номер физического канала";
    drawText(painter, rect, channelNumber, channelNumberT);

    //Состояние инфраструктуры АС
    QRect state(0, 0, 250, 30);
    state.moveTo(rect.left() + 5, rect.top() + 45);
    QString stateT = "Состояние инфраструктуры АС";
    drawText(painter, rect, state, stateT);

    //Направление поляризации
    QRect polarization(0, 0, 250, 30);
    polarization.moveTo(rect.left() + 5, rect.top() + 65);
    QString polarizationT = "Направление поляризации";
    drawText(painter, rect, polarization, polarizationT);

    //Номер сектора приема
    QRect numberSector(0, 0, 250, 30);
    numberSector.moveTo(rect.left() + 5, rect.top() + 85);
    QString numberSectorT = "Номер сектора приема";
    drawText(painter, rect, numberSector, numberSectorT);

    //Среднеквадратический уровень сигнала приема
    QRect levelSignal(0, 0, 250, 35);
    levelSignal.moveTo(rect.left() + 5, rect.top() + 105);
    painter->drawText(levelSignal, Qt::TextWordWrap, "Среднеквадратический уровень сигнала приема");
}

void ReceivingDelegate::drawRightSide(QPainter *painter,
                                      QRect rect,
                                      const QModelIndex &index) const
{
    //Центральная частота в кГц
    QRect centralFrequency(0, 0, 80, 30);
    centralFrequency.moveTo(rect.left() + 255, rect.top() + 5);
    QString centralFrequencyT = index.data(ReceivingChecklist::CenterFrequency).toString();
    drawText(painter, rect, centralFrequency, centralFrequencyT);

    //Номер физического канала
    QRect channelNumber(0, 0, 80, 30);
    channelNumber.moveTo(rect.left() + 255, rect.top() + 25);
    QString channelNumberT = index.data(ReceivingChecklist::ChannelNumber).toString();
    drawText(painter, rect, channelNumber, channelNumberT);

    //Состояние инфраструктуры АС
    QRect state(0, 0, 80, 30);
    state.moveTo(rect.left() + 255, rect.top() + 45);
    QString stateT = index.data(ReceivingChecklist::State).toString();
    drawText(painter, rect, state, stateT);

    //Направление поляризации
    QRect polarization(0, 0, 80, 30);
    polarization.moveTo(rect.left() + 255, rect.top() + 65);
    QString polarizationT = index.data(ReceivingChecklist::DirectionOfPolarizaion).toString();
    drawText(painter, rect, polarization, polarizationT);

    //Номер сектора приема
    QRect numberSector(0, 0, 80, 30);
    numberSector.moveTo(rect.left() + 255, rect.top() + 85);
    QString numberSectorT = index.data(ReceivingChecklist::ReceivingSectorNumber).toString();
    drawText(painter, rect, numberSector, numberSectorT);

    //Среднеквадратический уровень сигнала приема
    QRect levelSignal(0, 0, 80, 35);
    levelSignal.moveTo(rect.left() + 255, rect.top() + 105);
    painter->drawText(levelSignal, Qt::AlignVCenter, index.data(ReceivingChecklist::LevelOfSignal).toString());
}

void ReceivingDelegate::drawSectorAzimut(QPainter *painter, QRect rect, const QModelIndex &index) const
{
    //Азимут начала сектора приема
    QRect azimutStart(0, 0, 170, 40);
    azimutStart.moveTo(rect.left() + 5, rect.top());
    QString azimutStartT = "Азимут начала сектора приема";
    painter->drawText(azimutStart, Qt::TextWordWrap, azimutStartT);

    //Азимут конца сектора приема
    QRect azimutEnd(0, 0, 170, 40);
    azimutEnd.moveTo(rect.left() + 5, rect.top() + 35);
    QString azimutEndT = "Азимут конца сектора приема";
    painter->drawText(azimutEnd, Qt::TextWordWrap, azimutEndT);

    QRect azimutStartSector(0, 0, 80, 30);
    azimutStartSector.moveTo(rect.left() + 175, rect.top());
    QString azimutStartSectorT = index.data(ReceivingChecklist::AzimutStartSector).toString();
    painter->drawText(azimutStartSector, Qt::AlignVCenter, azimutStartSectorT);

    QRect azimutEndSector(0, 0, 80, 30);
    azimutEndSector.moveTo(rect.left() + 175, rect.top() + 35);
    QString azimutEndSectorT = index.data(ReceivingChecklist::AzimutEndSector).toString();
    painter->drawText(azimutEndSector, Qt::AlignVCenter, azimutEndSectorT);

    int line1Y = rect.top() + rect.height()/2;
    int line2Y = rect.top() + (2*rect.height())/2 + 50;

    painter->drawLine(rect.left(), line1Y,
                      rect.right(), line1Y);
    painter->drawLine(rect.left(), line2Y,
                      rect.right(), line2Y);

    int leftLineX = rect.left() + 170;
    painter->drawLine(leftLineX, rect.top() + 100, leftLineX, rect.bottom() + 71);
    painter->drawLine(leftLineX, rect.top(), leftLineX, rect.bottom());
}

void ReceivingDelegate::drawCurrentAzimut(QPainter *painter, QRect rect, const QModelIndex &index) const
{
    //Текущий азимут луча
    QRect currentAzimut(0, 0, 170, 30);
    currentAzimut.moveTo(rect.left() + 5, rect.top());
    QString currentAzimutT = "Текущий азимут луча";
    painter->drawText(currentAzimut, Qt::TextSingleLine, currentAzimutT);

    //Текущий угол места луча
    QRect currentBean(0, 0, 170, 40);
    currentBean.moveTo(rect.left() + 5, rect.top() + 20);
    QString currentBeanT = "Текущий угол места луча";
    painter->drawText(currentBean, Qt::TextSingleLine, currentBeanT);

    QRect azimutStartSector(0, 0, 80, 30);
    azimutStartSector.moveTo(rect.left() + 175, rect.top() - 5);
    QString azimutStartSectorT = index.data(ReceivingChecklist::CurrentAzimut).toString();
    painter->drawText(azimutStartSector, Qt::AlignVCenter, azimutStartSectorT);

    QRect azimutEndSector(0, 0, 80, 30);
    azimutEndSector.moveTo(rect.left() + 175, rect.top() + 15);
    QString azimutEndSectorT = index.data(ReceivingChecklist::CurrentBeanAzimut).toString();
    painter->drawText(azimutEndSector, Qt::AlignVCenter, azimutEndSectorT);
}

QSize ReceivingDelegate::sizeHint(const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const
{
    Q_UNUSED(index)
    Q_UNUSED(option)

    return QSize(450, 200);
}

QWidget* ReceivingDelegate::createEditor(QWidget *parent,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) const
{
    Q_UNUSED(parent)
    Q_UNUSED(option)
    Q_UNUSED(index)
    return nullptr;
}
