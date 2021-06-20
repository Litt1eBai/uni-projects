#include "cellularrecordtableviewwidget.h"
#include "ui_cellularrecordtableviewwidget.h"
#include "cellularrecord.h"
#include <QAbstractButton>
#include <QModelIndex>
#include <QCheckBox>


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
}
