/*************************************************************************
【文件名】                Translator_ui.h
【功能模块和目的】         译者操作平台
【开发者及日期】           2019/7/31
*************************************************************************/
#include "translator_ui.h"
#include "ui_translator_ui.h"
#include <QFileDialog>
#include <QTextStream>
#include "m_QInformbox.h"
#include "messageinformbox.h"
translator_ui::translator_ui(AssignmentTranslator &a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::translator_ui),
    m_asTran(a)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    ui->textEditReview->setEnabled(false);
    ui->textEditReview->setText(m_asTran.getReview().getText());
    ui->textEditTran->setText(m_asTran.getTranlatedText().getText());
    ui->lineEdit->setEnabled(false);
    ui->textEditReviewSubAS->setText(m_asTran.getSubAssignment().getText());
    ui->textEditReviewSubAS->setEnabled(false);
}

translator_ui::~translator_ui()
{
    delete ui;
}


void translator_ui::on_toolButton_clicked()
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
    ui->textEditTran->setPlainText(aStream.readAll());
    aFile.close();//关闭文件
}

void translator_ui::on_btnOK_clicked()
{
    m_asTran.editTextOnline(ui->textEditTran->toPlainText());
    m_QInformBox::information(this, "提示", "上传成功！");
    this->accept();
}

void translator_ui::on_btnCancel_clicked()
{
    this->reject();
}

void translator_ui::on_btnFinal_clicked()
{
    m_asTran.editTextOnline(ui->textEditTran->toPlainText());
    User u(m_asTran.getUserId());
    QString m = QString("任务状态变更，您负责的任务 %1 译者%2已经提交译稿！")
            .arg(m_asTran.getName()).arg(u.getUserName());
    Message m_message(QDateTime::currentDateTime(), m_asTran.getName(), u.getID(), m_asTran.getManagerID(), m);
    m_QInformBox::information(this, "提示", "提交成功！");
}
