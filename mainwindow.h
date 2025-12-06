#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QString &username,
                        const QString &role,
                        QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpenAdmin_clicked();
    void on_btnOpenStudent_clicked();

private:
    Ui::MainWindow *ui;
    QString username;
    QString role;
};

#endif // MAINWINDOW_H
