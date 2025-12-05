#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "database.h"
#include "authmanager.h"
#include "mainwindow.h"

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    Database::connect();
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnLogin_clicked()
{
    QString uname = ui->txtUsername->text();
    QString pass = ui->txtPassword->text();

    QString role = AuthManager::login(uname, pass);

    if (role == "") {
        ui->lblMessage->setText("Invalid username or password!");
        return;
    }

    MainWindow *mw = new MainWindow(uname, role);
    mw->show();
    this->close();
}
