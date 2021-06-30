#include "cellularrecordtableviewwidget.h"
#include "ui_cellularrecordtableviewwidget.h"
#include "cellularrecord.h"
#include "cellularrecordimportwindow.h"
#include <QAbstractButton>
#include <QModelIndex>
#include <QCheckBox>
#include <QMessageBox>


CellularRecordTableViewWidget::CellularRecordTableViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CellularRecordTableViewWidget)
{
    ui->setupUi(this);
}

void CellularRecordTableViewWidget::initialise(CellularRecordModel *cellularRecordModel)
{
    this->cellularRecordModel = cellularRecordModel;
    init();
}

CellularRecordTableViewWidget::~CellularRecordTableViewWidget()
{
    delete ui;
}

void CellularRecordTableViewWidget::init()
{
    ui->cellularModelTableView->setModel(this->cellularRecordModel);
    ui->cellularModelTableView->setSortingEnabled(true);

    ui->cellularModelTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->addButton->setDisabled(true);
    ui->removeButton->setDisabled(true);
    ui->importButton->setDisabled(true);

    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->addButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->removeButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->importButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->cellularModelTableView, [=](bool checked){
       if (checked == true) {
            ui->cellularModelTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
       } else {
           ui->cellularModelTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
       }
    });


    connect(ui->addButton, &QAbstractButton::clicked, this, [=](){
        CellularRecord newRow;
        this->cellularRecordModel->appendRow(newRow);
    });

    connect(ui->removeButton, &QAbstractButton::clicked, this, [=](){
        QModelIndex currentIndex = ui->cellularModelTableView->currentIndex();
        this->cellularRecordModel->removeRow(currentIndex.row());
    });

    ui->findEdit->setText("Type pole code to search");
    connect(ui->findButton, &QAbstractButton::clicked, this->cellularRecordModel, [=](){
       int columnIndex = cellularRecordModel->findRecord_getIndex(ui->findEdit->text());
       if (columnIndex >= 0 && columnIndex < cellularRecordModel->rowCount()) {
           ui->cellularModelTableView->selectRow(columnIndex);
       } else {
           QMessageBox messageBox;
           messageBox.warning(0,"Warning","Device Not Found!");
           messageBox.setFixedSize(500,200);
       }
    });

    connect(ui->importButton, &QAbstractButton::clicked, this, [=](){
        CellularRecordImportWindow *importWindow = new CellularRecordImportWindow(this->cellularRecordModel, this);
        importWindow->exec();
    });

    ui->cellularModelTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
