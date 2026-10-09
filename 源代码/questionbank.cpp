#include "questionbank.h"

void QuestionBank::generateQuestions(int n)
{
    QFile file("questionbank.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) return;

    QTextStream out(&file);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(30, 99); // 20<n<100

    int count = dis(gen);
    for (int i = 0; i < count; ++i) {
        QString expr = generateExpr();
        while (!Calculate::checkExpr(expr)) {
            expr = generateExpr();
        }
        auto postfix = Calculate::infixToPostfix(expr);
        int ans = Calculate::calculatePostfix(postfix);
        out << expr << "=" << ans << "\n";
    }
    file.close();
}

QVector<QString> QuestionBank::loadQuestions()
{
    QVector<QString> questions;
    QFile file("questionbank.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return questions;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        questions.append(line.split("=")[0]);
    }
    file.close();
    return questions;
}

QString QuestionBank::generateExpr()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> numDis(1, 99);
    std::uniform_int_distribution<> opDis(0, 3);

    QString expr;
    int len = std::uniform_int_distribution<>(3, 7)(gen); // 表达式长度3-7
    bool hasBracket = std::uniform_int_distribution<>(0, 1)(gen);

    if (hasBracket) {
        expr += "(";
        expr += QString::number(numDis(gen));
        expr += getRandomOp();
        expr += QString::number(numDis(gen));
        expr += ")";
    } else {
        expr += QString::number(numDis(gen));
    }

    for (int i = 0; i < len - (hasBracket ? 3 : 1); ++i) {
        expr += getRandomOp();
        expr += QString::number(numDis(gen));
    }
    return expr;
}

QChar QuestionBank::getRandomOp()
{
    QVector<QChar> ops = {'+', '-', '*', '/'};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 3);
    return ops[dis(gen)];
}
