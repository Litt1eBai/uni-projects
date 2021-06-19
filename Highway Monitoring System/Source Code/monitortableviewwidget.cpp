#include "monitortableviewwidget.h"
#include "ui_monitortableviewwidget.h"
#include "monitoreditwindow.h"
#include "monitorsetupwindow.h"
#include <QDebug>
#include <QAbstractButton>
#include <QMessageBox>
#include <QSortFilterProxyModel>

MonitorTableViewWidget::MonitorTableViewWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorTableViewWidget)
{

    ui->setupUi(this);
    this->monitorModel = nullptr;
    this->poleModel = nullptr;

}

MonitorTableViewWidget::MonitorTableViewWidget(PoleModel *poleModel, MonitorModel *monitorModel, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitorTableViewWidget)
{
    ui->setupUi(this);
    this->monitorModel = monitorModel;
    this->poleModel = poleModel;
    init();
}

MonitorTableViewWidget::~MonitorTableViewWidget()
{
    delete ui;
}

void MonitorTableViewWidget::setMonitorModel(MonitorModel *monitorModel)
{
    this->monitorModel = monitorModel;
    ui->monitorTableView->setModel(this->monitorModel);
}

void MonitorTableViewWidget::setPoleModel(PoleModel *poleModel)
{
    this->poleModel = poleModel;
}

void MonitorTableViewWidget::initialise(PoleModel *poleModel, MonitorModel *monitorModel)
{
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    init();
}

void MonitorTableViewWidget::init()
{
    // set up table view
    ui->monitorTableView->setModel(this->monitorModel);
    ui->monitorTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->monitorTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // add and remove button
    connect(ui->addButton, &QAbstractButton::clicked, this->monitorModel, [=](){
        MonitorSetupWindow *monitorSetup = new MonitorSetupWindow(this->poleModel, this->monitorModel, this);
        monitorSetup->exec();
    });
    connect(ui->removeButton, &QAbstractButton::clicked, this->monitorModel, [=](){
       QModelIndex currentIndex = ui->monitorTableView->currentIndex();
        monitorModel->removeRow(currentIndex.row());
    });


    MonitorEditWindow* monitorEdit = new MonitorEditWindow(this->poleModel, this->monitorModel, this);

    // Another way:
//    MonitorEditWindow* monitorEdit = new MonitorEditWindow(this);
//    connect(this, &MonitorTableViewWidget::sendModel, monitorEdit, &MonitorEditWindow::getModel);
//    emit sendModel(model);

    // double click to pass data and index
    connect(this, &MonitorTableViewWidget::sendMonitorData, monitorEdit, &MonitorEditWindow::setPassedMonitorData);
    connect(this, &MonitorTableViewWidget::sendMonitorIndex, monitorEdit, &MonitorEditWindow::setMonitorModelIndex);
    connect(ui->monitorTableView, &QTableView::doubleClicked, this, [=](){
        emit sendMonitorData(this->monitorModel->getCurrentData(ui->monitorTableView->currentIndex()));
        emit sendMonitorIndex(ui->monitorTableView->currentIndex());
        monitorEdit->exec();
    });

    // find widget
    ui->findEdit->setText("Type device code to search");
    connect(ui->findButton, &QAbstractButton::clicked, this->monitorModel, [=](){
        // get row index if it can be found
       int rowIndex = monitorModel->findMonitor_getIndex(ui->findEdit->text());
        // if it is found
       if (rowIndex >= 0 && rowIndex < monitorModel->rowCount()) {
           ui->monitorTableView->selectRow(rowIndex);
           emit sendMonitorData(this->monitorModel->getCurrentData(ui->monitorTableView->currentIndex()));
           emit sendMonitorIndex(ui->monitorTableView->currentIndex());
           monitorEdit->exec();
       } else {
           QMessageBox messageBox;
           messageBox.warning(0,"Warning","Device Not Found!");
           messageBox.setFixedSize(500,200);
       }
    });

    ui->monitorTableView->setSortingEnabled(true);
    ui->monitorTableView->resizeColumnsToContents();
//    ui->monitorTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
