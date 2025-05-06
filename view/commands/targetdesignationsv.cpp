#include "targetdesignationsv.h"
#include "ui_targetdesignationsv.h"

#include "targetdesignationmodel.h"
#include "targetdesignationsinfo.h"

#include <QMessageBox>
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
        m_model->append(currentAzimut, currentElevationAngle);
    }
}

void TargetDesignationsV::on_createTarget_clicked()
{
    // Проверка времени
    QDateTime startTime = ui->startTime->dateTime();
    QDateTime endTime = ui->endTime->dateTime();

    if (!startTime.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат времени начала");
        return;
    }
    if (!endTime.isValid()) {
        QMessageBox::warning(this, "Ошибка", "Некорректный формат времени окончания");
        return;
    }

    // Проверка частоты
    int centerFreq = fromStringToInt(ui->centerFrequency->text());
    if (centerFreq <= 0) {
        QMessageBox::warning(this, "Ошибка", "Центральная частота должна быть положительным числом");
        return;
    }

    // Проверка номера канала
    int channelNum = fromStringToInt(ui->channelNumbers->currentText());
    if (channelNum < 1 || channelNum > 13) {
        QMessageBox::warning(this, "Ошибка", "Номер канала должен быть от 1 до 13");
        return;
    }

    // Проверка номера КА
    int spacecraftNum = fromStringToInt(ui->numberOfTheSpacecraft->text());
    if (spacecraftNum <= 0) {
        QMessageBox::warning(this, "Ошибка", "Номер КА должен быть положительным числом");
        return;
    }

    // Проверка координат
    if (m_model->coordinates().empty()) {
        QMessageBox::warning(this, "Ошибка", "Добавьте хотя бы одну пару координат");
        return;
    }

    TargetDesignations m_info;

    QDateTime time_start = ui->startTime->dateTime();
    QDateTime time_end = ui->endTime->dateTime();

    m_info.planStartTime = double(time_start.toSecsSinceEpoch()) / double (86400) + 25569;
    m_info.planEndTime = double(time_end.toSecsSinceEpoch()) / double(86400) + 25569;

    auto data = ui->polarization->itemData(ui->polarization->currentIndex());
    m_info.directionOfPolarizaion = data.toInt();

    m_info.centerFrequency = centerFreq;
    m_info.channelNumber = channelNum;
    m_info.spacecraftNumber = spacecraftNum;

    m_info.count = m_model->coordinates().size();
    m_info.coordinates = new qint16*[m_info.count ];
    for(quint16 i = 0; i < m_info.count ; i++) {
        m_info.coordinates[i] = new qint16[2];
    }
    for(quint16 i = 0; i < m_info.count; i++) {
        m_info.coordinates[i][0]= m_model->coordinates()[i][0];
        m_info.coordinates[i][1] = m_model->coordinates()[i][0];
    }

    emit sendTarget(m_info);
}

int TargetDesignationsV::fromStringToInt(QString str)
{
    bool ok;
    int num = str.toInt(&ok);
    if (ok)
        return num;

    return -1;
}

TargetDesignationsV::~TargetDesignationsV()
{
    delete ui;
}
