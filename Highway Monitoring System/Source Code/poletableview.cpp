#include "poletableview.h"
#include "ui_poletableview.h"

PoleTableView::PoleTableView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PoleTableView)
{
    ui->setupUi(this);
}

PoleTableView::~PoleTableView()
{
    delete ui;
}
