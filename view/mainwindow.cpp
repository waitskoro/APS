#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>
#include <QMessageBox>

using namespace Connection::View;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_authForm(new AuthForm())
    , m_msgBox(new QMessageBox())
{
    ui->setupUi(this);

    ui->menubar->setEnabled(false);
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

MainWindow::~MainWindow()
{
    delete ui;
}
