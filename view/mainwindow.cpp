#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QMessageBox>

#include "commands/targetdesignationsv.h"
#include "commands/tcptargetdesignations.h"

using namespace Connection::View;
using namespace Commands::View;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_authForm(new AuthForm())
    , m_msgBox(new QMessageBox())
    , m_tcpTargetDesignations(new Commands::TcpTargetDesignations(this))
{
    ui->setupUi(this);

    // ui->menubar->setEnabled(false);
    ui->menubar->setStyleSheet("background-color: #E8E7E7");
    ui->menubar->setStyleSheet("QMenu::item:selected { background-color: #8D8D8D; }");

    ui->horizontalLayout->addWidget(m_authForm);

    connect(m_authForm,
            &AuthForm::connected,
            [this](){
                ui->menubar->setEnabled(true);
                m_msgBox->setText("Успешно подключено к сокетам");
                m_msgBox->exec();
            });

    connect(m_authForm,
            &AuthForm::disconnected,
            [this](){
                ui->menubar->setEnabled(false);
                m_msgBox->setText("Отключение от сокетов");
                m_msgBox->exec();
            });

    connect(m_authForm,
            &AuthForm::unconnected,
            [this](){
                ui->menubar->setEnabled(false);
                m_msgBox->setText("Невозможно подключиться к сокету");
                m_msgBox->exec();
            });
}

void MainWindow::on_exit_triggered()
{
    emit m_authForm->disconnected();
}

void MainWindow::on_transferOfTarget_triggered()
{
    TargetDesignationsV *transferOfTarget = new TargetDesignationsV();
    transferOfTarget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
