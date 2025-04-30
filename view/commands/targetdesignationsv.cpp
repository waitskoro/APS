#include "targetdesignationsv.h"
#include "ui_targetdesignationsv.h"

#include "targetdesignationmodel.h"
#include "targetdesignationsinfo.h"

#include <QStandardItemModel>

using namespace Commands::View;

TargetDesignationsV::TargetDesignationsV(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransferOfTarget)
    , m_model(new TargetDesignationModel(this))
{
    ui->setupUi(this);

    //channel numbers
    for (int i = 0; i < 13; i++)
        ui->channelNumbers->addItem(QString::number(i + 1), QVariant(i));

    //polarization
    ui->polarization->addItem("Правая круговая", QVariant(0));
    ui->polarization->addItem("Левая круговая", QVariant(1));
    ui->polarization->addItem("Вертикальная", QVariant(2));
    ui->polarization->addItem("Горизонтальная", QVariant(3));
    ui->polarization->addItem("Линейная +45%", QVariant(4));
    ui->polarization->addItem("Линейная -45%", QVariant(5));

    ui->coordinates->setModel(m_model);
}

void TargetDesignationsV::on_addAzimut_clicked()
{
    auto currentAzimut = fromStringToInt(ui->currentAzimut->text());
    auto currentElevationAngle = fromStringToInt(ui->currentElevationAngle->text());

    if (currentAzimut != -1 && currentElevationAngle != -1) {
        short newCoord[2] = {static_cast<short>(currentAzimut),
                             static_cast<short>(currentElevationAngle)};

        m_model->append(newCoord);
    }
}

void TargetDesignationsV::on_createTarget_clicked()
{
    m_info->centerFrequency = fromStringToInt(ui->centerFrequency->text());
    m_info->channelNumber = fromStringToInt(ui->channelNumbers->currentText());
    m_info->spacecraftNumber = fromStringToInt(ui->numberOfTheSpacecraft->text());
    m_info->numberOfTargetDesignations = fromStringToInt(ui->numberOfTargetDesignations->text());
}

int TargetDesignationsV::fromStringToInt(QString str)
{
    bool ok;
    int num = str.toInt(&ok);
    if (ok) {
        return num;
    }

    return -1;
}

TargetDesignationsV::~TargetDesignationsV()
{
    delete ui;
}
