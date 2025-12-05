#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "admindashboard.h"
#include "studentdashboard.h"
#include "authmanager.h"

MainWindow::MainWindow(const QString &u, const QString &r, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    username = u;
    role = r;

    ui->lblWelcome->setText("Welcome, " + username);

    if (role == "admin") {
        ui->btnOpenStudent->setEnabled(false);
    } else {
        ui->btnOpenAdmin->setEnabled(false);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpenAdmin_clicked()
{
    AdminDashboard *ad = new AdminDashboard();
    ad->show();
}

void MainWindow::on_btnOpenStudent_clicked()
{
    int id = AuthManager::getStudentId(username);
    StudentDashboard *sd = new StudentDashboard(id);
    sd->show();
}
