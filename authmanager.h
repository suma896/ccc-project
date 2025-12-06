#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>

class AuthManager {
public:
    // Returns role string ("admin" or "student") or empty QString when auth fails
    static QString login(const QString &username, const QString &password);

    // Returns linked student id for a username (from users.student_id) or -1 if none
    static int getStudentId(const QString &username);
};

#endif // AUTHMANAGER_H
