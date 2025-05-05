#pragma once

#include <QMainWindow>
#include <QMessageBox>

#include "authform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

namespace Connection::Socket {
class ITcpSocket;
}

namespace Commands::View {
class TargetDesignationsV;
}

namespace Commands {
class TcpTargetDesignations;
}

namespace Connection::View {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_exit_triggered();
    void on_transferOfTarget_triggered();

signals:
    void stateChanged();

private:
    Ui::MainWindow *ui;

    AuthForm *m_authForm;

    ConnectionManager *m_connectionManager;
    Commands::TcpTargetDesignations *m_tcpTargetDesignations;

    void onConnectionChanged(ConnectionStatus status);
};

}
