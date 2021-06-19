#include "poleeditwindow.h"
#include "ui_poleeditwindow.h"
#include "monitoreditwindow.h"
#include "monitor.h"
#include <QTableView>
#include <QDebug>
#include <QAbstractButton>


PoleEditWindow::PoleEditWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::poleEditWindow),
    currentPoleData(0, 0)
{
    ui->setupUi(this);
    this->poleModel = new PoleModel;
    init();
}

PoleEditWindow::PoleEditWindow(PoleModel *poleModel, MonitorModel *monitorModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::poleEditWindow),
    currentPoleData(0, 0)
{
    ui->setupUi(this);
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    connect(this, &PoleEditWindow::updateDataToModel, this->poleModel, &PoleModel::setUpdatedData);
    init();

}

PoleEditWindow::~PoleEditWindow()
{
    delete ui;
}


void PoleEditWindow::setPoleModel(PoleModel *poleModel)
{
    // set model
    this->poleModel = poleModel;
    connect(this, &PoleEditWindow::updateDataToModel, this->poleModel, &PoleModel::setUpdatedData);
}

void PoleEditWindow::setMonitorModel(MonitorModel *monitorModel)
{
    this->monitorModel = monitorModel;
}

void PoleEditWindow::setPoleModelIndex(const QModelIndex &index)
{
    this->currentPoleModelIndex = index;
}

void PoleEditWindow::setPassedPoleModelData(Pole currentPoleData)
{
    this->currentPoleData = currentPoleData;
    // set header label
    ui->poleDetailHeaderLabel->setText(QString("Detail for Pole %1").arg(currentPoleData.getPoleCode()));
    ui->geoPositionDescriptionLabel->setText(QString("At Position (%1, %2), %3").arg(currentPoleData.getLongitude()).
                                             arg(currentPoleData.getLatitude()).arg(currentPoleData.getDescription()));
    // set editor
    ui->poleCodeEdit->setText(currentPoleData.getPoleCode());
    ui->longitudeEdit->setText(QVariant(currentPoleData.getLongitude()).toString());
    ui->latitudeEdit->setText(QVariant(currentPoleData.getLatitude()).toString());
    ui->descriptionEdit->setText(currentPoleData.getDescription());
    ui->CCTVDeviceCodeEdit->setText(currentPoleData.getDeviceCode(MonitorDeviceType::CCTV));
    ui->cellularMonitorCodeEdit->setText(currentPoleData.getDeviceCode(MonitorDeviceType::Cellular));
    ui->trafficMonitorCodeEdit->setText(currentPoleData.getDeviceCode(MonitorDeviceType::TrafficFlow));
    if (currentPoleData.getDeviceCode(MonitorDeviceType::CCTV) != "") {
        ui->CCTVCheck->setChecked(true);
        ui->CCTVDeviceCodeEdit->setEnabled(true);
        ui->CCTVDeviceDetailButton->setEnabled(true);
    }
    if (currentPoleData.getDeviceCode(MonitorDeviceType::Cellular) != "") {
        ui->cellularMonitorCheck->setChecked(true);
        ui->cellularMonitorCodeEdit->setEnabled(true);
        ui->cellularMonitorDetailButton->setEnabled(true);
    }
    if (currentPoleData.getDeviceCode(MonitorDeviceType::TrafficFlow) != "") {
        ui->trafficMonitorCheck->setChecked(true);
        ui->trafficMonitorCodeEdit->setEnabled(true);
        ui->trafficMonitorDetailButton->setEnabled(true);
    }

}

