#include "mainwindow.h"
#include <QFile>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QFile styleSheetFile("E:\\Jensen's Laptop\\Library\\Downloads\\QStyleSheet-master\\QStyleSheet-master\\materialStyle\\materialStyle.css");
//    styleSheetFile.open(QFile::ReadOnly);
//    QString styleSheet = QLatin1String(styleSheetFile.readAll());
//    a.setStyleSheet(styleSheet);

    MainWindow w;
    w.show();
    return a.exec();
}
