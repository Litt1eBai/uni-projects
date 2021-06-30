#ifndef WHEREAREYOUWIDGET_H
#define WHEREAREYOUWIDGET_H

#include <QWidget>

namespace Ui {
class WhereAreYouWidget;
}

class WhereAreYouWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WhereAreYouWidget(QWidget *parent = nullptr);
    ~WhereAreYouWidget();

    void initialise();

private:
    Ui::WhereAreYouWidget *ui;
};

#endif // WHEREAREYOUWIDGET_H
