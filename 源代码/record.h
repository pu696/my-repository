#ifndef RECORD_H
#define RECORD_H

#include <QString>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDateTime>

struct Record {
    QString username;
    QDateTime time;
    int score;
    int total;
};

class RecordManager
{
public:
    static void saveRecord(const QString &username, int score, int total); // 保存答卷
    static QVector<Record> loadRecords(const QString &username); // 加载用户记录
    static QString getEvaluation(int score, int total, const QVector<Record> &history); // 评价
};

#endif
