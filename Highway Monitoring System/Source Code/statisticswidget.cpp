#include "statisticswidget.h"
#include "ui_statisticswidget.h"
#include <QAbstractButton>

StatisticsWidget::StatisticsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatisticsWidget)
{
    ui->setupUi(this);
}

void StatisticsWidget::initialise(PoleModel *poleModel, MonitorModel *monitorModel, CellularRecordModel *cellularRecordModel)
{
    this->poleModel = poleModel;
    this->monitorModel = monitorModel;
    this->cellularRecordModel = cellularRecordModel;
    init();
}

StatisticsWidget::~StatisticsWidget()
{
    delete ui;
}

void StatisticsWidget::init()
{
    ui->poleTableViewWidget->initialise(this->poleModel, this->monitorModel);
    ui->monitorTableViewWidget->initialise(this->poleModel, this->monitorModel);
    ui->cellularRecordTableViewWidget->initialise(this->cellularRecordModel);
    connect(ui->poleDataButton, &QAbstractButton::clicked, this, [=](){
       ui->dataStackedWidget->setCurrentIndex(0);
    });
    connect(ui->monitorDataButton, &QAbstractButton::clicked, this, [=](){
       ui->dataStackedWidget->setCurrentIndex(1);
    });
    connect(ui->cellularRecordButton, &QAbstractButton::clicked, this, [=](){
       ui->dataStackedWidget->setCurrentIndex(2);
    });
}
