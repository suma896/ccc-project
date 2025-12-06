#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "admindashboard.h"
#include "studentdashboard.h"
#include "authmanager.h"

#include <QPushButton>
#include <QDebug>

MainWindow::MainWindow(const QString &username, const QString &role, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , username(username)
    , role(role)
{
    ui->setupUi(this);

    // Hide admin button for non-admin users
    if (role != "admin") {
        if (auto btn = this->findChild<QPushButton*>("btnOpenAdmin"))
            btn->setVisible(false);
    }

    // Connect buttons safely
    if (auto btnA = this->findChild<QPushButton*>("btnOpenAdmin"))
        connect(btnA, &QPushButton::clicked, this, &MainWindow::on_btnOpenAdmin_clicked);

    if (auto btnS = this->findChild<QPushButton*>("btnOpenStudent"))
        connect(btnS, &QPushButton::clicked, this, &MainWindow::on_btnOpenStudent_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnOpenAdmin_clicked()
{
    if (role != "admin") return;

    AdminDashboard *adm = new AdminDashboard();
    adm->setAttribute(Qt::WA_DeleteOnClose);
    adm->show();
}

void MainWindow::on_btnOpenStudent_clicked()
{
    int sid = AuthManager::getStudentId(username);

    StudentDashboard *sd = new StudentDashboard(sid);
    sd->setAttribute(Qt::WA_DeleteOnClose);
    sd->show();
}