void PoleEditWindow::init()
{
    ui->PoleDetailStackedWidget->setCurrentIndex(0);
    // disable monitor check box
    ui->CCTVDeviceCodeEdit->setDisabled(true);
    ui->cellularMonitorCodeEdit->setDisabled(true);
    ui->trafficMonitorCodeEdit->setDisabled(true);
    ui->CCTVDeviceDetailButton->setDisabled(true);
    ui->cellularMonitorDetailButton->setDisabled(true);
    ui->trafficMonitorCodeEdit->setDisabled(true);

    // select check box to enable edit
    connect(ui->CCTVCheck, &QCheckBox::clicked, ui->CCTVDeviceCodeEdit, &QLineEdit::setEnabled);
    connect(ui->cellularMonitorCheck, &QCheckBox::clicked, ui->cellularMonitorCodeEdit, &QLineEdit::setEnabled);
    connect(ui->trafficMonitorCheck, &QCheckBox::clicked, ui->trafficMonitorCodeEdit, &QLineEdit::setEnabled);
    connect(ui->CCTVCheck, &QCheckBox::clicked, ui->CCTVDeviceDetailButton, &QAbstractButton::setEnabled);
    connect(ui->cellularMonitorCheck, &QCheckBox::clicked, ui->cellularMonitorDetailButton, &QAbstractButton::setEnabled);
    connect(ui->trafficMonitorCheck, &QCheckBox::clicked, ui->trafficMonitorDetailButton, &QAbstractButton::setEnabled);


    // click save to update data to model
    connect(ui->OKButton, &QAbstractButton::clicked, this, [=](){
        qDebug() << "set data function called";
        currentPoleData.setPoleCode((char*)(ui->poleCodeEdit->text().toStdString().c_str()));
        currentPoleData.setLongitude(ui->longitudeEdit->text().toDouble());
        currentPoleData.setLatitude(ui->latitudeEdit->text().toDouble());
        currentPoleData.setDescription((char*)(ui->descriptionEdit->text().toStdString().c_str()));
        if (ui->CCTVCheck->isChecked()) {
            currentPoleData.addMonitor(MonitorDeviceType::CCTV, (char*)(ui->CCTVDeviceCodeEdit->text().toStdString().c_str()));
        } else {
            currentPoleData.removeMonitor(MonitorDeviceType::CCTV);
        }
        if (ui->cellularMonitorCheck->isChecked()) {
            currentPoleData.addMonitor(MonitorDeviceType::Cellular, (char*)(ui->cellularMonitorCodeEdit->text().toStdString().c_str()));
        } else {
            currentPoleData.removeMonitor(MonitorDeviceType::Cellular);
        }
        if (ui->trafficMonitorCheck->isChecked()) {
            currentPoleData.addMonitor(MonitorDeviceType::TrafficFlow, (char*)(ui->trafficMonitorCodeEdit->text().toStdString().c_str()));
        } else {
            currentPoleData.removeMonitor(MonitorDeviceType::TrafficFlow);
        }

        emit updateDataToModel(this->currentPoleData, this->currentPoleModelIndex);

        this->close();
    });

    // click discard to close window
    connect(ui->discardButton, &QAbstractButton::clicked, this, &PoleEditWindow::close);

    // click monitor detail button to inform model
    connect(ui->CCTVDeviceDetailButton, &QAbstractButton::clicked, this, [=](){
        QString deviceCode = this->currentPoleData.getDeviceCode(MonitorDeviceType::CCTV);
        this->setAssociatedMonitorDataInWidget(MonitorDeviceType::CCTV, deviceCode);
        ui->PoleDetailStackedWidget->setCurrentIndex(1);
    });

    connect(ui->cellularMonitorDetailButton, &QAbstractButton::clicked, this, [=](){
        QString deviceCode = this->currentPoleData.getDeviceCode(MonitorDeviceType::Cellular);
        this->setAssociatedMonitorDataInWidget(MonitorDeviceType::Cellular, deviceCode);
        ui->PoleDetailStackedWidget->setCurrentIndex(1);
    });

    connect(ui->trafficMonitorDetailButton, &QAbstractButton::clicked, this, [=](){
        QString deviceCode = this->currentPoleData.getDeviceCode(MonitorDeviceType::TrafficFlow);
        this->setAssociatedMonitorDataInWidget(MonitorDeviceType::CCTV, deviceCode);
        ui->PoleDetailStackedWidget->setCurrentIndex(1);
    });

    // click edit button to get monitor edit window
    connect(ui->editButton, &QAbstractButton::clicked, this, [=](){
        // edit button is enabled only if device code is valid
        // get device data
        QString associatedDeviceCode = ui->monitorCodeText->text();
        Monitor associatedMonitorData = this->monitorModel->findMonitor_getData(associatedDeviceCode);
        int rowIndex = this->monitorModel->findMonitor_getIndex(associatedDeviceCode);

        MonitorEditWindow *associatedMonitorEdit = new MonitorEditWindow(this->poleModel, this->monitorModel);
        associatedMonitorEdit->setPassedMonitorData(associatedMonitorData);
        connect(associatedMonitorEdit, &MonitorEditWindow::updatedMonitorData, this, [=](Monitor updatedData){
            this->monitorModel->updateCurrentData(updatedData, rowIndex);
        });
        this->close();
        associatedMonitorEdit->exec();

    });

    // click back button to pole detail page
    connect(ui->backButton, &QAbstractButton::clicked, ui->PoleDetailStackedWidget, [=](){
        ui->PoleDetailStackedWidget->setCurrentIndex(0);
    });

}

