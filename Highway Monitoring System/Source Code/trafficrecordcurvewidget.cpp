#include "trafficrecordcurvewidget.h"
#include "ui_trafficrecordcurvewidget.h"
#include <QColor>
#include <QBrush>
#include <QVector>
#include <QDebug>
#include "qcustomplot.h"

TrafficRecordCurveWidget::TrafficRecordCurveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrafficRecordCurveWidget)
{
    ui->setupUi(this);
    this->m_end = QDateTime().currentDateTime().addDays(1);
    this->m_start = QDateTime().currentDateTime().addDays(-1);
    this->m_interval= 1;
    this->m_poleCode = "";
}

void TrafficRecordCurveWidget::initialise(TrafficRecordModel *trafficRecordModel)
{
    this->trafficRecordModel = trafficRecordModel;
    init();
    plotSetup();
}

void TrafficRecordCurveWidget::setPoleCode(QString poleCode)
{
    this->m_poleCode = poleCode;
    this->trafficRecordProxyModel->setPoleCode(this->m_poleCode);
    replot();
}

TrafficRecordCurveWidget::~TrafficRecordCurveWidget()
{
    delete ui;
}

void TrafficRecordCurveWidget::init()
{
    ui->intervalEdit->setValue(1);
    ui->stackedWidget->setCurrentIndex(0);
    ui->fromTimeEdit->setDateTime(this->m_start);
    ui->toTimeEdit->setDateTime(this->m_end);
    ui->intervalEdit->setRange(1,60*24);

    this->trafficRecordProxyModel = new TrafficRecordProxyModel(this);
    this->trafficRecordProxyModel->setSourceModel(this->trafficRecordModel);


    ui->recordTableView->setModel(this->trafficRecordProxyModel);
    ui->recordTableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->recordTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    this->trafficRecordProxyModel->setSourceModel(this->trafficRecordModel);
    connect(ui->fromTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](QDateTime start){
        this->m_start = start;
        this->trafficRecordProxyModel->setInterval(this->m_start, this->m_end);
        replot();
    });

    connect(ui->toTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](QDateTime end){
        this->m_end = end;
        this->trafficRecordProxyModel->setInterval(this->m_start, this->m_end);
        replot();
    });

    connect(ui->intervalEdit, static_cast<void (QDoubleSpinBox::*)(double data)>(&QDoubleSpinBox::valueChanged),
            this, [=](double interval){
        this->m_interval = interval;
        replot();
    });

    connect(ui->refresButton, &QAbstractButton::clicked, this, [=](){
        ui->recordPlot->replot();
    });

    connect(ui->curveButton, &QAbstractButton::clicked, this, [=](){
       ui->stackedWidget->setCurrentIndex(0);
    });
    connect(ui->dataButton, &QAbstractButton::clicked, this, [=](){
       ui->stackedWidget->setCurrentIndex(1);
    });
}

void TrafficRecordCurveWidget::plotSetup()
{
    ui->recordPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
    ui->recordPlot->addGraph();

    ui->recordPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle));

    int upperRange;
    QVector<QCPGraphData> timeData = this->trafficRecordModel->getTimeData(m_start, m_end, m_interval, m_poleCode, upperRange);
    ui->recordPlot->graph()->data()->set(timeData);
    ui->recordPlot->xAxis->setRange(timeData.first().key, timeData.last().key);
    ui->recordPlot->yAxis->setRange(0, upperRange);

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);
    dateTicker->setDateTimeFormat("dd-MMMM-yyyy\nHH:mm:ss");
    dateTicker->setTickCount(5);
    ui->recordPlot->xAxis->setTicker(dateTicker);

    ui->recordPlot->xAxis->setLabel("Date");
    ui->recordPlot->yAxis->setLabel("Traffic");

    ui->recordPlot->replot();


//    ui->recordPlot->graph()->setLineStyle(QCPGraph::lsLine);
//    ui->recordPlot->graph()->setPen(QPen(Qt::blue));
//    ui->recordPlot->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
    // configure bottom axis to show date instead of number:
//    ui->recordPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(m_start),
//            QCPAxisTickerDateTime::dateTimeToKey(m_end));




    // configure left axis text labels:
//    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);

//    textTicker->addTick(10, "a bit\nlow");
//    textTicker->addTick(50, "quite\nhigh");

//    ui->recordPlot->yAxis->setTicker(textTicker);

    // set a more compact font size for bottom and left axis tick labels:
//    ui->recordPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
//    ui->recordPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));
    // set axis labels:
//    ui->recordPlot->xAxis2->setVisible(true);
//    ui->recordPlot->yAxis2->setVisible(true);
//    ui->recordPlot->xAxis2->setTicks(false);
//    ui->recordPlot->yAxis2->setTicks(false);
//    ui->recordPlot->xAxis2->setTickLabels(false);
//    ui->recordPlot->yAxis2->setTickLabels(false);
    // show legend with slightly transparent background brush:
//    ui->recordPlot->legend->setVisible(true);
    //    ui->recordPlot->legend->setBrush(QColor(255, 255, 255, 150));
}

void TrafficRecordCurveWidget::replot()
{
    int upperRange;
    QVector<QCPGraphData> timeData = this->trafficRecordModel->getTimeData(m_start, m_end, m_interval, m_poleCode, upperRange);
    ui->recordPlot->yAxis->setRange(0, upperRange);
    ui->recordPlot->graph()->data()->set(timeData);
    ui->recordPlot->xAxis->setRange(QCPAxisTickerDateTime::dateTimeToKey(m_start),
            QCPAxisTickerDateTime::dateTimeToKey(m_end));
    ui->recordPlot->replot();
}
