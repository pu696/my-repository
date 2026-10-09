#ifndef CALCULATE_H
#define CALCULATE_H

#include <QString>
#include <QRegularExpression>
#include <stack>
#include <vector>

class Calculate
{
public:
    static bool checkExpr(const QString &expr); // 表达式正确性验证
    static int calculatePostfix(const std::vector<QString> &postfix); // 后缀式计算
    static std::vector<QString> infixToPostfix(const QString &expr); // 中缀转后缀
private:
    static bool exactMatch(const QRegularExpression &reg, const QChar &ch); // 正则精确匹配
    static int getPriority(const QChar &op); // 运算符优先级
};

#endif
