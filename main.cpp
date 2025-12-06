#include <QApplication>
#include "loginwindow.h"
#include "database.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // initialize DB
    if (!Database::connect()) {
        qWarning() << "Failed to connect to DB -- application continues but DB will not work.";
    }

    LoginWindow w;
    w.show();

    return a.exec();
}