void PoleEditWindow::closeEvent(QCloseEvent *event) {
    // reset check state
    ui->CCTVCheck->setChecked(false);
    ui->CCTVDeviceCodeEdit->setDisabled(true);
    ui->CCTVDeviceDetailButton->setDisabled(true);
    ui->cellularMonitorCheck->setChecked(false);
    ui->cellularMonitorCodeEdit->setDisabled(true);
    ui->cellularMonitorDetailButton->setDisabled(true);
    ui->trafficMonitorCheck->setChecked(false);
    ui->trafficMonitorCodeEdit->setDisabled(true);
    ui->trafficMonitorDetailButton->setDisabled(true);
    // reset page
    ui->PoleDetailStackedWidget->setCurrentIndex(0);
    QWidget::closeEvent(event);
}

void PoleEditWindow::setAssociatedMonitorDataInWidget(MonitorDeviceType type, QString deviceCode)
{
    // get data for associated monitor
    if (!(this->monitorModel->findMonitor(deviceCode))) {
        ui->monitorDetailHeaderLabel->setText("Device not found");
        ui->descriptionHeaderLabel_MonitorDetailPage->setText("Device not found");
        ui->monitorCodeText->setText("Not found");
        ui->monitorTypeText->setText("Not found");
        ui->monitorWorkStatusText->setText("Not found");
        ui->editButton->setDisabled(true);
    } else {
        ui->editButton->setEnabled(true);

        Monitor associatedMonitorData = this->monitorModel->findMonitor_getData(deviceCode);

        QString monitorDetailHeaderLabelText;
        switch (associatedMonitorData.getDeviceType()) {
            case MonitorDeviceType::CCTV: {
                monitorDetailHeaderLabelText += "CCTV";
                ui->monitorTypeText->setText("CCTV");
                break;
            }
            case MonitorDeviceType::Cellular: {
                monitorDetailHeaderLabelText += "Cellular";
                ui->monitorTypeText->setText("Cellular ");
                break;
            }
            case MonitorDeviceType::TrafficFlow: {
                monitorDetailHeaderLabelText += "Traffic";
                ui->monitorTypeText->setText("Traffic ");
                break;
            }
            case MonitorDeviceType::Abstract: {
                monitorDetailHeaderLabelText += "Unknown";
                ui->monitorTypeText->setText("Unkown");
                break;
            }
        }

        monitorDetailHeaderLabelText += " Monitor on Pole ";
        monitorDetailHeaderLabelText += this->currentPoleData.getPoleCode();
        ui->monitorDetailHeaderLabel->setText(monitorDetailHeaderLabelText);

        ui->descriptionHeaderLabel_MonitorDetailPage->setText(QString("At (%1, %2), %3")
                                                              .arg(this->currentPoleData.getLongitude())
                                                              .arg(this->currentPoleData.getLatitude())
                                                              .arg(this->currentPoleData.getDescription()));


        ui->monitorCodeText->setText(associatedMonitorData.getDeviceCode());

        switch (associatedMonitorData.getWorkStatus()) {
            case DeviceWorkStatus::Running: {
                ui->monitorWorkStatusText->setText("Running");
                break;
            }
            case DeviceWorkStatus::Down :{
                ui->monitorWorkStatusText->setText("Down");
                break;
            }
            case DeviceWorkStatus::NotInstalled: {
                ui->monitorWorkStatusText->setText("Not Installed");
                break;
            }
        }

        ui->monitorDescriptionTextBrowser->setText(associatedMonitorData.getDescription());
    }

}
