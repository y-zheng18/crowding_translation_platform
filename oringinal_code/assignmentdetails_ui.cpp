#include "assignmentdetails_ui.h"
#include "ui_assignmentdetails_ui.h"
#include <QGraphicsDropShadowEffect>
#include "database.h"
#include "usermessage_ui.h"
#include "m_QInformbox.h"
#include <QFileDialog>
#include <QTextStream>

/*************************************************************************
【函数名称】        AssignmentDetails_ui
【函数功能】        展示任务详细属性
【参数】
【返回值】
【开发者及日期】     7/30
*************************************************************************/
AssignmentDetails_ui::AssignmentDetails_ui(User& u, Assignment& a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssignmentDetails_ui),
    m_assignment(a),
    m_User(u)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(800, 1000));
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);

    QString key = "";
    for (int i = 0;i < m_assignment.getKeywords().size();i++)
    {
        key += m_assignment.getKeywords()[i];
        key += " ";
    }
    ui->labelkey1->setText(key);
    ui->labelMoney->setText(QString("%1 yuan").arg(m_assignment.getReward()));
    ui->labelNameShow->setText(m_assignment.getName());
    ui->textDescription->setText(m_assignment.getDescription());
    ui->btnPublisher->setText(User(m_assignment.getPublisherID()).getUserName());
    ui->btnManager->setText(User(m_assignment.getManagerID()).getUserName());
    int n = m_assignment.getTranslaors().size();
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(n);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    if (m_assignment.getTranslationForm() == ENGLISH_TO_CHINESE)
    {
        ui->labelLanguage->setText("英译汉");
    }
    else if (m_assignment.getTranslationForm() == CHINESE_TO_ENGLISH)
    {
        ui->labelLanguage->setText("汉译英");
    }
    for (int i = 0;i < n;i++)
    {
        User trans(m_assignment.getTranslaors()[i]);

        QLabel* label = new QLabel;
        label->setText(trans.getUserName());
        //btn->setStyleSheet("QPushButton{background-color: rgba(255, 255, 255, 0)}");
        ui->tableWidget->setCellWidget(i, 0, label);
        //connect(btn, SIGNAL(clicked()), this, SLOT(on_on_btnUser_clicked(trans.getID())));
    }
    STATUS s = STATUS(m_assignment.getStatus());
    if (s == RECRUITING_MANAGER)
    {
        ui->labelStatus->setText("负责人招募中");
        ui->btnSignUp->setText("负责人报名");
        ui->btnSignUp->setEnabled(true);
        ui->labelfinalDDL->setText("总任务截至日期：");
        ui->labelDDL_FINAL->setText(m_assignment.get_deadline().toString());
        ui->labelCurrentDDL->setText("报名截止日期：");
        ui->labelDDL_CUR->setText(m_assignment.get_currentDDL().toString());
    }
    else if (s == MANAGER_RECUIT_DONE)
    {
        ui->labelStatus->setText("负责人招募完成");
        ui->btnSignUp->setText("不可报名");
        ui->btnSignUp->setEnabled(false);
        ui->labelfinalDDL->setText("总任务截至日期：");
        ui->labelDDL_FINAL->setText(m_assignment.get_deadline().toString());
        ui->labelCurrentDDL->hide();
        ui->labelDDL_CUR->hide();
    }
    else if (s == RECRUITING_TRANSLATOR)
    {
        ui->labelM->setText("译者总酬金");
        float money = m_assignment.getReward() * 3 / 4;
        ui->labelMoney->setText(QString("%1yuan").arg(money));
        ui->labelStatus->setText("译者招募中");
        ui->btnSignUp->setText("译者报名");
        ui->btnSignUp->setEnabled(true);
        ui->labelfinalDDL->setText("总任务截至日期：");
        ui->labelDDL_FINAL->setText(m_assignment.get_deadline().toString());
        ui->labelCurrentDDL->setText("报名截止日期：");
        ui->labelDDL_CUR->setText(m_assignment.get_currentDDL().toString());
    }
    else if (s == PROCCESSING)
    {
        ui->labelStatus->setText("翻译进行中");
        ui->btnSignUp->setText("审稿人报名");
        ui->btnSignUp->setEnabled(true);
        ui->labelfinalDDL->setText("翻译任务截至日期：");
        ui->labelDDL_FINAL->setText(m_assignment.get_currentDDL().toString());
        ui->labelCurrentDDL->hide();
        ui->labelDDL_CUR->hide();
    }
    else if (s == ASSIGNMENT_DONE)
    {
        ui->labelStatus->setText("任务已完成");
        ui->btnSignUp->setText("不可报名");
        ui->btnSignUp->setEnabled(false);
        ui->labelfinalDDL->setText("任务截至日期：");
        ui->labelDDL_FINAL->setText(m_assignment.get_deadline().toString());
        ui->labelCurrentDDL->hide();
        ui->labelDDL_CUR->hide();
    }
    ui->labelPicture->setText(m_assignment.getName());
    QPixmap pix = m_assignment.getPix();
    if (!pix.isNull())
    {
        pix.scaled(ui->labelPicture->size(), Qt::KeepAspectRatio);
        ui->labelPicture->setScaledContents(true);
        ui->labelPicture->setPixmap(pix);
    }
    if (m_User.getID() == a.getPublisherID())
    {
        ui->btnSignUp->setText("查看并编辑信息");
        ui->btnSignUp->setEnabled(true);
    }
    if (m_User.getID() == a.getPublisherID() && m_assignment.getStatus() == ASSIGNMENT_DONE)
    {
        ui->btnSignUp->setText("任务完成，支付定金");
        ui->btnSignUp->setEnabled(true);
        ui->btndownload->setText("下载译文");
    }
}

