#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QMessageBox>

#include "commands/targetdesignationsv.h"
#include "connection/connectionmanager.h"

using namespace Commands::View;
using namespace Connection::View;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_authForm(new AuthForm())
    , m_connectionManager(new ConnectionManager(this))
    , m_transferOfTargetV(new TargetDesignationsV())
{
    ui->setupUi(this);

    // ui->menubar->setEnabled(false);
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

    connect(m_transferOfTargetV,
            &TargetDesignationsV::sendTarget,
            m_connectionManager,
            &ConnectionManager::sendTargetDesign);
}

void MainWindow::onConnectionChanged(ConnectionStatus status)
{
    if (status == Unconnected || status == Connecting || status == Disconnected) {
        ui->menubar->setEnabled(false);
    } else {
        ui->menubar->setEnabled(true);
    }

    m_authForm->onConnectionChanged(status);
}

void MainWindow::on_exit_triggered()
{
    emit m_connectionManager->disconnect();
}

void MainWindow::on_transferOfTarget_triggered()
{
    m_transferOfTargetV->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
