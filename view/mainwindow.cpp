#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QMessageBox>

#include "view/loader.h"
#include "main/receivingсhecklist.h"
#include "commands/targetdesignationsv.h"
#include "connection/connectionmanager.h"
#include "requests/stateofdatachannels.h"

using namespace Receiving::View;
using namespace Connection::View;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_timeoutTimer(new QTimer())
    , m_authForm(new AuthForm())
    , m_loader(new Loader())
    , m_connectionManager(new ConnectionManager(this))
    , m_transferOfTargetV(new TargetDesignationsV())
    , m_stateOfDataChannels(new StateOfDataChannels())
{
    ui->setupUi(this);
    m_receivingChecklist = new ReceivingChecklist(this);
    m_receivingChecklist->move(50, 120);
    m_receivingChecklist->setStyleSheet("background-color: #F6F6F6");
    m_receivingChecklist->setVisible(false);

    ui->label->setVisible(false);
    ui->menubar->setEnabled(false);

    ui->menubar->setStyleSheet("background-color: #E8E7E7");
    ui->menubar->setStyleSheet("QMenu::item:selected { background-color: #8D8D8D; }");

    ui->horizontalLayout->addWidget(m_authForm);

    m_timeoutTimer->setInterval(10000);

    connect(m_timeoutTimer,
            &QTimer::timeout,
            this,
            &MainWindow::onTimeout);

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
            &ConnectionManager::executedTheCommandRecevied,
            m_transferOfTargetV,
            &TargetDesignationsV::onExecutedTheCommandRecevied);

    connect(m_connectionManager,
            &ConnectionManager::receivingMessage,
            m_receivingChecklist,
            &ReceivingChecklist::addMessage);

    connect(m_connectionManager,
            &ConnectionManager::receivingMessageEmpty,
            m_receivingChecklist,
            &ReceivingChecklist::emptyMessages);

    connect(m_connectionManager,
            &ConnectionManager::dataChannelMessageReceived,
            m_stateOfDataChannels,
            &StateOfDataChannels::onMessageRecieved);

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
                ui->menubar->setEnabled(true);

                m_receivingChecklist->setVisible(true);
            });
}

void MainWindow::onConnectionChanged(ConnectionStatus status)
{
    if (status == Unconnected || status == Connecting || status == Disconnected) {
        ui->label->setVisible(false);
        ui->menubar->setEnabled(false);
        m_receivingChecklist->setVisible(false);
    }
    else {
        ui->label->setVisible(true);
        ui->menubar->setEnabled(true);
        m_receivingChecklist->setVisible(true);
    }

    m_authForm->onConnectionChanged(status);
}

void MainWindow::onExecutedTheCommandRecevied(Connection::ExecutedTheCommand result)
{
    if (!m_timeoutTimer->isActive())
        return;

    m_loader->close();
    m_timeoutTimer->stop();

    QMessageBox *msgBox = new QMessageBox;
    msgBox->setStyleSheet("background-color:#8481C3;");

    if (result.result == 0) {
        msgBox->setText("Успешное завершение приема по всем каналам. Переход в режим ожидания новых планов слежения");
    } else {
        msgBox->setText("Результат исполнения команды: \n Ошибка \n" + QString::number(result.result));
    }

    msgBox->exec();
}

void MainWindow::startTimer()
{
    m_timeoutTimer->start();

    QString text = "Ожидания ответа от программы на остановку приема";
    m_loader->setText(text);
    m_loader->viewGif(true);
    m_loader->setVisibleButtonOk(false);
    m_loader->show();

    this->setEnabled(false);
}

void MainWindow::onTimeout()
{
    m_timeoutTimer->stop();
    m_loader->close();

    QMessageBox *msgBox = new QMessageBox;
    msgBox->setStyleSheet("background-color:#8481C3;");
    msgBox->setText("Результат исполнения команды:\n"
                    "Нет ответа от АС.");
    msgBox->exec();
}

void MainWindow::on_exit_triggered()
{
    m_receivingChecklist->emptyMessages();
    emit m_connectionManager->disconnect();
}

void MainWindow::on_stopMessages_triggered()
{
    QMessageBox* message = new QMessageBox(QMessageBox::Icon::Question, tr(""),
                                           tr("Вы уверены, что хотите совершить остановку приема по всем каналам данных?"),
                                           QMessageBox::Button::Yes | QMessageBox::Button::Cancel,
                                           this);
    message->setDefaultButton(QMessageBox::Button::Cancel);
    message->open();
    connect(message, &QDialog::finished, this, [this, message] {
        message->deleteLater();
        if (message->result() == QMessageBox::Button::Yes) {
            startTimer();
            m_connectionManager->stopMessages();
        }
    });}

void MainWindow::on_transferOfTarget_triggered()
{
    setEnabled(false);
    m_transferOfTargetV->setEnabled(true);
    m_transferOfTargetV->showWindow();
}

void MainWindow::on_stateOfDataChannels_triggered()
{
    setEnabled(false);
    m_stateOfDataChannels->setEnabled(true);
    m_stateOfDataChannels->showWindow();
    m_connectionManager->requestStateOfData();
}

MainWindow::~MainWindow()
{
    delete ui;
}
