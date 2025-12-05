#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

bool Database::connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("studentsystem.db");

    if (!db.open()) {
        qDebug() << "DB Connection failed!";
        return false;
    }

    QSqlQuery q;

    q.exec("CREATE TABLE IF NOT EXISTS users ("
           "username TEXT PRIMARY KEY,"
           "password TEXT,"
           "role TEXT,"
           "student_id INTEGER)");

    q.exec("CREATE TABLE IF NOT EXISTS students ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "roll TEXT,"
           "name TEXT,"
           "department TEXT,"
           "year INTEGER,"
           "cgpa REAL,"
           "email TEXT,"
           "phone TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS requests ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "student_id INTEGER,"
           "message TEXT,"
           "status TEXT)");

    return true;
}
