#include "database.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool Database::connect() {
    // Use default unnamed connection
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        QSqlDatabase db = QSqlDatabase::database();
        if (db.isOpen()) return true;
    }

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("students.db");

    if (!db.open()) {
        qWarning() << "Cannot open database:" << db.lastError().text();
        return false;
    }

    QSqlQuery q;

    q.exec("CREATE TABLE IF NOT EXISTS users ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "username TEXT UNIQUE,"
           "password TEXT,"
           "role TEXT,"
           "student_id INTEGER)");

    q.exec("CREATE TABLE IF NOT EXISTS students ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "roll TEXT UNIQUE,"
           "name TEXT,"
           "department TEXT,"
           "year TEXT,"
           "email TEXT,"
           "phone TEXT,"
           "cgpa TEXT)");

    q.exec("CREATE TABLE IF NOT EXISTS requests ("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "student_id INTEGER,"
           "message TEXT,"
           "resolved INTEGER DEFAULT 0)");

    // Insert default admin
    q.exec("INSERT OR IGNORE INTO users (username, password, role)"
           "VALUES ('Ravi','Ravi123','admin')");

    return true;
}
