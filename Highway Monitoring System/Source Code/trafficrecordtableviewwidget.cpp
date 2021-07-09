#include "trafficrecordtableviewwidget.h"
#include "ui_trafficrecordtableviewwidget.h"
#include "trafficrecordimportwindow.h"
#include <QMessageBox>

TrafficRecordTableViewWidget::TrafficRecordTableViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrafficRecordTableViewWidget)
{
    ui->setupUi(this);
}

void TrafficRecordTableViewWidget::initialise(TrafficRecordModel *trafficRecordModel)
{
    this->trafficRecordModel = trafficRecordModel;
    init();
}

TrafficRecordTableViewWidget::~TrafficRecordTableViewWidget()
{
    delete ui;
}

void TrafficRecordTableViewWidget::init()
{
    ui->trafficRecordTableView->setModel(this->trafficRecordModel);
    ui->trafficRecordTableView->setSortingEnabled(true);

    ui->trafficRecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->addButton->setDisabled(true);
    ui->removeButton->setDisabled(true);
    ui->importButton->setDisabled(true);

    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->addButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->removeButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->importButton, &QAbstractButton::setEnabled);
    connect(ui->recordEditableCheck, &QCheckBox::clicked, ui->trafficRecordTableView, [=](bool checked){
       if (checked == true) {
            ui->trafficRecordTableView->setEditTriggers(QAbstractItemView::DoubleClicked);
       } else {
           ui->trafficRecordTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
       }
    });


    connect(ui->addButton, &QAbstractButton::clicked, this, [=](){
        TrafficRecord newRow;
        newRow.setRecoedNo((char*)QString("%1").arg(QVariant(this->trafficRecordModel->totalRecords() + 1).toString()).toStdString().c_str());
        this->trafficRecordModel->appendRow(newRow);
    });

    connect(ui->removeButton, &QAbstractButton::clicked, this, [=](){
        QModelIndex currentIndex = ui->trafficRecordTableView->currentIndex();
        this->trafficRecordModel->removeRow(currentIndex.row());
    });

    ui->findEdit->setText("Type pole code to search");
    connect(ui->findButton, &QAbstractButton::clicked, this->trafficRecordModel, [=](){
       int columnIndex = trafficRecordModel->findRecord_getIndex(ui->findEdit->text());
       if (columnIndex >= 0 && columnIndex < trafficRecordModel->rowCount()) {
           ui->trafficRecordTableView->selectRow(columnIndex);
       } else {
           QMessageBox messageBox;
           messageBox.warning(0,"Warning","Device Not Found!");
           messageBox.setFixedSize(500,200);
       }
    });

    connect(ui->importButton, &QAbstractButton::clicked, this, [=](){
        TrafficRecordImportWindow *importWindow = new TrafficRecordImportWindow(this->trafficRecordModel, this);
        importWindow->exec();
    });

    ui->trafficRecordTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
