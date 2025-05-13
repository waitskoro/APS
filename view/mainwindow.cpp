#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QMessageBox>

#include "main/receivingсhecklist.h"
#include "commands/targetdesignationsv.h"
#include "connection/connectionmanager.h"

using namespace Commands::View;
using namespace Receiving::View;
using namespace Connection::View;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_authForm(new AuthForm())
    , m_connectionManager(new ConnectionManager(this))
    , m_transferOfTargetV(new TargetDesignationsV())
{
    ui->setupUi(this);
    m_receivingChecklist = new ReceivingChecklist(this);
    m_receivingChecklist->move(50, 120);
    m_receivingChecklist->setStyleSheet("background-color: #F6F6F6");
    m_receivingChecklist->setVisible(false);

    ui->label->setVisible(false);
    ui->label_2->setVisible(false);
    ui->menubar->setEnabled(false);
    ui->activeChannel->setVisible(false);

    ui->menubar->setStyleSheet("background-color: #E8E7E7");
    ui->menubar->setStyleSheet("QMenu::item:selected { background-color: #8D8D8D; }");

    ui->horizontalLayout->addWidget(m_authForm);

    connect(m_authForm,
            &AuthForm::connectToHost,
            m_connectionManager,
            &ConnectionManager::connectToHost);

    connect(m_authForm,
            &AuthForm::cancel,
            m_connectionManager,
            &ConnectionManager::cancel);

    connect(m_connectionManager,
            &ConnectionManager::stateChanged,
            this,
            &MainWindow::onConnectionChanged);

    connect(m_connectionManager,
            &ConnectionManager::executedTheCommandRecevied,
            m_transferOfTargetV,
            &TargetDesignationsV::onExecutedTheCommandRecevied);

    connect(m_connectionManager,
            &ConnectionManager::receivingMessage,
            m_receivingChecklist,
            &ReceivingChecklist::addMessage);

    connect(m_transferOfTargetV,
            &TargetDesignationsV::sendTarget,
            m_connectionManager,
            &ConnectionManager::sendTargetDesign);

    connect(m_transferOfTargetV,
            &TargetDesignationsV::closedEvent,
            [this](){
                m_transferOfTargetV->close();

                setEnabled(true);
                ui->label->setVisible(true);
                ui->label_2->setVisible(true);
                ui->menubar->setEnabled(true);
                ui->activeChannel->setVisible(true);

                m_receivingChecklist->setVisible(true);
            });
}

void MainWindow::onConnectionChanged(ConnectionStatus status)
{
    if (status == Unconnected || status == Connecting || status == Disconnected) {
        ui->label->setVisible(false);
        ui->menubar->setEnabled(false);
        ui->label_2->setVisible(false);
        ui->activeChannel->setVisible(false);
        m_receivingChecklist->setVisible(false);
    }
    else {
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
        ui->menubar->setEnabled(true);
        ui->activeChannel->setVisible(true);
        m_receivingChecklist->setVisible(true);
    }

    m_authForm->onConnectionChanged(status);
}

void MainWindow::on_exit_triggered()
{
    emit m_connectionManager->disconnect();
}

void MainWindow::on_transferOfTarget_triggered()
{
    setEnabled(false);
    m_transferOfTargetV->setEnabled(true);
    m_transferOfTargetV->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
