/*************************************************************************
【文件名】                 ManagerOperate_ui.cpp
【功能模块和目的】          负责人操作界面
【开发者及日期】           2019/8/1
*************************************************************************/

#include "manageroperate_ui.h"
#include "ui_manageroperate_ui.h"
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include "choosetrans_ui.h"
#include "review_ui.h"
/*************************************************************************
【函数名称】        ManagerOperate_ui
【函数功能】        构造函数，为负责人设置接口进行操作
【参数】           负责人引用
【返回值】
【开发者及日期】     8/1
*************************************************************************/
ManagerOperate_ui::ManagerOperate_ui(User& u, AssignmentManager& a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManagerOperate_ui),
    asManager(a),
    m_user(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
    ui->dateEditCurrent->setDate(QDate::currentDate());
    ui->timeEditCurrent->setTime(QTime::currentTime());
    if (asManager.getStatus() == MANAGER_RECUIT_DONE)
    {
        ui->btnOK->setText("设置截至日期");
        ui->labelDDL->setText("设置译者报名截至日期");
        ui->textBrowser->hide();
        ui->toolButton->hide();
        ui->lineEdit->hide();
    }
    else if (asManager.getStatus() == RECRUITING_TRANSLATOR)
    {
        ui->dateEditCurrent->hide();
        ui->timeEditCurrent->hide();
        ui->labelDDL->hide();
        ui->textBrowser->hide();
        ui->toolButton->hide();
        ui->btnOK->setText("查看报名状态");

        ui->lineEdit->hide();
    }
    else if (asManager.getStatus() == PROCCESSING)
    {
        ui->dateEditCurrent->hide();
        ui->timeEditCurrent->hide();
        ui->labelDDL->hide();
        ui->btnOK->setText("查看译者翻译状态");
        ui->btnload->setText("上传最终译稿");
    }
}

ManagerOperate_ui::~ManagerOperate_ui()
{
    delete ui;
}

void ManagerOperate_ui::on_btnOK_clicked()
{
    if (asManager.getStatus() == MANAGER_RECUIT_DONE)
    {
        QDate d = ui->dateEditCurrent->date();
        QTime t = ui->timeEditCurrent->time();
        QDateTime dt;
        dt.setDate(d);
        dt.setTime(t);
        if (dt < QDateTime::currentDateTime())
        {
            m_QInformBox::warning(this, "提示", "报名截止日期不能在当下时间前！");
            return;
        }
        if (dt > asManager.get_deadline())
        {
            m_QInformBox::warning(this, "提示", "报名截止日期不能在总任务完成前！");
            return;
        }
        m_QInformBox::information(this, "提示", "报名截止日期设置成功！");
        asManager.setCurrentDDL(dt);
        this->accept();
    }
    else if (asManager.getStatus() == RECRUITING_TRANSLATOR)
    {
        chooseTrans_ui* chooseTran = new chooseTrans_ui(m_user, asManager);
        chooseTran->exec();
    }
    else if (asManager.getStatus() == PROCCESSING)
    {
        Review_ui* rev = new Review_ui(m_user, asManager);
        rev->exec();
    }
}

void ManagerOperate_ui::on_btnload_clicked()
{
    if (asManager.getStatus() == PROCCESSING)
    {
        QString text = ui->lineEdit->text();
        QFile aFile(text);
        if (!text.isNull() && aFile.exists())
        {
            asManager.uploadText(ui->lineEdit->text());
            asManager.setStatusDone();

            m_QInformBox::information(this, "提示", "提交成功！");
            this->accept();
        }
        else {
            m_QInformBox::information(this, "提示", "提交失败！译稿错误！");
            return;
        }
    }
    else
    {
        QString filePath = QFileDialog::getSaveFileName(this,tr("Open File"),"/home",tr("Text File(*.txt)"));
        if (filePath.isEmpty())
            return;
        QFile aFile(filePath);
        if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QTextStream aStream(&aFile); //用文本流读取文件
        QString str = asManager.getText(); //转换为字符串
        aStream<<str; //写入文本流
        aFile.close();//关闭文件
        m_QInformBox::information(this, "提示", "保存成功！");
        return;
    }
}

void ManagerOperate_ui::on_toolButton_clicked()
{
    QString filePath =
            QFileDialog::getOpenFileName( this,   tr("选择文本"), ".",  "(*.txt);;All files(*.*)");
    ui->lineEdit->setText(filePath);
    if (filePath == "")
    {
        m_QInformBox::warning(this, "提示", "上传失败！请检查文本格式！");
        return;
    }
    QFile aFile(filePath);
    if (!aFile.exists()) //文件不存在
    {
        m_QInformBox::warning(this, "提示", "上传失败！请检查文本格式！");
        return;
    }
    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        m_QInformBox::warning(this, "提示", "上传失败！请检查文本格式！");
        return;
    }
    QTextStream aStream(&aFile); //用文本流读取文件
    ui->textBrowser->setText(aStream.readAll());
    return;
}

void ManagerOperate_ui::on_btnCancel_clicked()
{
    this->close();
}
