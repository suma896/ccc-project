#include "authmanager.h"
#include <QSqlQuery>

QString AuthManager::login(const QString &username, const QString &password)
{
    QSqlQuery q;
    q.prepare("SELECT role FROM users WHERE username=? AND password=?");
    q.addBindValue(username);
    q.addBindValue(password);
    q.exec();

    if (q.next())
        return q.value(0).toString();

    return "";
}

int AuthManager::getStudentId(const QString &username)
{
    QSqlQuery q;
    q.prepare("SELECT student_id FROM users WHERE username=?");
    q.addBindValue(username);
    q.exec();

    if (q.next())
        return q.value(0).toInt();

    return -1;
}
