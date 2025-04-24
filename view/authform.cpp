#include "authform.h"
#include "ui_authform.h"

#include <QBoxLayout>
#include <QDateTime>

using namespace Connection;
using namespace Connection::View;

AuthForm::AuthForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthForm)
{
    ui->setupUi(this);

    m_connectionList = new ConnectionsList(this);
    m_connectionList->move(0, 50);

    connect(m_connectionList,
            &ConnectionsList::selectedItemChanged,
            this,
            &AuthForm::onSelectedItemChanged);
}

void AuthForm::onSelectedItemChanged(qint32 id)
{
    auto element = m_connectionList->connectionInfo(id);
    m_selectedInfo = element;
    setConnectionInfo(element);
}

void AuthForm::setConnectionInfo(const ConnectionInfo info)
{
    ui->name_connection->setText(info.nameConnection);
    ui->tcp_ac->setText(info.tcpAC);
    ui->tcp_p2->setText(info.tcpP2);
}

void AuthForm::on_save_clicked()
{
    ConnectionInfo info;
    info.nameConnection = ui->name_connection->text();
    info.tcpAC = ui->tcp_ac->text();
    info.tcpP2 = ui->tcp_p2->text();

    if (info.nameConnection.trimmed() != "" ||
        info.tcpAC.trimmed() != "" ||
        info.tcpP2.trimmed() != "") {

        if (m_selectedInfo.id == -1)
            m_connectionList->addConnection(info);
        else {
            m_connectionList->changeConnection(m_selectedInfo.id, info);
            onSelectedItemChanged(info.id);
        }
    }
}

void AuthForm::on_remove_clicked()
{
    if (m_selectedInfo.id != -1 && m_selectedInfo.nameConnection.trimmed() != "")
        m_connectionList->removeConnectionInfo(m_selectedInfo.id);
}

void AuthForm::on_clearInputs_clicked()
{
    setConnectionInfo({});
    m_selectedInfo = {};

    m_connectionList->clearSelection();
}

AuthForm::~AuthForm()
{
    delete ui;
}
