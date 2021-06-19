#include "polesetupwindow.h"
#include "ui_polesetupwindow.h"
#include <QCheckBox>
#include <QLineEdit>
#include <QMessageBox>
#include <QDebug>

PoleSetupWindow::PoleSetupWindow(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::PoleSetupWindow),
    m_poleData(0, 0)
{
    ui->setupUi(this);
}

PoleSetupWindow::PoleSetupWindow(PoleModel *poleModel, MonitorModel *monitorModel, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::PoleSetupWindow),
    m_poleData(0, 0)
{
    ui->setupUi(this);
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    init();
}

PoleSetupWindow::~PoleSetupWindow()
{
    delete ui;
}

void PoleSetupWindow::init()
{
    // set initial index
    ui->setupStackedWidget->setCurrentIndex(0);

    // disable line edit
    ui->CCTVEditor_devicePage->setDisabled(true);
    ui->cellularMonitorEditor_devicePage->setDisabled(true);
    ui->trafficMonitorEditor_devicePage->setDisabled(true);

    // connect check box
    connect(ui->CCTVCheck_devicePage, &QCheckBox::clicked, ui->CCTVEditor_devicePage, &QLineEdit::setEnabled);
    connect(ui->cellularCheck_devicePage, &QCheckBox::clicked, ui->cellularMonitorEditor_devicePage, &QLineEdit::setEnabled);
    connect(ui->trafficMonitorCheck_devicePage, &QCheckBox::clicked, ui->trafficMonitorEditor_devicePage, &QLineEdit::setEnabled);

    // setup next and previous button
    ui->previousButton->setDisabled(true);
    connect(ui->nextButton, &QAbstractButton::clicked, ui->setupStackedWidget, [=](){
        int currentIndex = ui->setupStackedWidget->currentIndex();
        int totalIndex = 3;
        if (currentIndex <= totalIndex && currentIndex >= 0) {
            switch (currentIndex) {
                case 0: {
                    QString poleCodeVal = ui->poleCodeEdit->text();
                    if (this->poleModel->findPole(poleCodeVal)) {
                        QMessageBox messageBox;
                        messageBox.warning(0,"Warning","This pole already exists");
                        messageBox.setFixedSize(500,200);
                    } else {
                        // set data
                        this->m_poleData.setPoleCode((char*)poleCodeVal.toStdString().c_str());

                        // prepare for next page
                        ui->setupStackedWidget->setCurrentIndex(currentIndex + 1);
                        ui->previousButton->setEnabled(true);
                    }
                    break;
                }
                case 1: {
                    // set data
                    this->m_poleData.setDescription((char*)ui->descriptionEdit_locationPage->text().toStdString().c_str());
                    this->m_poleData.setLongitude(ui->longitudeEdit_locationPage->text().toDouble());
                    this->m_poleData.setLatitude(ui->latitudeEdit_locationPage->text().toDouble());

                    // prepare for next page
                    ui->setupStackedWidget->setCurrentIndex(currentIndex + 1);
                    break;
                }
                case 2: {
                    if (ui->CCTVCheck_devicePage->isChecked()) {
                        this->m_poleData.addMonitor(MonitorDeviceType::CCTV, (char*)ui->CCTVEditor_devicePage->text().toStdString().c_str());
                    } else {
                        this->m_poleData.addMonitor(MonitorDeviceType::CCTV, "");
                    }
                    if (ui->cellularCheck_devicePage->isChecked()) {
                        this->m_poleData.addMonitor(MonitorDeviceType::Cellular, (char*)ui->cellularMonitorEditor_devicePage->text().toStdString().c_str());
                    } else {
                        this->m_poleData.addMonitor(MonitorDeviceType::Cellular, "");
                    }
                    if (ui->trafficMonitorCheck_devicePage->isChecked()) {
                        this->m_poleData.addMonitor(MonitorDeviceType::TrafficFlow, (char*)ui->trafficMonitorEditor_devicePage->text().toStdString().c_str());
                    } else {
                        this->m_poleData.addMonitor(MonitorDeviceType::TrafficFlow, "");
                    }

                    // prepare for next page
                    ui->setupStackedWidget->setCurrentIndex(currentIndex + 1);
                    ui->nextButton->setText("Done");
                    QString descriptionText = QString("Your pole is at (%1, %2), %3,")
                            .arg(QVariant(this->m_poleData.getLongitude()).toString())
                            .arg(QVariant(this->m_poleData.getLatitude()).toString())
                            .arg(this->m_poleData.getDescription());
                    ui->descriptionShowLabel_donePage->setText(descriptionText);

                    int monitorCount = 0;
                    QString monitorText = QString("and it has its ");
                    if (this->m_poleData.getDeviceCode(MonitorDeviceType::CCTV) != "") {
                        monitorText += QString("CCTV(%1) ").arg(this->m_poleData.getDeviceCode(MonitorDeviceType::CCTV));
                        monitorCount++;
                    }
                    if (this->m_poleData.getDeviceCode(MonitorDeviceType::Cellular) != "") {
                        monitorText += QString("Cellular(%1) ").arg(this->m_poleData.getDeviceCode(MonitorDeviceType::Cellular));
                        monitorCount++;
                    }
                    if (this->m_poleData.getDeviceCode(MonitorDeviceType::TrafficFlow) != "") {
                        monitorText += QString("Traffic(%1) ").arg(this->m_poleData.getDeviceCode(MonitorDeviceType::TrafficFlow));
                        monitorCount++;
                    }
                    if (monitorCount == 0) {
                        ui->monitorInstallationShowLabel_donePage->setText("and the pole doesn't have any monitor installed");
                    } else if (monitorCount == 1) {
                        monitorText += QString("monitor installed");
                        ui->monitorInstallationShowLabel_donePage->setText(monitorText);
                    } else {
                        monitorText += QString("monitors installed");
                        ui->monitorInstallationShowLabel_donePage->setText(monitorText);
                    }
                    break;
                }
                case 3: {
                    // update model
                    this->poleModel->appedRow(this->m_poleData);
                    // close window
                    this->close();
                }
            }

        }
    });
    connect(ui->previousButton, &QAbstractButton::clicked, ui->setupStackedWidget, [=](){
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
    connect(ui->cancelButton, &QPushButton::clicked, this, &PoleSetupWindow::close);

}

void PoleSetupWindow::setPoleModel(PoleModel *poleModel)
{
    this->poleModel = poleModel;
}

void PoleSetupWindow::setMonitorModel(MonitorModel *monitorModel)
{
    this->monitorModel = monitorModel;
}
