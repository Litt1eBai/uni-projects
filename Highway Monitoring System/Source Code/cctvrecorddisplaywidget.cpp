#include "cctvrecorddisplaywidget.h"
#include "ui_cctvrecorddisplaywidget.h"
#include "mediaplayer.h"
#include <QTableView>
#include "cctvrecord.h"

CCTVRecordDisplayWidget::CCTVRecordDisplayWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCTVRecordDisplayWidget)
{
    ui->setupUi(this);
    this->m_end = QDateTime().currentDateTime().addDays(1);
    this->m_start = QDateTime().currentDateTime().addDays(-1);
    this->m_poleCode = "";
}

void CCTVRecordDisplayWidget::initialise(CCTVRecordModel *cctvRecordModel)
{
    this->cctvRecordModel = cctvRecordModel;
    init();
}

void CCTVRecordDisplayWidget::setPoleCode(QString poleCode)
{
    this->m_poleCode = poleCode;
    this->cctvRecordProxyModel->setPoleCode(this->m_poleCode);
}

CCTVRecordDisplayWidget::~CCTVRecordDisplayWidget()
{
    delete ui;
}

void CCTVRecordDisplayWidget::init()
{
    this->cctvRecordProxyModel = new CCTVRecordProxyModel(this);
    this->cctvRecordProxyModel->setSourceModel(this->cctvRecordModel);

    ui->fromTimeEdit->setDateTime(m_start);
    ui->toTimeEdit->setDateTime(m_end);

    ui->recordTableView->setModel(this->cctvRecordProxyModel);
    ui->recordTableView->setEditTriggers(QTableView::NoEditTriggers);
    ui->recordTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(ui->fromTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](QDateTime start){
        this->m_start = start;
        this->cctvRecordProxyModel->setInterval(this->m_start, this->m_end);
    });

    connect(ui->toTimeEdit, &QDateTimeEdit::dateTimeChanged, this, [=](QDateTime end){
        this->m_end = end;
        this->cctvRecordProxyModel->setInterval(this->m_start, this->m_end);
    });

    connect(ui->recordTableView, &QTableView::doubleClicked, this, [=](){
        MediaPlayer *playerWindow = new MediaPlayer(this);
        QModelIndex currentIndex = ui->recordTableView->currentIndex();
        QModelIndex sourceIndex = this->cctvRecordProxyModel->mapToSource(currentIndex);
        CCTVRecord record = this->cctvRecordModel->getCurrentRecord(sourceIndex.row());
        QString filePath = record.getFilePath();
        if (filePath == "")
            return;
        playerWindow->initialise(filePath);
        playerWindow->show();
    });

}
