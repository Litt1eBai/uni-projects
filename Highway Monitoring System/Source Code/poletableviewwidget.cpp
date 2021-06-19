#include "poletableviewwidget.h"
#include "ui_poletableviewwidget.h"
#include "polemodel.h"
#include "poleeditwindow.h"
#include "polesetupwindow.h"
#include <QMessageBox>

PoleTableViewWidget::PoleTableViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PoleTableViewWidget)
{
    ui->setupUi(this);
    this->poleModel = nullptr;
    this->monitorModel = nullptr;

}

PoleTableViewWidget::PoleTableViewWidget(PoleModel *poleModel, MonitorModel *monitorModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PoleTableViewWidget)
{
    ui->setupUi(this);
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    init();
}


PoleTableViewWidget::~PoleTableViewWidget()
{
    delete ui;
}

void PoleTableViewWidget::setPoleModel(PoleModel *poleModel)
{
    this->poleModel = poleModel;
    ui->poleTableView->setModel(this->poleModel);
    this->poleEdit->setPoleModel(this->poleModel);
}

void PoleTableViewWidget::setMonitorModel(MonitorModel *monitorModel)
{
    this->monitorModel = monitorModel;
    this->poleEdit->setMonitorModel(this->monitorModel);
}

void PoleTableViewWidget::initialise(PoleModel *poleModel, MonitorModel *monitorModel)
{
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    init();
}

void PoleTableViewWidget::init()
{
    // set up table view
    ui->poleTableView->setModel(this->poleModel);
    ui->poleTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->poleTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // add and remove button
    connect(ui->addButton, &QAbstractButton::clicked, this->poleModel, [=](){
        PoleSetupWindow *poleSetup = new PoleSetupWindow(this->poleModel, this->monitorModel);
        poleSetup->exec();
    });
    connect(ui->removeBotton, &QAbstractButton::clicked, this->poleModel, [=](){
        QModelIndex currentIndex = ui->poleTableView->selectionModel()->currentIndex();
        poleModel->removeRow(currentIndex.row());
    });


    // make edit window
    poleEdit = new PoleEditWindow(this->poleModel, this->monitorModel, this);

    // Another way:
//    PoleEditWindow* poleEdit = new PoleEditWindow(this);
//    connect(this, &PoleTableViewWidget::sendModel, poleEdit, &PoleEditWindow::getModel);
//    emit sendModel(poleModel);

    // double click to pass data and index
    connect(this, &PoleTableViewWidget::sendPoleData, poleEdit, &PoleEditWindow::setPassedPoleModelData);
    connect(this, &PoleTableViewWidget::sendPoleModelIndex, poleEdit, &PoleEditWindow::setPoleModelIndex);
    connect(ui->poleTableView, &QTableView::doubleClicked, this, [=](){
        emit sendPoleData(this->poleModel->getCurrentData(ui->poleTableView->currentIndex()));
        emit sendPoleModelIndex(ui->poleTableView->currentIndex());
        poleEdit->exec();
    });

    // find widget
    ui->findEdit->setText("Type pole code to search");
    connect(ui->findButton, &QAbstractButton::clicked, this->poleModel, [=](){
       int columnIndex = poleModel->findPole_getIndex(ui->findEdit->text());
       if (columnIndex >= 0 && columnIndex < poleModel->rowCount()) {
           ui->poleTableView->selectRow(columnIndex);
           emit sendPoleData(this->poleModel->getCurrentData(ui->poleTableView->currentIndex()));
           emit sendPoleModelIndex(ui->poleTableView->currentIndex());
           poleEdit->exec();
       } else {
           QMessageBox messageBox;
           messageBox.warning(0,"Warning","Device Not Found!");
           messageBox.setFixedSize(500,200);
       }
    });

    ui->poleTableView->setSortingEnabled(true);
    ui->poleTableView->resizeColumnsToContents();
//    ui->poleTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
