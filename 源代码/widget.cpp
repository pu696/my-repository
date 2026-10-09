#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

widget::widget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::widget)
    , m_timer(new QTimer(this))
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);
    this->setWindowTitle("小学生四则运算测试系统");

    // 初始化控件状态
    ui->stackedWidget->setCurrentIndex(0); // 显示登录页
    ui->generateBtn->setEnabled(false);
    ui->startBtn->setEnabled(false);
    ui->submitBtn->setEnabled(false);

    connect(m_timer, &QTimer::timeout, this, &widget::updateTimer);
}

widget::~widget()
{
    delete ui;
}

void widget::on_loginBtn_clicked()
{
    QString username = ui->userEdit->text();
    QString pwd = ui->pwdEdit->text();
    UserType type;

    if (User::login(username, pwd, type)) {
        m_currentUser = username;
        m_userType = type;
        ui->stackedWidget->setCurrentIndex(1); // 显示主界面
        ui->userLabel->setText("当前用户：" + username);
        if (type == AdminUser) {
            ui->generateBtn->setEnabled(true);
        }
        ui->startBtn->setEnabled(true);
        QMessageBox::information(this, "登录成功", "欢迎使用四则运算测试系统！");
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
    }
}

void widget::on_generateBtn_clicked()
{
    QuestionBank::generateQuestions(50); // 随机生成30-99题
    QMessageBox::information(this, "生成成功", "题库已生成（questionbank.txt）！");
    ui->startBtn->setEnabled(true);
}

void widget::on_startBtn_clicked()
{
    m_questions = QuestionBank::loadQuestions();
    if (m_questions.isEmpty()) {
        QMessageBox::warning(this, "错误", "请先生成题库！");
        return;
    }

    // 加载题目
    ui->questionEdit->clear();
    for (int i = 0; i < m_questions.size(); ++i) {
        ui->questionEdit->append(QString("%1. %2 = ").arg(i+1).arg(m_questions[i]));
    }

    // 初始化计时
    m_time = QTime(0, 0, 0);
    m_timer->start(1000);
    ui->timeLabel->setText("答题时间：00:00:00");
    ui->submitBtn->setEnabled(true);
    ui->startBtn->setEnabled(false);
}

void widget::on_submitBtn_clicked()
{
    m_timer->stop();
    QString answerText = ui->answerEdit->toPlainText();
    QStringList answers = answerText.split("\n");

    int score = 0;
    for (int i = 0; i < m_questions.size() && i < answers.size(); ++i) {
        auto postfix = Calculate::infixToPostfix(m_questions[i]);
        int correct = Calculate::calculatePostfix(postfix);
        int userAns = answers[i].toInt();
        if (userAns == correct) score++;
    }

    // 保存记录
    RecordManager::saveRecord(m_currentUser, score, m_questions.size());
    auto history = RecordManager::loadRecords(m_currentUser);
    QString eval = RecordManager::getEvaluation(score, m_questions.size(), history);

    // 显示结果
    QMessageBox::information(this, "答题结果",
                             QString("总题数：%1\n答对：%2\n得分：%3\n%4\n用时：%5")
                                 .arg(m_questions.size()).arg(score).arg(score * 100 / m_questions.size())
                                 .arg(eval).arg(m_time.toString("hh:mm:ss")));

    // 重置状态
    ui->startBtn->setEnabled(true);
    ui->submitBtn->setEnabled(false);
    ui->answerEdit->clear();
}

void widget::updateTimer()
{
    m_time = m_time.addSecs(1);
    ui->timeLabel->setText("答题时间：" + m_time.toString("hh:mm:ss"));
}
