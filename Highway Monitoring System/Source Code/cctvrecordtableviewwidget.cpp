#include "cctvrecordtableviewwidget.h"
#include "ui_cctvrecordtableviewwidget.h"
#include "cctvrecordimportwindow.h"
#include <QMessageBox>
#include <QCheckBox>

CCTVRecordTableViewWidget::CCTVRecordTableViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCTVRecordTableViewWidget)
{
    ui->setupUi(this);
}

CCTVRecordTableViewWidget::~CCTVRecordTableViewWidget()
{
    delete ui;
}

void CCTVRecordTableViewWidget::initialise(CCTVRecordModel *cctvRecordModel)
{
    this->cctvRecordModel = cctvRecordModel;
    init();
}

void CCTVRecordTableViewWidget::init()
{
    ui->CCTVRecordTableView->setModel(this->cctvRecordModel);
    ui->CCTVRecordTableView->setSortingEnabled(true);

    ui->CCTVRecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    ui->addButton->setDisabled(true);
    ui->removeButton->setDisabled(true);
    ui->importButton->setDisabled(true);

//    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->addButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->removeButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->importButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->CCTVRecordTableView, [=](bool checked){
       if (checked == true) {
            ui->CCTVRecordTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
       } else {
           ui->CCTVRecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
       }
    });

//    connect(ui->addButton, &QAbstractButton::clicked, this, [=](){
//        CCTVRecord newRow;
//        this->cctvRecordModel->appendRow(newRow);
//    });

    connect(ui->removeButton, &QAbstractButton::clicked, this, [=](){
        QModelIndex currentIndex = ui->CCTVRecordTableView->currentIndex();
        this->cctvRecordModel->removeRow(currentIndex.row());
    });

    ui->findEdit->setText("Type pole code to search");
    connect(ui->findButton, &QAbstractButton::clicked, this->cctvRecordModel, [=](){
       int columnIndex = cctvRecordModel->findRecord_getIndex(ui->findEdit->text());
       if (columnIndex >= 0 && columnIndex < cctvRecordModel->rowCount()) {
           ui->CCTVRecordTableView->selectRow(columnIndex);
       } else {
           QMessageBox messageBox;
           messageBox.warning(0,"Warning","Device Not Found!");
           messageBox.setFixedSize(500,200);
       }
    });

    connect(ui->importButton, &QAbstractButton::clicked, this, [=](){
        CCTVRecordImportWindow *importWindow = new CCTVRecordImportWindow(this->cctvRecordModel, this);
        importWindow->exec();
    });

    ui->CCTVRecordTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
