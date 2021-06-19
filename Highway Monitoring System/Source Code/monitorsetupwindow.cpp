#include "monitorsetupwindow.h"
#include "ui_monitorsetupwindow.h"
#include <QMessageBox>

MonitorSetupWindow::MonitorSetupWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MonitorSetupWindow)
{
    ui->setupUi(this);
}

MonitorSetupWindow::MonitorSetupWindow(PoleModel *poleMode, MonitorModel *monitorModel, QWidget *parent):
    QDialog(parent),
    ui(new Ui::MonitorSetupWindow)
{
    ui->setupUi(this);
    this->poleModel = poleMode;
    this->monitorModel = monitorModel;
    init();
}

MonitorSetupWindow::~MonitorSetupWindow()
{
    delete ui;
}

void MonitorSetupWindow::init()
{
    // set initial index
    ui->setupStackedWidget->setCurrentIndex(0);

    // setup next and previous button
    ui->previousButton->setDisabled(true);
    connect(ui->nextButton, &QAbstractButton::clicked, this, [=](){
        int currentIndex = ui->setupStackedWidget->currentIndex();
        int totalIndex = 3;
        if (currentIndex <= totalIndex && currentIndex >= 0) {
            switch (currentIndex) {
                case 0: {
                    QString deviceCodeVal = ui->deviceCodeEdit->text();
                    if (this->monitorModel->findMonitor(deviceCodeVal)) {
                        QMessageBox messageBox;
                        messageBox.warning(0,"Warning","This monitor already exists");
                        messageBox.setFixedSize(500,200);
                    } else {
                        // set data;
                        m_monitorData.setDeviceCode((char*)deviceCodeVal.toStdString().c_str());

                        // prepare for next page
                        ui->setupStackedWidget->setCurrentIndex(currentIndex + 1);
                        ui->previousButton->setEnabled(true);
                    }
                    break;
                }
                case 1: {

                    // set data
                    if (ui->CCTVMonitorButton->isChecked()) {
                        this->m_monitorData.setDeviceType(MonitorDeviceType::CCTV);
                    }
                    if (ui->cellularMonitorButton->isChecked()) {
                        this->m_monitorData.setDeviceType(MonitorDeviceType::Cellular);
                    }
                    if (ui->trafficMonitorButton->isChecked()) {
                        this->m_monitorData.setDeviceType(MonitorDeviceType::TrafficFlow);
                    }

                    if (ui->workingButton->isChecked()) {
                        this->m_monitorData.setDeviceWorkStatus(DeviceWorkStatus::NotInstalled);
                    }
                    if (ui->notWorkingButton->isChecked()) {
                        this->m_monitorData.setDeviceWorkStatus(DeviceWorkStatus::Down);
                    }

                    // prepare for next page
                    ui->setupStackedWidget->setCurrentIndex(currentIndex + 1);

                    ui->descriptionEdit->setText("Manufacture:\nDevice Model:\nOther:");

                    break;
                }
                case 2: {
                    // set data
                    this->m_monitorData.setDescription((char*)ui->descriptionEdit->toPlainText().toStdString().c_str());

                    //prepare for next page
                    ui->setupStackedWidget->setCurrentIndex(currentIndex + 1);
                    ui->nextButton->setText("Done");
                    QString descriptionText = ("This is a ");
                    switch (this->m_monitorData.getDeviceType()) {
                        case MonitorDeviceType::CCTV: {
                            descriptionText += "CCTV ";
                            break;
                        }
                        case MonitorDeviceType::Cellular: {
                            descriptionText += "Cellular ";
                            break;
                        }
                        case MonitorDeviceType::TrafficFlow: {
                            descriptionText += "Traffic";
                            break;
                        }
                        case MonitorDeviceType::Abstract: {
                            descriptionText += "Erroe";
                            break;
                        }
                    }
                    descriptionText += "Monitor with code ";
                    descriptionText += this->m_monitorData.getDeviceCode();
                    descriptionText +=",";
                    ui->descriptionLabel_donePage->setText(descriptionText);

                    QString workStatusText = ("and it is ");
                    switch (this->m_monitorData.getWorkStatus()) {
                        case DeviceWorkStatus::NotInstalled: {
                            workStatusText += "currently functioning";
                            break;
                        }
                        case DeviceWorkStatus::Running: {
                            workStatusText += "currently functioning";
                            break;
                        }
                        case DeviceWorkStatus::Down: {
                            workStatusText += "broken and needs attention";
                            break;
                        }
                    }
                    ui->workStatusLabel_donePage->setText(workStatusText);
                    break;
                }
                case 3: {
                    // update model
                    this->monitorModel->appedRow(this->m_monitorData);
                    // close window
                    this->close();
                }
            }
        }
    });

    connect(ui->previousButton, &QAbstractButton::clicked, this, [=](){
        int currentIndex = ui->setupStackedWidget->currentIndex();
        if (currentIndex - 1 >= 0) {
            if (currentIndex == 3) {
                ui->nextButton->setText("Next >>");
            } else if (currentIndex == 1) {
                ui->previousButton->setDisabled(true);
            }
            ui->setupStackedWidget->setCurrentIndex(currentIndex - 1);
        }
    });

    connect(ui->cancelButton, &QAbstractButton::clicked, this, &MonitorSetupWindow::close);
}

void MonitorSetupWindow::setPoleModel(PoleModel *poleModel)
{
    this->poleModel = poleModel;
}
void MonitorSetupWindow::setMonitorModel(MonitorModel *monitorModel)
{
    this->monitorModel = monitorModel;
}
