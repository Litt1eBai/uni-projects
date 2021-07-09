#include "trafficrecordimportwindow.h"
#include "ui_trafficrecordimportwindow.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
#include <QDebug>

TrafficRecordImportWindow::TrafficRecordImportWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrafficRecordImportWindow)
{
    ui->setupUi(this);
}

TrafficRecordImportWindow::TrafficRecordImportWindow(TrafficRecordModel *trafficRecordModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrafficRecordImportWindow)
{
    ui->setupUi(this);
    this->trafficRecordModel = trafficRecordModel;
    init();
}

TrafficRecordImportWindow::~TrafficRecordImportWindow()
{
    delete ui;
}

void TrafficRecordImportWindow::init()
{
    ui->exampleFormatTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // set up temp model
    this->m_importedTempTrafficRecordModel = new TrafficRecordModel(this);
    ui->importedRecordTableView->setModel(this->m_importedTempTrafficRecordModel);
    ui->importedRecordTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // set initial index
    ui->importGuideStackedWidget->setCurrentIndex(0);

    // initialise file system model
    this->fileSystemModel = new QFileSystemModel(this);
    this->fileSystemModel->setRootPath("");
    this->fileSystemModel->setNameFilters(QStringList() << "*.xlsx");
    ui->filePathTreeView->setModel(this->fileSystemModel);
    ui->filePathTreeView->setRootIndex(this->fileSystemModel->index(""));

    ui->nextButton_beforeImportPage->setDisabled(true);

    // setup checkbox
    connect(ui->currectDataExtentionCheck, &QAbstractButton::clicked, this, [=](bool clicked){
        if (clicked && ui->currectFormatCheck->isChecked()) {
            ui->nextButton_beforeImportPage->setEnabled(true);
        } else {
            ui->nextButton_beforeImportPage->setDisabled(true);
        }
    });
    connect(ui->currectFormatCheck, &QAbstractButton::clicked, this, [=](bool clicked){
        if (clicked && ui->currectDataExtentionCheck->isChecked()) {
            ui->nextButton_beforeImportPage->setEnabled(true);
        } else {
            ui->nextButton_beforeImportPage->setDisabled(true);
        }
    });

    connect(ui->nextButton_beforeImportPage, &QAbstractButton::clicked, this, [=](){
        ui->importGuideStackedWidget->setCurrentIndex(1);
    });

    connect(ui->nextButton_filePathPage, &QAbstractButton::clicked, this, [=](){
        QString filePath = fileSystemModel->filePath(ui->filePathTreeView->currentIndex());
        int dataCount = ui->dataCountEdit->value();
        importDataFromXlsx(filePath, dataCount);
        ui->importGuideStackedWidget->setCurrentIndex(2);
    });

    connect(ui->nextButton_donePage, &QAbstractButton::clicked, this, [=](){
        QVector<TrafficRecord> newData = m_importedTempTrafficRecordModel->getRecordData();
        for (int i = 0; i < newData.size(); i++) {
            this->trafficRecordModel->appendRow(newData.at(i));
        }
        this->close();
    });

    connect(ui->cancelButton_beforeImportPage, &QAbstractButton::clicked, this, &TrafficRecordImportWindow::close);
    connect(ui->cancelButton_donePage, &QAbstractButton::clicked, this, &TrafficRecordImportWindow::close);
    connect(ui->previousButton_filePagePage, &QAbstractButton::clicked, this, [=](){
        ui->importGuideStackedWidget->setCurrentIndex(0);
    });
}

void TrafficRecordImportWindow::importDataFromXlsx(QString filePath, int rowCount)
{
    int currentRecordCount = this->trafficRecordModel->totalRecords();
    QXlsx::Document xlsxR(filePath);
    if ( xlsxR.load() ) // load excel file
    {
        qDebug() << "[debug] success to load xlsx file.";

        for (int row = 2; row <= rowCount + 1; row++) {
            TrafficRecord data;
            for (int col = 1; col <= 4; col++) {
                QXlsx::Cell* cell = xlsxR.cellAt(row, col);
                if ( cell != NULL )
                {
                    QVariant var = cell->readValue();
                    data.setRecoedNo((char*)QString("%1").arg(currentRecordCount + row).toStdString().c_str());
                    if (col == 1) {
                        QDateTime date = var.toDateTime();
                        qDebug() << var.toString();
                        qDebug() << date;
                        data.setRecordTime(date);
                    } else if (col == 2) {
                        QString poleCode = var.toString();
                        poleCode.replace(" ", "");
                        data.setPoleCode((char*)poleCode.toStdString().c_str());

                    } else if (col == 3) {
                        data.setSpeed(var.toDouble());
                    } else if (col == 4) {
                        data.setRegistrationNo((char*)var.toString().toStdString().c_str());
                    }
                }
            }
            this->m_importedTempTrafficRecordModel->appendRow(data);
        }
    }
    else
    {
        qDebug() << "[debug][error] failed to load xlsx file.";
    }
}
