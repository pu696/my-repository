#include "record.h"

void RecordManager::saveRecord(const QString &username, int score, int total)
{
    QFile file("records.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) return;

    QTextStream out(&file);
    out << username << " " << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << " " << score << " " << total << "\n";
    file.close();
}

QVector<Record> RecordManager::loadRecords(const QString &username)
{
    QVector<Record> records;
    QFile file("records.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return records;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts[0] == username) {
            Record r;
            r.username = parts[0];
            r.time = QDateTime::fromString(parts[1] + " " + parts[2], "yyyy-MM-dd hh:mm:ss");
            r.score = parts[3].toInt();
            r.total = parts[4].toInt();
            records.append(r);
        }
    }
    file.close();
    return records;
}

QString RecordManager::getEvaluation(int score, int total, const QVector<Record> &history)
{
    double rate = (double)score / total;
    if (history.isEmpty()) {
        if (rate >= 0.9) return "首次答题，表现优秀！";
        else if (rate >= 0.7) return "首次答题，表现良好！";
        else return "首次答题，继续努力！";
    }

    double avg = 0;
    for (const Record &r : history) avg += (double)r.score / r.total;
    avg /= history.size();

    if (rate > avg) return "比历史平均水平优秀，继续保持！";
    else if (rate == avg) return "与历史平均水平持平，加油！";
    else return "略低于历史平均水平，再努力！";
}
