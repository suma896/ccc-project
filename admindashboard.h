#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QDialog>

namespace Ui {
class admindashboard;
}

class admindashboard : public QDialog
{
    Q_OBJECT

public:
    explicit admindashboard(QWidget *parent = nullptr);
    ~admindashboard();

private:
    Ui::admindashboard *ui;
};

#endif // ADMINDASHBOARD_H
