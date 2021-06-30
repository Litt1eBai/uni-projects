#include "statisticswidget.h"
#include "ui_statisticswidget.h"
#include <QAbstractButton>

StatisticsWidget::StatisticsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWidget)
{
    ui->setupUi(this);
}

void StatisticsWidget::initialise(PoleModel *poleModel, MonitorModel *monitorModel,
                                  CellularRecordModel *cellularRecordModel, CCTVRecordModel *cctvRecordModel)
{
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    this->cellularRecordModel = cellularRecordModel;
    this->cctvRecordModel = cctvRecordModel;
    init();
}

StatisticsWidget::~StatisticsWidget()
{
    delete ui;
}

void StatisticsWidget::init()
{
    ui->dataStackedWidget->setCurrentIndex(0);

    ui->poleTableViewWidget->initialise(this->poleModel, this->monitorModel);
    ui->monitorTableViewWidget->initialise(this->poleModel, this->monitorModel);
    ui->cellularRecordTableViewWidget->initialise(this->cellularRecordModel);
    ui->cctvRecordTableViewWidget->initialise(this->cctvRecordModel);

    connect(ui->poleDataButton, &QAbstractButton::clicked, this, [=](){
       ui->dataStackedWidget->setCurrentIndex(0);
    });
    connect(ui->monitorDataButton, &QAbstractButton::clicked, this, [=](){
       ui->dataStackedWidget->setCurrentIndex(1);
    });
    connect(ui->CCTVRecordButton, &QAbstractButton::clicked, this, [=](){
       ui->dataStackedWidget->setCurrentIndex(2);
    });
    connect(ui->cellularRecordButton, &QAbstractButton::clicked, this, [=](){
       ui->dataStackedWidget->setCurrentIndex(3);
    });
}
