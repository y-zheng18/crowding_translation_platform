#include "choosetrans_ui.h"
#include "ui_choosetrans_ui.h"
#include "usermessage_ui.h"
#include "database.h"
#include"m_QInformbox.h"
#include <QTime>
#include "review_ui.h"
#include "QGraphicsDropShadowEffect"
/*************************************************************************
【函数名称】        chooseTrans_ui
【函数功能】        展示译者报名情况、选择译者
【参数】           任务、User引用
【返回值】
【开发者及日期】     7/31
*************************************************************************/
chooseTrans_ui::chooseTrans_ui(User &u, AssignmentManager& a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseTrans_ui),
    m_user(u),
    m_asManager(a)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(800, 900));
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(m_asManager.getTranSignUp().size());
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    ui->dateEditCurrent->setDate(QDate::currentDate());
    ui->timeEditCurrent->setTime(QTime::currentTime());
    if ( m_asManager.getTranSignUp().size() == 0)
    {
        ui->comboBox->hide();
        ui->btnChoose->hide();
        ui->label->setText("暂无报名");
    }
    for (int i = 0;i < m_asManager.getTranSignUp().size();i++)
    {
        User u(m_asManager.getTranSignUp()[i].getCandidate());
        userMessage_ui * aShow = new userMessage_ui(u, ui->tableWidget);
        aShow->setFixedSize(650, 500);
        ui->tableWidget->setColumnWidth(0, 650);
        ui->tableWidget->setRowHeight(i, 500);
        ui->tableWidget->setCellWidget(i, 0, aShow);
        aShow->show();
        ui->comboBox->addItem(u.getUserName());
    }
    if (m_asManager.getStatus() == PROCCESSING)
    {
        ui->btnChoose->setEnabled(false);
        ui->btnChooseTime->hide();
        ui->btnOK->setEnabled(false);
        ui->btnOK->setText("您已选择译者！");
        ui->dateEditCurrent->hide();
        ui->timeEditCurrent->hide();
        ui->labelDDL->hide();
    }
    else if (QDateTime::currentDateTime() < m_asManager.get_currentDDL())
    {
        ui->btnChoose->setEnabled(false);
        ui->btnChooseTime->hide();
        ui->btnOK->setEnabled(false);
        ui->btnOK->setText("报名截至时间未到！");
        ui->dateEditCurrent->hide();
        ui->timeEditCurrent->hide();
        ui->labelDDL->hide();
    }
}

chooseTrans_ui::~chooseTrans_ui()
{
    delete ui;
}

void chooseTrans_ui::on_btnCancel_clicked()
{
    this->reject();
}

void chooseTrans_ui::on_btnOK_clicked()
{
    QDate d = ui->dateEditCurrent->date();
    QTime t = ui->timeEditCurrent->time();
    QDateTime dt;
    dt.setDate(d);
    dt.setTime(t);
    if (dt < QDateTime::currentDateTime())
    {
        m_QInformBox::warning(this, "提示", QString("截至日期不能在当下时间前！"));
        return;
    }
    if (dt > m_asManager.get_deadline())
    {
        m_QInformBox::warning(this, "提示", QString("截至日期不能在总任务截止日期前！"));
        return;
    }
    m_asManager.setDDL(dt);
    m_QInformBox::information(this, "提示", "请分配任务！");
    Review_ui* allocate = new Review_ui(m_user, m_asManager);
    allocate->exec();
    this->accept();
}

void chooseTrans_ui::on_btnChoose_clicked()
{
    QString name = ui->comboBox->currentText();
    DataBaseUser db;
    User u = db.getUserByName(name);
    m_asManager.chooseTranslator(u.getID());
    m_QInformBox::information(this, "提示", QString("%1 已成为您的翻译者！").arg(name));
}

void chooseTrans_ui::on_btnChooseTime_clicked()
{
    QDate d = ui->dateEditCurrent->date();
    QTime t = ui->timeEditCurrent->time();
    QDateTime dt;
    dt.setDate(d);
    dt.setTime(t);
    if (dt < QDateTime::currentDateTime())
    {
        m_QInformBox::warning(this, "提示", QString("截至日期不能在当下时间前！"));
        return;
    }
    if (dt > m_asManager.get_deadline())
    {
        m_QInformBox::warning(this, "提示", QString("截至日期不能在总任务截止日期前！"));
        return;
    }
    m_asManager.setDDL(dt);
    m_QInformBox::warning(this, "提示", QString("您选择的提交截止日期为：%1").arg(dt.toString()));
}
