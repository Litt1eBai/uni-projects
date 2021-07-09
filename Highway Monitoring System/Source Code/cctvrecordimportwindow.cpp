#include "cctvrecordimportwindow.h"
#include "ui_cctvrecordimportwindow.h"
#include <QAbstractButton>

CCTVRecordImportWindow::CCTVRecordImportWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCTVRecordImportWindow)
{
    ui->setupUi(this);
}

CCTVRecordImportWindow::CCTVRecordImportWindow(CCTVRecordModel *cctvRecordModel, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CCTVRecordImportWindow)
{
    ui->setupUi(this);
    this->cctvRecordModel = cctvRecordModel;
    init();
}

CCTVRecordImportWindow::~CCTVRecordImportWindow()
{
    delete ui;
}

void CCTVRecordImportWindow::init()
{   

    ui->importGuideStackedWidget->setCurrentIndex(0);
    ui->startTimeEdit->setDateTime(QDateTime().currentDateTime());
    ui->endTimeEdit->setDateTime(QDateTime().currentDateTime());

    // initialise file system model
    this->fileSystemModel = new QFileSystemModel(this);
    this->fileSystemModel->setRootPath("");
    this->fileSystemModel->setNameFilters(QStringList() << "*.mp4");
    ui->filePathTreeView->setModel(this->fileSystemModel);
    ui->filePathTreeView->setRootIndex(this->fileSystemModel->index(""));

    connect(ui->nextButton_firstPage, &QAbstractButton::clicked, this, [=](){
        this->m_cctvRecord.setPoleCode((char*)ui->poleCodeEdit->text().toStdString().c_str());
        this->m_cctvRecord.setDeviceCode((char*)ui->monitorCodeEdit->text().toStdString().c_str());
        this->m_cctvRecord.setStartTime(ui->startTimeEdit->dateTime());
        this->m_cctvRecord.setEndTime(ui->endTimeEdit->dateTime());
        this->m_cctvRecord.setDescription((char*)ui->descriptionEdit->toPlainText().toStdString().c_str());

        ui->importGuideStackedWidget->setCurrentIndex(1);
    });

    connect(ui->nextButton_filePathPage, &QAbstractButton::clicked, this, [=](){
        QString filePath = fileSystemModel->filePath(ui->filePathTreeView->currentIndex());
        this->m_cctvRecord.setFilePath((char*)filePath.toStdString().c_str());
        ui->importGuideStackedWidget->setCurrentIndex(2);
    });

    connect(ui->previousButton_filePagePage, &QAbstractButton::clicked, this, [=](){
       ui->importGuideStackedWidget->setCurrentIndex(0);
    });

    connect(ui->nextButton_donePage, &QAbstractButton::clicked, this, [=](){
        this->cctvRecordModel->appendRow(this->m_cctvRecord);
        this->close();
    });

    connect(ui->cancelButton_donePage, &QAbstractButton::clicked, this, [=](){
       this->close();
    });


}
