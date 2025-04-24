#include "delegate.h"

#include "delegate.h"
#include "view/connection/connectionlist.h"

#include <QPainter>

using namespace Connection::View;
using Connection::ConnectionsList;

Delegate::Delegate(QObject *parent)
    : QStyledItemDelegate(parent)
{}

void Delegate::paint(QPainter *painter,
                     const QStyleOptionViewItem &option,
                     const QModelIndex &index) const
{
    QStyleOptionViewItem opt(option);
    initStyleOption(&opt, index);

    const QRect &rect(opt.rect);
    const QRect &contentRect(rect.adjusted(10,10,0,0));
    const bool lastIndex = (index.model()->rowCount() - 1) == index.row();
    const int bottomEdge = rect.bottom();
    QFont f(opt.font);

    painter->save();
    painter->setClipping(true);
    painter->setClipRect(rect);

    painter->fillRect(rect, opt.state & QStyle::State_Selected ?
                                "#8481C3" :
                                "#CAC9D7");

    // Draw bottom line
    painter->drawLine(lastIndex ? rect.left() : 0,
                      bottomEdge, rect.right(), bottomEdge);

    // Draw name
    QRect connectionName(0, 10, 100, 100);
    connectionName.moveTo(10, contentRect.top() - 5);

    f.setBold(true);
    painter->setFont(f);
    painter->drawText(connectionName, Qt::TextSingleLine, index.data(ConnectionsList::Name).toString());

    // Draw tcpAC
    QRect connectionTcpAc(0, 20, 150, 100);
    connectionTcpAc.moveTo(10, contentRect.top() + 15);

    f.setBold(false);
    painter->setFont(f);
    painter->drawText(connectionTcpAc, Qt::TextSingleLine, "П1: " + index.data(ConnectionsList::TcpAc).toString());

    // Draw tcpP2
    QRect connectionTcpP2(0, 40, 150, 100);
    connectionTcpP2.moveTo(10, contentRect.top() + 30);

    painter->setFont(f);
    painter->drawText(connectionTcpP2, Qt::TextSingleLine, "П2: " + index.data(ConnectionsList::TcpP2).toString());

    bool ok;
    int num = opt.text.toInt(&ok);
    if (ok) {
        if (opt.state & QStyle::State_Selected)
            emit selectedItemChanged(num);
    }

    painter->restore();
}

QSize Delegate::sizeHint(const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    Q_UNUSED(index)
    Q_UNUSED(option)

    return QSize(175, 60);
}
