#pragma once

#include "commands/targetdesignation/targetdesignationsinfo.h"

#include <QTimer>
#include <QWidget>
#include <QThread>
#include <QCloseEvent>

namespace Ui {
class TransferOfTarget;
}

namespace Commands {
class TargetDesignationModel;
}

namespace Connection {
struct ExecutedTheCommand;
}

namespace Common::View {
class Loader;
}

using namespace Common::View;

namespace Commands::View {

class TargetDesignationsV : public QWidget
{
    Q_OBJECT

public:
    explicit TargetDesignationsV(QWidget *parent = nullptr);
    ~TargetDesignationsV();
    void showWindow();
    void onExecutedTheCommandRecevied(Connection::ExecutedTheCommand);

signals:
    void sendTarget(TargetDesignations target);
    void closedEvent();

protected:
    void closeEvent(QCloseEvent *event) override;

public slots:
    void on_back_clicked();
    void on_addAzimut_clicked();
    void on_createTarget_clicked();

private:
    Loader *m_loader;
    Ui::TransferOfTarget *ui;
    TargetDesignationModel *m_model;

    void startTimer();
    void onTimeout();

    QTimer *m_timeoutTimer;
};

}
