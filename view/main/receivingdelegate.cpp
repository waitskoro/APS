#include "receivingdelegate.h"

#include <QPainter>

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
                      "Номер космического аппарата:");
    painter->restore();

    // Define rectangles
    QRect rect1 = innerRect.adjusted(20, 40, -300, -20);
    QRect rect2 = innerRect.adjusted(400, 40, -20, -100);
    QRect rect3 = innerRect.adjusted(400, 120, -20, -20);

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
    drawRightSide(painter, rect1);
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

void ReceivingDelegate::drawRightSide(QPainter *painter, QRect rect) const
{
    //Центральная частота в кГц
    QRect centralFrequency(0, 0, 80, 30);
    centralFrequency.moveTo(rect.left() + 255, rect.top() + 5);
    QString centralFrequencyT = "1234123412341234";
    drawText(painter, rect, centralFrequency, centralFrequencyT);

    //Номер физического канала
    QRect channelNumber(0, 0, 80, 30);
    channelNumber.moveTo(rect.left() + 255, rect.top() + 25);
    QString channelNumberT = "1234123412341234";
    drawText(painter, rect, channelNumber, channelNumberT);

    //Состояние инфраструктуры АС
    QRect state(0, 0, 80, 30);
    state.moveTo(rect.left() + 255, rect.top() + 45);
    QString stateT = "1234123412341234";
    drawText(painter, rect, state, stateT);

    //Направление поляризации
    QRect polarization(0, 0, 80, 30);
    polarization.moveTo(rect.left() + 255, rect.top() + 65);
    QString polarizationT = "1234123412341234";
    drawText(painter, rect, polarization, polarizationT);

    //Номер сектора приема
    QRect numberSector(0, 0, 80, 30);
    numberSector.moveTo(rect.left() + 255, rect.top() + 85);
    QString numberSectorT = "1234123412341234";
    drawText(painter, rect, numberSector, numberSectorT);

    //Среднеквадратический уровень сигнала приема
    QRect levelSignal(0, 0, 80, 35);
    levelSignal.moveTo(rect.left() + 255, rect.top() + 105);
    painter->drawText(levelSignal, Qt::AlignVCenter, "1234123412341234");
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
