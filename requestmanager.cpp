#include "requestmanager.h"
#include "database.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

bool RequestManager::createRequest(int studentId, const QString &msg) {
    if (!Database::connect()) return false;
    QSqlQuery q;
    q.prepare("INSERT INTO requests (student_id, message, resolved) VALUES (:sid, :msg, 0)");
    q.bindValue(":sid", studentId);
    q.bindValue(":msg", msg);
    if (!q.exec()) {
        qWarning() << "createRequest failed:" << q.lastError().text();
        return false;
    }
    return true;
}

QVector<QMap<QString, QString>> RequestManager::getStudentRequests(int studentId) {
    QVector<QMap<QString, QString>> list;
    if (!Database::connect()) return list;
    QSqlQuery q;
    q.prepare("SELECT id, student_id, message, resolved, created_at FROM requests WHERE student_id = :sid ORDER BY created_at DESC");
    q.bindValue(":sid", studentId);
    if (!q.exec()) {
        qWarning() << "getStudentRequests failed:" << q.lastError().text();
        return list;
    }
    while (q.next()) {
        QMap<QString, QString> m;
        m["id"] = q.value(0).toString();
        m["student_id"] = q.value(1).toString();
        m["message"] = q.value(2).toString();
        m["resolved"] = q.value(3).toString();
        m["created_at"] = q.value(4).toString();
        list.append(m);
    }
    return list;
}

QVector<QMap<QString, QString>> RequestManager::getAllRequests() {
    QVector<QMap<QString, QString>> list;
    if (!Database::connect()) return list;
    QSqlQuery q("SELECT r.id, r.student_id, r.message, r.resolved, r.created_at, s.name, s.roll FROM requests r LEFT JOIN students s ON r.student_id = s.id ORDER BY r.created_at DESC");
    if (!q.exec()) {
        qWarning() << "getAllRequests failed:" << q.lastError().text();
        return list;
    }
    while (q.next()) {
        QMap<QString, QString> m;
        m["id"] = q.value(0).toString();
        m["student_id"] = q.value(1).toString();
        m["message"] = q.value(2).toString();
        m["resolved"] = q.value(3).toString();
        m["created_at"] = q.value(4).toString();
        m["student_name"] = q.value(5).toString();
        m["student_roll"] = q.value(6).toString();
        list.append(m);
    }
    return list;
}

bool RequestManager::markResolved(int requestId) {
    if (!Database::connect()) return false;
    QSqlQuery q;
    q.prepare("UPDATE requests SET resolved = 1 WHERE id = :id");
    q.bindValue(":id", requestId);
    if (!q.exec()) {
        qWarning() << "markResolved failed:" << q.lastError().text();
        return false;
    }
    return true;
}
