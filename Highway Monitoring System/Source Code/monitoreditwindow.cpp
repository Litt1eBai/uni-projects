#include "monitoreditwindow.h"
#include "ui_monitoreditwindow.h"
#include <QDebug>

MonitorEditWindow::MonitorEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorEditWindow)
{
    ui->setupUi(this);
    this->monitorModel = new MonitorModel;
    this->poleModel = nullptr;
    init();

}

MonitorEditWindow::MonitorEditWindow(PoleModel *poleModel, MonitorModel *monitorModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorEditWindow)
{
    ui->setupUi(this);
    this->monitorModel = monitorModel;
    this->poleModel = poleModel;
    connect(this, &MonitorEditWindow::updateMonitorDataToModel, this->monitorModel, &MonitorModel::setUpdatedData);
    init();

}

MonitorEditWindow::~MonitorEditWindow()
{
    delete ui;
}

void MonitorEditWindow::getMonitorModel(MonitorModel *model)
{
    this->monitorModel = model;
    connect(this, &MonitorEditWindow::updateMonitorDataToModel, this->monitorModel, &MonitorModel::setUpdatedData);
}

void MonitorEditWindow::setMonitorModelIndex(const QModelIndex &index)
{
    this->m_currentMonitorModelIndex = index;
    this->m_gotMonitorModelIndexFlag = true;
}

void MonitorEditWindow::setPassedMonitorData(Monitor currentData)
{
    this->m_currentMonitorData = currentData;
    // set header label
    ui->monitorDetailHeaderLabel->setText(QString("Detail for Monitor %1").arg(currentData.getDeviceCode()));
    // set editor
    ui->deviceCodeEdit->setText(currentData.getDeviceCode());
    ui->installationDataEdit->setDateTime(currentData.getInstallationDate());
    ui->descriptionEdit->setText(currentData.getDescription());
    switch (currentData.getDeviceType()) {
        case MonitorDeviceType::CCTV: {
            ui->CCTVButton->setChecked(true);
            break;
        }
        case MonitorDeviceType::Cellular: {
            ui->cellularMonitorButton->setChecked(true);
            break;
        }
        case MonitorDeviceType::TrafficFlow: {
            ui->trafficMonitorButton->setChecked(true);
            break;
        }
        case MonitorDeviceType::Abstract: {
            break;
        }
    }
    switch (currentData.getWorkStatus()) {
        case DeviceWorkStatus::Running: {
            ui->runningStateButton->setChecked(true);
            break;
        }
        case DeviceWorkStatus::Down: {
            ui->downStateButton->setChecked(true);
            break;
        }
        case DeviceWorkStatus::NotInstalled: {
            ui->notInstalledStateButton->setChecked(true);
            break;
        }
    }

}

void MonitorEditWindow::init()
{
    // did not revieve model index => emit signal only by value
    this->m_gotMonitorModelIndexFlag = false;

    // saveButton click to store data
    connect(ui->saveButton, &QAbstractButton::clicked, this, [=](){
        qDebug() << "set data function called";
        m_currentMonitorData.setDeviceCode((char*)(ui->deviceCodeEdit->text().toStdString().c_str()));
        m_currentMonitorData.setDescription((char*)ui->descriptionEdit->toPlainText().toStdString().c_str());
        if (ui->CCTVButton->isChecked()) {
            m_currentMonitorData.setDeviceType(MonitorDeviceType::CCTV);
        } else if (ui->cellularMonitorButton->isChecked()) {
            m_currentMonitorData.setDeviceType(MonitorDeviceType::Cellular);
        } else if (ui->trafficMonitorButton->isChecked()) {
            m_currentMonitorData.setDeviceType(MonitorDeviceType::TrafficFlow);
        }

        if (ui->runningStateButton->isChecked()) {
            m_currentMonitorData.setDeviceWorkStatus(DeviceWorkStatus::Running);
        } else if (ui->downStateButton->isChecked()) {
            m_currentMonitorData.setDeviceWorkStatus(DeviceWorkStatus::Down);
        } else if (ui->notInstalledStateButton->isChecked()) {
            m_currentMonitorData.setDeviceWorkStatus(DeviceWorkStatus::NotInstalled);
        }


        // Got valid index => ask model to update data
        // Didn't get index or index is invalid => pass data to someone else
        if (this->m_gotMonitorModelIndexFlag == true && this->m_currentMonitorModelIndex.isValid()) {
            emit updateMonitorDataToModel(this->m_currentMonitorData, this->m_currentMonitorModelIndex);
        } else {
            emit updatedMonitorData(this->m_currentMonitorData);
        }
        this->close();
    });

    // click discard button to close
    connect(ui->discardButton, &QAbstractButton::clicked, this, &MonitorEditWindow::close);
}

void MonitorEditWindow::closeEvent(QCloseEvent *event)
{
    QWidget::closeEvent(event);
}
