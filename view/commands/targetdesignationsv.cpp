#include "targetdesignationsv.h"
#include "ui_targetdesignationsv.h"

#include "view/loader.h"
#include "common/helper.h"
#include "common/messagesinfo.h"
#include "targetdesignationmodel.h"
#include "commands/targetdesignation/targetdesignationsinfo.h"

#include <QString>
#include <QMessageBox>
#include <QStandardItemModel>

using namespace Commands::View;

TargetDesignationsV::TargetDesignationsV(QWidget *parent)
    : QWidget(parent)
    , m_loader(new Loader())
    , ui(new Ui::TransferOfTarget)
    , m_model(new TargetDesignationModel(this))
    , m_timeoutTimer(new QTimer())
{
    ui->setupUi(this);

    m_timeoutTimer->setInterval(10000);

    connect(m_timeoutTimer,
            &QTimer::timeout,
            this,
            &TargetDesignationsV::onTimeout);

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

void TargetDesignationsV::on_back_clicked()
{
    emit closedEvent();
}

void TargetDesignationsV::on_addAzimut_clicked()
{
    auto currentAzimut = fromStrToInt(ui->currentAzimut->text());
    auto currentElevationAngle = fromStrToInt(ui->currentElevationAngle->text());

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
    int centerFreq = fromStrToInt(ui->centerFrequency->text());
    if (centerFreq <= 0) {
        QMessageBox::warning(this, "Ошибка", "Центральная частота должна быть положительным числом");
        return;
    }

    // Проверка номера канала
    int channelNum = fromStrToInt(ui->channelNumbers->currentText());
    if (channelNum < 1 || channelNum > 13) {
        QMessageBox::warning(this, "Ошибка", "Номер канала должен быть от 1 до 13");
        return;
    }

    // Проверка номера КА
    int spacecraftNum = fromStrToInt(ui->numberOfTheSpacecraft->text());
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

    m_info.planStartTime = fromDateToDouble(ui->startTime->dateTime());
    m_info.planEndTime = fromDateToDouble(ui->endTime->dateTime());

    auto data = ui->polarization->itemData(ui->polarization->currentIndex());
    m_info.directionOfPolarizaion = data.toInt();

    m_info.centerFrequency = centerFreq;
    m_info.channelNumber = channelNum;
    m_info.spacecraftNumber = spacecraftNum;

    m_info.count = m_model->coordinates().size();
    m_info.coordinates = new qint16*[m_info.count];

    for(quint16 i = 0; i < m_info.count ; i++) {
        m_info.coordinates[i] = new qint16[2];
    }
    for(quint16 i = 0; i < m_info.count; i++) {
        m_info.coordinates[i][0]= m_model->coordinates()[i][0];
        m_info.coordinates[i][1] = m_model->coordinates()[i][1];
    }

    startTimer();

    emit sendTarget(m_info);
}

void TargetDesignationsV::onExecutedTheCommandRecevied(Connection::ExecutedTheCommand result)
{
    m_loader->close();
    m_timeoutTimer->stop();

    QMessageBox *msgBox = new QMessageBox;
    msgBox->setStyleSheet("background-color:#8481C3;");

    if (result.result == 0) {
        msgBox->setText("Целеуказание успешно получено программой АС");
    } else {
        msgBox->setText("Целеуказание принято с ошибкой. Код ошибки:" + QString::number(result.result));
    }

    msgBox->exec();

    emit closedEvent();
}

void TargetDesignationsV::closeEvent(QCloseEvent *event)
{
    if (event->type() == QEvent::Close || event->type() == QEvent::Quit)
    {
        emit closedEvent();
    }
}

void TargetDesignationsV::startTimer()
{
    m_timeoutTimer->start();

    QString text = "Ожидание статуса выполнения команды";
    m_loader->setText(text);
    m_loader->viewGif(true);
    m_loader->setVisibleButtonOk(false);
    m_loader->show();

    this->setEnabled(false);
}

void TargetDesignationsV::onTimeout()
{
    m_timeoutTimer->stop();
    m_loader->close();

    QMessageBox *msgBox = new QMessageBox;
    msgBox->setStyleSheet("background-color:#8481C3;");
    msgBox->setText("Данных об получении целеуказаний нет.\n"
                    "АС не работоспособна.");
    msgBox->exec();

    emit closedEvent();
}

TargetDesignationsV::~TargetDesignationsV()
{
    delete ui;
}
