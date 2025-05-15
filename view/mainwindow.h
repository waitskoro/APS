#pragma once

#include <QMainWindow>
#include <QMessageBox>

#include "authform.h"
#include "common/messagesinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


namespace Commands::View {
class TargetDesignationsV;
}

namespace Requests::View {
class StateOfDataChannels;
}

namespace Receiving::View {
class ReceivingChecklist;
}

namespace Common::View {
class Loader;
}

using namespace Common::View;
using namespace Commands::View;
using namespace Requests::View;

namespace Connection::View {

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void on_exit_triggered();
    void on_stopMessages_triggered();
    void on_transferOfTarget_triggered();
    void on_stateOfDataChannels_triggered();

signals:
    void stateChanged();

private:

    Ui::MainWindow *ui;
    QTimer *m_timeoutTimer;

    AuthForm *m_authForm;
    Loader *m_loader;

    ConnectionManager *m_connectionManager;
    TargetDesignationsV *m_transferOfTargetV;
    StateOfDataChannels *m_stateOfDataChannels;

    Receiving::View::ReceivingChecklist *m_receivingChecklist;

    void startTimer();
    void onTimeout();

    void onConnectionChanged(ConnectionStatus status);
    void onExecutedTheCommandRecevied(Connection::ExecutedTheCommand result);
};

}
