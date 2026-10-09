#include "user.h"

QString User::m_adminPwd = "admin123";

User::User() : m_userType(NormalUser) {}

bool User::login(const QString &username, const QString &pwd, UserType &type)
{
    QFile file("users.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // 初始化用户文件
        file.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&file);
        out << "admin " << m_adminPwd << " admin\n";
        out << "student1 123456 normal\n";
        file.close();
        file.open(QIODevice::ReadOnly | QIODevice::Text);
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts[0] == username && parts[1] == pwd) {
            type = (parts[2] == "admin") ? AdminUser : NormalUser;
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool User::isAdmin(const QString &username)
{
    return username == "admin";
}
