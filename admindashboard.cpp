#include "admindashboard.h"
#include "ui_admindashboard.h"

admindashboard::admindashboard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::admindashboard)
{
    ui->setupUi(this);
}

admindashboard::~admindashboard()
{
    delete ui;
}
