#ifndef WIDGET_H
#define WIDGET_H

#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include "user.h"
#include "questionbank.h"
#include "record.h"
#include "calculate.h"

namespace Ui {
class widget;
}

class widget : public QMainWindow
{
    Q_OBJECT


public:
    explicit widget(QWidget *parent = nullptr);
    ~widget();

private slots:
    void on_loginBtn_clicked(); // 登录按钮
    void on_generateBtn_clicked(); // 生成题库（管理员）
    void on_startBtn_clicked(); // 开始答题
    void on_submitBtn_clicked(); // 提交答卷
    void updateTimer(); // 计时更新

private:
    Ui::widget *ui;
    QVector<QString> m_questions;
    QVector<int> m_answers;
    QTimer *m_timer;
    QTime m_time;
    QString m_currentUser;
    UserType m_userType;
};

#endif
