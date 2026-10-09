#ifndef USER_H
#define USER_H

#include <QString>
#include <QFile>
#include <QTextStream>

enum UserType { NormalUser, AdminUser };

class User
{
public:
    User();
    static bool login(const QString &username, const QString &pwd, UserType &type); // 登录验证
    static bool isAdmin(const QString &username); // 判断是否为管理员
private:
    static QString m_adminPwd; // 管理员密码（初始：admin123）
    UserType m_userType;
};

#endif
