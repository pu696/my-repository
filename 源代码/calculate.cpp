#include "calculate.h"
#include <QDebug>

bool Calculate::exactMatch(const QRegularExpression &reg, const QChar &ch)
{
    QString s(ch);
    QRegularExpressionMatch match = reg.match(s);
    return match.hasMatch() && match.capturedStart() == 0 && match.capturedEnd() == s.length();
}

int Calculate::getPriority(const QChar &op)
{
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '(') return 0;
    return -1;
}

bool Calculate::checkExpr(const QString &expr)
{
    QRegularExpression regNum("[0-9]");
    QRegularExpression regOp("[+\\-*/()]");

    if (expr.isEmpty()) return false;
    if (exactMatch(regOp, expr.front()) && expr.front() != '(') return false;
    if (exactMatch(regOp, expr.back()) && expr.back() != ')') return false;

    std::stack<QChar> st;
    for (int i = 0; i < expr.size(); ++i) {
        QChar ch = expr[i];
        if (!exactMatch(regNum, ch) && !exactMatch(regOp, ch)) return false;

        if (ch == '(') st.push(ch);
        else if (ch == ')') {
            if (st.empty() || st.top() != '(') return false;
            st.pop();
        }
    }
    return st.empty();
}

std::vector<QString> Calculate::infixToPostfix(const QString &expr)
{
    std::vector<QString> postfix;
    std::stack<QChar> opStack;
    QString num;

    for (int i = 0; i < expr.size(); ++i) {
        QChar ch = expr[i];
        if (ch.isDigit()) {
            num += ch;
            if (i == expr.size() - 1 || !expr[i+1].isDigit()) {
                postfix.push_back(num);
                num.clear();
            }
        } else if (ch == '(') {
            opStack.push(ch);
        } else if (ch == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                postfix.push_back(QString(opStack.top()));
                opStack.pop();
            }
            opStack.pop();
        } else {
            while (!opStack.empty() && getPriority(opStack.top()) >= getPriority(ch)) {
                postfix.push_back(QString(opStack.top()));
                opStack.pop();
            }
            opStack.push(ch);
        }
    }
    while (!opStack.empty()) {
        postfix.push_back(QString(opStack.top()));
        opStack.pop();
    }
    return postfix;
}

int Calculate::calculatePostfix(const std::vector<QString> &postfix)
{
    std::stack<int> numStack;
    for (const QString &s : postfix) {
        if (s[0].isDigit()) {
            numStack.push(s.toInt());
        } else {
            int b = numStack.top(); numStack.pop();
            int a = numStack.top(); numStack.pop();
            if (s == "+") numStack.push(a + b);
            else if (s == "-") numStack.push(a - b);
            else if (s == "*") numStack.push(a * b);
            else if (s == "/") numStack.push(a / b);
        }
    }
    return numStack.top();
}
