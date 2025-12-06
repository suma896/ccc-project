#ifndef ADMINDASHBOARD_H
#define ADMINDASHBOARD_H

#include <QWidget>
#include <QMap>

class StudentManager;
class RequestManager;

namespace Ui {
class AdminDashboard;
}

class AdminDashboard : public QWidget
{
    Q_OBJECT

public:
    explicit AdminDashboard(QWidget *parent = nullptr);
    ~AdminDashboard();

private slots:
    void on_btnSearch_clicked();
    void on_btnAdd_clicked();
    void on_btnUpdate_clicked();
    void on_btnDelete_clicked();
    void on_btnResolved_clicked();
    void loadRequests();

private:
    Ui::AdminDashboard *ui;

    StudentManager *studentManager;
    RequestManager *requestManager;

    void clearFields();
};

#endif // ADMINDASHBOARD_H
