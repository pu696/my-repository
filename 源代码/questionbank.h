#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <random>
#include "calculate.h"

class QuestionBank
{
public:
    static void generateQuestions(int n); // 生成n道题目
    static QVector<QString> loadQuestions(); // 加载题库
private:
    static QString generateExpr(); // 生成单个表达式
    static QChar getRandomOp(); // 随机生成运算符
};

#endif
