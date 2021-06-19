#include "whereareyouwidget.h"
#include "ui_whereareyouwidget.h"

WhereAreYouWidget::WhereAreYouWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WhereAreYouWidget)
{
    ui->setupUi(this);
}

WhereAreYouWidget::~WhereAreYouWidget()
{
    delete ui;
}
