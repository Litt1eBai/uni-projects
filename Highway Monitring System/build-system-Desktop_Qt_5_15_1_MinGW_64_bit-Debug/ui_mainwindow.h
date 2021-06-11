/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *MainWindow_UpperLayer;
    QHBoxLayout *horizontalLayout;
    QLabel *MainWindow_Lable;
    QTabWidget *mainWindow_Tab;
    QWidget *MainWindow_Dashboard_Tab;
    QWidget *MainWindow_Statistics_Tab;
    QVBoxLayout *verticalLayout_3;
    QTableView *testTableView;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(913, 652);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        MainWindow_UpperLayer = new QWidget(centralwidget);
        MainWindow_UpperLayer->setObjectName(QString::fromUtf8("MainWindow_UpperLayer"));
        horizontalLayout = new QHBoxLayout(MainWindow_UpperLayer);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        MainWindow_Lable = new QLabel(MainWindow_UpperLayer);
        MainWindow_Lable->setObjectName(QString::fromUtf8("MainWindow_Lable"));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu"));
        font.setPointSize(26);
        MainWindow_Lable->setFont(font);

        horizontalLayout->addWidget(MainWindow_Lable);


        verticalLayout->addWidget(MainWindow_UpperLayer);

        mainWindow_Tab = new QTabWidget(centralwidget);
        mainWindow_Tab->setObjectName(QString::fromUtf8("mainWindow_Tab"));
        MainWindow_Dashboard_Tab = new QWidget();
        MainWindow_Dashboard_Tab->setObjectName(QString::fromUtf8("MainWindow_Dashboard_Tab"));
        mainWindow_Tab->addTab(MainWindow_Dashboard_Tab, QString());
        MainWindow_Statistics_Tab = new QWidget();
        MainWindow_Statistics_Tab->setObjectName(QString::fromUtf8("MainWindow_Statistics_Tab"));
        verticalLayout_3 = new QVBoxLayout(MainWindow_Statistics_Tab);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        testTableView = new QTableView(MainWindow_Statistics_Tab);
        testTableView->setObjectName(QString::fromUtf8("testTableView"));

        verticalLayout_3->addWidget(testTableView);

        mainWindow_Tab->addTab(MainWindow_Statistics_Tab, QString());

        verticalLayout->addWidget(mainWindow_Tab);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 913, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        mainWindow_Tab->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        MainWindow_Lable->setText(QCoreApplication::translate("MainWindow", "Your Dashboard", nullptr));
        mainWindow_Tab->setTabText(mainWindow_Tab->indexOf(MainWindow_Dashboard_Tab), QCoreApplication::translate("MainWindow", "Dashboard", nullptr));
        mainWindow_Tab->setTabText(mainWindow_Tab->indexOf(MainWindow_Statistics_Tab), QCoreApplication::translate("MainWindow", "Statistics", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
