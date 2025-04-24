#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>

using namespace Connection::View;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_authForm(new AuthForm())
{
    ui->setupUi(this);
    ui->horizontalLayout->addWidget(m_authForm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