AssignmentDetails_ui::~AssignmentDetails_ui()
{
    delete ui;
}

void AssignmentDetails_ui::setAssignment(const Assignment& assignment)
{
    m_assignment = assignment;
}

void AssignmentDetails_ui::on_btnClose_clicked()
{
    this->hide();
}

void AssignmentDetails_ui::on_btnSignUp_clicked()
{
    QString m_sUserId = m_User.getID();
    if (m_sUserId == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    if (m_User.getID() == m_assignment.getPublisherID())
    {
        if (m_assignment.getStatus() == ASSIGNMENT_DONE)
        {
            m_User.setMoney(m_User.getMoney() - m_assignment.getReward());
            AssignmentPublisher asP(m_assignment.getName());
            if (asP.payReward() > 0)
            {
                AssignmentManager asM(m_assignment.getName());
                asM.payReward();
                m_QInformBox::information(this, "提示", "支付成功！");
                ui->btndownload->setEnabled(true);
                ui->btnSignUp->setEnabled(false);
            }
            else {
                m_QInformBox::information(this, "提示", "余额不足，支付失败！");
            }
        }
        else if (m_assignment.getStatus() != RECRUITING_MANAGER)
        {
            m_QInformBox::warning(this, "提示", "已选择负责人，不可更改任务信息！");
        }
    }
    else {
        DataBaseAssignment db;
        if (m_assignment.getStatus() == RECRUITING_MANAGER)
        {
            if (m_assignment.get_currentDDL() < QDateTime::currentDateTime())
            {
                 QMessageBox::warning(this, "提示", "报名时间已过！");
                 return;
            }
            db.setTableName("managerSignUp");
            if (db.searchAssignment(m_sUserId, m_assignment.getName(), "candidateID"))
            {
                QMessageBox::warning(this, "提示", "您已报名，请勿重复报名！");
                ui->btnSignUp->setText("已报名");
                ui->btnSignUp->setEnabled(false);
                return;
            }
            if (m_User.getScore() < 20)
            {
                m_QInformBox::warning(this, "提示", "您的积分不足！无法成为负责人！");
                return;
            }
            m_User.signUpForManager(m_assignment.getName());
            QMessageBox::information(this, "提示", "负责人报名成功！");
            ui->btnSignUp->setText("已报名");
            ui->btnSignUp->setEnabled(false);
            return;
        }
        if (m_assignment.getStatus() == RECRUITING_TRANSLATOR)
        {
            if (m_assignment.get_currentDDL() < QDateTime::currentDateTime())
            {
                 QMessageBox::warning(this, "提示", "报名时间已过！");
                 return;
            }
            db.setTableName("translatorSignUp");
            if (db.searchAssignment(m_sUserId, m_assignment.getName(), "candidateID"))
            {
                QMessageBox::warning(this, "提示", "您已报名，请勿重复报名！");
                ui->btnSignUp->setText("已报名");
                ui->btnSignUp->setEnabled(false);
                return;
            }
            m_User.signUpForTran(m_assignment.getName());
            QMessageBox::information(this, "", "译者报名成功！");
            ui->btnSignUp->setText("已报名");
            ui->btnSignUp->setEnabled(false);
            return;
        }

    }
}

void AssignmentDetails_ui::on_btnPublisher_clicked()
{
    DataBaseUser db;
    User u = db.getUserByName( ui->btnPublisher->text());
    userMessage_ui user_ui(u);
    user_ui.exec();
}

void AssignmentDetails_ui::on_btnManager_clicked()
{
    DataBaseUser db;
    User u = db.getUserByName( ui->btnManager->text());
    userMessage_ui user_ui(u);
    user_ui.exec();
}

void AssignmentDetails_ui::on_btndownload_clicked()
{

    QString filePath = QFileDialog::getSaveFileName(this,tr("Open File"),"/home",tr("Text File(*.txt)"));
    if (filePath.isEmpty())
        return;
    QFile aFile(filePath);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream aStream(&aFile); //用文本流读取文件
    QString str=m_assignment.getText(); //转换为字符串
    if (m_User.getID() == m_assignment.getPublisherID() && m_assignment.getStatus() == ASSIGNMENT_DONE)
    {
        AssignmentPublisher asP(m_assignment.getName());
        str = asP.getFinalTranslation();
    }
    aStream<<str; //写入文本流
    aFile.close();//关闭文件
    m_QInformBox::information(this, "提示", "保存成功！");
    return;
}
