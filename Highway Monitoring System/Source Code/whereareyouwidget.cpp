#include "whereareyouwidget.h"
#include "ui_whereareyouwidget.h"
#include "pole.h"
#include <QTableView>

WhereAreYouWidget::WhereAreYouWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WhereAreYouWidget)
{
    ui->setupUi(this);
    this->poleCode = "";
}

WhereAreYouWidget::~WhereAreYouWidget()
{
    delete ui;
}

void WhereAreYouWidget::initialise(PoleModel *poleModel, MonitorModel *monitorModel, CCTVRecordModel *cctvRecordModel, TrafficRecordModel *trafficRecordModel, CellularRecordModel *cellularRecordModel)
{
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    this->cctvRecordModel = cctvRecordModel;
    this->trafficRecordModel = trafficRecordModel;
    this->cellularRecordModel = cellularRecordModel;
    init();
}

void WhereAreYouWidget::init()
{
    this->locationFilterProxyModel = new LocationFilterProxyModel(this);
    this->locationFilterProxyModel->setSourceModel(this->poleModel);

    ui->cellularCurveWidget->initialise(this->cellularRecordModel);
    ui->trafficCurveWidget->initialise(this->trafficRecordModel);
    ui->cctvDisplayWidget->initialise(this->cctvRecordModel);

    ui->locationTableView->setModel(this->locationFilterProxyModel);
    ui->locationTableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->locationTableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->locationTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    connect(ui->locationTableView, &QTableView::doubleClicked, this, [=](){
        Pole currentData = this->poleModel->getCurrentData(ui->locationTableView->currentIndex());
        this->poleCode = currentData.getPoleCode();
        ui->cellularCurveWidget->setPoleCode(this->poleCode);
        ui->trafficCurveWidget->setPoleCode(this->poleCode);
        ui->cctvDisplayWidget->setPoleCode(this->poleCode);
        ui->poleCodeText->setText(currentData.getPoleCode());
        ui->latitudeText->setText(QVariant(currentData.getLatitude()).toString());
        ui->longitudeText->setText(QVariant(currentData.getLatitude()).toString());
        ui->descriptionText->setText(currentData.getDescription());
    });

}
