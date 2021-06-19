#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "polemodel.h"
#include <QDebug>
#include <QAbstractButton>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), poleModel(this), monitorModel(this)
{
    ui->setupUi(this);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    QMainWindow::showMaximized();

    // set headerlabel and tab
    ui->generalTab->setCurrentIndex(0);
    ui->headerLabel->setText("Your Dashboard");

    ui->statisticsWidget->initialise(&(this->poleModel), &(this->monitorModel));

    // click tab to change header label
    connect(ui->generalTab, &QTabWidget::currentChanged, ui->headerLabel, [=](int index){
        switch (index) {
            case 0: {
                ui->headerLabel->setText("Your Dashboard");
                break;
            }
            case 1: {
                ui->headerLabel->setText("Where Are You");
                break;
            }
            case 2: {
                ui->headerLabel->setText("Statistics");
            }
        }
    });



}

