#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <QString>

class AuthManager {
public:
    static QString login(const QString &username, const QString &password);
    static int getStudentId(const QString &username);
};

#endif // AUTHMANAGER_H
