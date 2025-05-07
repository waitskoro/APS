#include "receivingсhecklist.h"

#include "receivingdelegate.h"

#include <QStandardItemModel>

using namespace Receiving::View;

ReceivingChecklist::ReceivingChecklist(QWidget *parent)
    : QListView(parent)
{
    auto *delegate = new ReceivingDelegate(this);
    setItemDelegate(delegate);

    setSpacing(5);

    setModel(new QStandardItemModel(this));

    setFixedWidth(700);
    setFixedHeight(450);
}

void ReceivingChecklist::addMessage(ReceivingMessage)
{
    auto *item = new QStandardItem();
    static_cast<QStandardItemModel *>(model())->appendRow(item);
    scrollToBottom();
}
