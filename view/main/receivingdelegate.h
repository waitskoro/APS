#pragma once

#include <QObject>
#include <QStyledItemDelegate>

namespace Receiving::View {

class ReceivingDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ReceivingDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;

    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

    QWidget* createEditor(QWidget *parent,
                          const QStyleOptionViewItem &option,
                          const QModelIndex &index) const override;

private:
    void drawRectangle(QPainter *painter, QBrush color, QRect rect) const;
    void drawText(QPainter *painter, QRect rect, QRect textRect, QString &text) const;

    void drawLeftSide(QPainter *painter, QRect rect) const;
    void drawRightSide(QPainter *painter, QRect rect, const QModelIndex &index) const;
    void drawSectorAzimut(QPainter *painter, QRect rect, const QModelIndex &index) const;
    void drawCurrentAzimut(QPainter *painter, QRect rect, const QModelIndex &index) const;
};

}
