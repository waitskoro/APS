#pragma once

#include <QMainWindow>
#include <QMessageBox>

#include "authform.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


namespace Commands::View {
class TargetDesignationsV;
}

using namespace Commands::View;

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
    TargetDesignationsV *m_transferOfTargetV;

    void onConnectionChanged(ConnectionStatus status);
};

}
