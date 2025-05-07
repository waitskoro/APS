#pragma once

#include <QObject>
#include <QStyledItemDelegate>

namespace Connection::View {

class Delegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit Delegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const override;

signals:
    void selectedItemChanged(const qint32 id) const;
};

}
