#pragma once

#include <QWidget>

namespace Ui {
class TransferOfTarget;
}

namespace Commands {
class TargetDesignations;
class TargetDesignationModel;
}

namespace Commands::View {

class TargetDesignationsV : public QWidget
{
    Q_OBJECT

public:
    explicit TargetDesignationsV(QWidget *parent = nullptr);
    ~TargetDesignationsV();

public slots:
    void on_addAzimut_clicked();
    void on_createTarget_clicked();

private:
    int fromStringToInt(QString str);

    Ui::TransferOfTarget *ui;
    TargetDesignations *m_info;
    TargetDesignationModel *m_model;
};

}
