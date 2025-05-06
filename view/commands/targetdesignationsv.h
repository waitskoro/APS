#pragma once

#include "targetdesignationsinfo.h"

#include <QWidget>

namespace Ui {
class TransferOfTarget;
}

namespace Commands {
class TargetDesignationModel;
}

namespace Commands::View {

class TargetDesignationsV : public QWidget
{
    Q_OBJECT

public:
    explicit TargetDesignationsV(QWidget *parent = nullptr);
    ~TargetDesignationsV();

signals:
    void sendTarget(TargetDesignations target);

public slots:
    void on_addAzimut_clicked();
    void on_createTarget_clicked();

private:
    int fromStringToInt(QString str);

    Ui::TransferOfTarget *ui;
    TargetDesignationModel *m_model;
};

}
