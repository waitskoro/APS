#include "authform.h"
#include "ui_authform.h"

#include <QDateTime>
#include <QBoxLayout>

#include "loader.h"
#include "connection/connectionmanager.h"

using namespace Connection;
using namespace Connection::View;

AuthForm::AuthForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AuthForm)
    , m_connectionManager(new ConnectionManager())
    , m_loader(new Loader(this))
{
    ui->setupUi(this);

    m_connectionList = new ConnectionsList(this);
    m_connectionList->move(0, 50);

    m_loader->setVisible(false);
    ui->load->addWidget(m_loader);

    connect(m_connectionList,
            &ConnectionsList::selectedItemChanged,
            this,
            &AuthForm::onSelectedItemChanged);

    connect(m_connectionManager,
            &ConnectionManager::connectionFailed,
            this,
            [this](){
                setEnabled(true);
                m_loader->viewGif(false);
                emit unconnected();
            });

    connect(m_connectionManager,
            &ConnectionManager::disconnected,
            this,
            [this](){
                setEnabled(true);
            });

    connect(m_connectionManager,
            &ConnectionManager::connecting,
            this,
            [this](){
                setEnabled(false);
                m_loader->viewGif(true);
                emit connecting();
            });

    connect(m_connectionManager,
            &ConnectionManager::connected,
            this,
            [this](){
                setVisible(false);
                m_loader->viewGif(false);
                emit connected();
            });

    connect(m_loader,
            &Loader::cancel,
            [this](){
                setEnabled(true);
                emit m_connectionManager->cancel();
            });
}

void AuthForm::setEnabled(bool enable)
{

    ui->save->setEnabled(enable);
    ui->remove->setEnabled(enable);
    ui->connect->setEnabled(enable);
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

void AuthForm::on_connect_clicked()
{
    if (validateInput(ui->tcp_ac->text()) && validateInput(ui->tcp_p2->text())) {
        QUrl url_ac = QUrl::fromUserInput(ui->tcp_ac->text());
        QUrl url_p2 = QUrl::fromUserInput(ui->tcp_p2->text());

        m_connectionManager->connectToHost(url_ac, url_p2);
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

bool AuthForm::validateInput(const QString &text) const
{
    const QUrl url = QUrl::fromUserInput(text);
    return url.isValid() && !url.host().isEmpty();
}

AuthForm::~AuthForm()
{
    delete ui;
}
