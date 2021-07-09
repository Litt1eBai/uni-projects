#include "dashboardwidget.h"
#include "ui_dashboardwidget.h"
#include "qcustomplot.h"

DashboardWidget::DashboardWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DashboardWidget)
{
    ui->setupUi(this);
    this->poleCode = "";
}

DashboardWidget::~DashboardWidget()
{
    delete ui;
}

void DashboardWidget::initialise(PoleModel *poleModel, MonitorModel *monitorModel, CCTVRecordModel *cctvRecordModel, TrafficRecordModel *trafficRecordModel, CellularRecordModel *cellularRecordModel)
{
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    this->cctvRecordModel = cctvRecordModel;
    this->trafficRecordModel = trafficRecordModel;
    this->cellularRecordModel = cellularRecordModel;
    init();
}

void DashboardWidget::init()
{
    this->locationFilterProxyModel = new LocationFilterProxyModel(this);
    this->locationFilterProxyModel->setSourceModel(this->poleModel);
    ui->cellularCurveWidget->initialise(this->cellularRecordModel);
    ui->trafficCurveWidget->initialise(this->trafficRecordModel);
    ui->locationTableView->setModel(this->locationFilterProxyModel);
    ui->locationTableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->locationTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->locationTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    connect(ui->locationTableView, &QTableView::doubleClicked, this, [=](){
        Pole currentData = this->poleModel->getCurrentData(ui->locationTableView->currentIndex());
        this->poleCode = currentData.getPoleCode();
        ui->cellularCurveWidget->setPoleCode(this->poleCode);
        ui->trafficCurveWidget->setPoleCode(this->poleCode);
        ui->poleCodeText->setText(currentData.getPoleCode());
        ui->latitudeText->setText(QVariant(currentData.getLatitude()).toString());
        ui->longitudeText->setText(QVariant(currentData.getLatitude()).toString());
        ui->descriptionText->setText(currentData.getDescription());
    });
}
