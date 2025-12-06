#include "authmanager.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

QString AuthManager::login(const QString &username, const QString &password) {
    // Ensure DB is connected
    if (!Database::connect()) {
        qWarning() << "DB not connected in login";
        return QString();
    }

    // Use the default connection (same one created in Database::connect)
    QSqlQuery q;
    q.prepare("SELECT role FROM users WHERE username = :u AND password = :p LIMIT 1");
    q.bindValue(":u", username);
    q.bindValue(":p", password);
    if (!q.exec()) {
        qWarning() << "Login query failed:" << q.lastError().text();
        return QString();
    }
    if (q.next()) {
        return q.value(0).toString();
    }
    return QString();
}

int AuthManager::getStudentId(const QString &username) {
    if (!Database::connect()) {
        qWarning() << "DB not connected in getStudentId";
        return -1;
    }

    // First try to read the student_id field from users table (preferred)
    QSqlQuery q;
    q.prepare("SELECT student_id FROM users WHERE username = :u LIMIT 1");
    q.bindValue(":u", username);
    if (q.exec() && q.next()) {
        QVariant v = q.value(0);
        if (!v.isNull()) return v.toInt();
    }

    // Fallback: try to match username with students.roll or students.email
    q.prepare("SELECT id FROM students WHERE roll = :u LIMIT 1");
    q.bindValue(":u", username);
    if (q.exec() && q.next()) {
        return q.value(0).toInt();
    }

    q.prepare("SELECT id FROM students WHERE email LIKE :e LIMIT 1");
    q.bindValue(":e", QString("%%1%").arg(username)); // contains username
    if (q.exec() && q.next()) {
        return q.value(0).toInt();
    }

    return -1;
}
