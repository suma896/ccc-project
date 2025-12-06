#include "studentdashboard.h"
#include "ui_studentdashboard.h"
#include "studentmanager.h"
#include "requestmanager.h"

#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTextEdit>      // >>> IMPORTANT FIX <<<

StudentDashboard::StudentDashboard(int studentId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudentDashboard),
    id(studentId)
{
    ui->setupUi(this);

    loadProfile();
    loadRequests();

    // Connect submit button safely
    if (auto btn = this->findChild<QPushButton*>("btnSubmit")) {
        connect(btn, &QPushButton::clicked, this, &StudentDashboard::on_btnSubmit_clicked);
    }
}

StudentDashboard::~StudentDashboard()
{
    delete ui;
}

static QLineEdit* findLE(QWidget *w, const QStringList &names) {
    for (const auto &n : names) {
        auto le = w->findChild<QLineEdit*>(n);
        if (le) return le;
    }
    return nullptr;
}

void StudentDashboard::loadProfile()
{
    if (id <= 0) {
        qDebug() << "Invalid student ID — loadProfile skipped";
        return;
    }

    auto map = StudentManager::getStudent(id);
    if (map.isEmpty()) return;

    auto trySet = [&](const QStringList &names, const QString &val){
        for (auto &n : names) {
            if (auto lbl = this->findChild<QLabel*>(n)) {
                lbl->setText(val);
                return true;
            }
            if (auto le = this->findChild<QLineEdit*>(n)) {
                le->setText(val);
                return true;
            }
        }
        return false;
    };

    trySet({"lblRoll","edtRoll","lineEditRoll"}, map.value("roll"));
    trySet({"lblName","edtName","lineEditName"}, map.value("name"));
    trySet({"lblDept","edtDept","lineEditDept"}, map.value("department"));
    trySet({"lblYear","edtYear","lineEditYear"}, map.value("year"));
    trySet({"lblEmail","edtEmail","lineEditEmail"}, map.value("email"));
    trySet({"lblPhone","edtPhone","lineEditPhone"}, map.value("phone"));
    trySet({"lblCgpa","edtCgpa","lineEditCgpa"}, map.value("cgpa"));
}

void StudentDashboard::loadRequests()
{
    if (id <= 0) return;

    auto list = RequestManager::getStudentRequests(id);

    QTableWidget *tbl =
        this->findChild<QTableWidget*>("tblRequests") ?
            this->findChild<QTableWidget*>("tblRequests") :
            this->findChild<QTableWidget*>("tableWidgetRequests");

    if (!tbl) return;

    tbl->clear();
    tbl->setColumnCount(3);
    tbl->setHorizontalHeaderLabels({"ID", "Message", "Resolved"});
    tbl->setRowCount(list.size());

    for (int i = 0; i < list.size(); i++) {
        auto &m = list[i];
        tbl->setItem(i, 0, new QTableWidgetItem(m.value("id")));
        tbl->setItem(i, 1, new QTableWidgetItem(m.value("message")));
        tbl->setItem(i, 2, new QTableWidgetItem(m.value("resolved") == "1" ? "Yes" : "No"));
    }
}

void StudentDashboard::on_btnSubmit_clicked()
{
    QString msg;

    // Priority: QLineEdit → QPlainTextEdit → QTextEdit
    if (auto le = this->findChild<QLineEdit*>("txtRequest"))
        msg = le->text().trimmed();

    else if (auto le = this->findChild<QLineEdit*>("lineEditRequest"))
        msg = le->text().trimmed();

    else if (auto pte = this->findChild<QPlainTextEdit*>("txtRequestPlain"))
        msg = pte->toPlainText().trimmed();

    else if (auto te = this->findChild<QTextEdit*>("txtRequestPlain"))
        msg = te->toPlainText().trimmed();

    if (msg.isEmpty()) {
        QMessageBox::warning(this, "Request", "Enter request message.");
        return;
    }

    if (id <= 0) {
        QMessageBox::warning(this, "Request", "Student ID unknown.");
        return;
    }

    if (!RequestManager::createRequest(id, msg)) {
        QMessageBox::warning(this, "Request", "Failed to submit request.");
        return;
    }

    QMessageBox::information(this, "Request", "Request submitted successfully!");

    loadRequests();

    // Clear all possible input fields
    if (auto le = this->findChild<QLineEdit*>("txtRequest")) le->clear();
    if (auto le = this->findChild<QLineEdit*>("lineEditRequest")) le->clear();
    if (auto pte = this->findChild<QPlainTextEdit*>("txtRequestPlain")) pte->clear();
    if (auto te = this->findChild<QTextEdit*>("txtRequestPlain")) te->clear();
}
