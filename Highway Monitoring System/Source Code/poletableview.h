#ifndef POLETABLEVIEW_H
#define POLETABLEVIEW_H

#include <QDialog>

namespace Ui {
class PoleTableView;
}

class PoleTableView : public QDialog
{
    Q_OBJECT

public:
    explicit PoleTableView(QWidget *parent = nullptr);
    ~PoleTableView();

private:
    Ui::PoleTableView *ui;
};

#endif // POLETABLEVIEW_H
