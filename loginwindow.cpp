#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "authmanager.h"
#include "mainwindow.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QDebug>

LoginWindow::LoginWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // Ensure password field hides text
    if (auto pwd = this->findChild<QLineEdit*>("txtPassword"))
        pwd->setEchoMode(QLineEdit::Password);

    // Connect button if UI uses btnLogin
    if (ui->btnLogin)
        connect(ui->btnLogin, &QPushButton::clicked, this, &LoginWindow::on_btnLogin_clicked);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_btnLogin_clicked()
{
    // Read username + password
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text().trimmed();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please enter both username and password.");
        return;
    }

    // Authenticate using AuthManager
    QString role = AuthManager::login(username, password);

    if (role.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
        return;
    }

    // Open main window
    MainWindow *mw = new MainWindow(username, role);
    mw->show();

    // Close login window
    this->close();
}
