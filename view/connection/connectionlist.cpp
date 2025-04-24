#include "connectionlist.h"

#include "delegate.h"
#include "connection/connectionparameters.h"

#include <QDateTime>
#include <QStandardItemModel>

using namespace Connection;

ConnectionsList::ConnectionsList(QWidget *parent)
    : QListView(parent)
    , m_connectionParameters(new ConnectionParameters())
{
    auto *delegate = new View::Delegate(this);
    setModel(new QStandardItemModel(this));
    setItemDelegate(delegate);

    setFixedWidth(210);
    setFixedHeight(300);

    for (auto &item : m_connectionParameters->elements())
        addConnection(item);

    connect(delegate,
            &View::Delegate::selectedItemChanged,
            this,
            &ConnectionsList::selectedItemChanged);
}

const ConnectionInfo ConnectionsList::connectionInfo(const qint32 id) const
{
    return m_connectionParameters->element(id);
}

void ConnectionsList::removeConnectionInfo(const qint32 id)
{
    static_cast<QStandardItemModel *>(model())->removeRow(currentIndex().row());
    m_connectionParameters->remove(id);
}

ConnectionInfo ConnectionsList::addConnection(Connection::ConnectionInfo info)
{
    auto conInfo = m_connectionParameters->save(info);

    auto *item = new QStandardItem(QString::number(conInfo.id));

    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    item->setData(conInfo.nameConnection, Name);
    item->setData(conInfo.tcpAC, TcpAc);
    item->setData(conInfo.tcpP2, TcpP2);

    static_cast<QStandardItemModel *>(model())->appendRow(item);

    scrollToBottom();

    return conInfo;
}

void ConnectionsList::changeConnection(const qint32 last_id, const Connection::ConnectionInfo info)
{
    removeConnectionInfo(last_id);
    auto newConnection = addConnection(info);

    m_connectionParameters->changeElement(last_id, newConnection);

    QStandardItemModel* stdModel = qobject_cast<QStandardItemModel*>(model());
    setCurrentIndex(model()->index(stdModel->rowCount() - 1, 0));
}
