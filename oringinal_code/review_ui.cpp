/*************************************************************************
【文件名】                review_ui.cpp
【功能模块和目的】         负责人分配任务以及评价界面
【开发者及日期】           2019/8/1
*************************************************************************/
#include "review_ui.h"
#include "ui_review_ui.h"
#include "database.h"
#include "QFileDialog"
#include "QGraphicsDropShadowEffect"
Review_ui::Review_ui(User &u, AssignmentManager &a, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Review_ui),
    m_asManager(a),
    m_user(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(900, 900));
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(m_asManager.getTranslaors().size());
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    m_iStatus = 0;
    for (int i = 0;i < m_asManager.getTranslaors().size();i++)
    {
        if (m_asManager.getSubAssignment()[m_asManager.getTranslaors()[i]].getText() == "")
        {
            m_iStatus = 1;
        }
    }
    if (!m_iStatus)                      //已分配任务
    {
        ui->lineEdit->hide();
        ui->toolButton->hide();
        QMap<QString, TextInteraction> getTrans = m_asManager.getSubTranslated();
        for (int i = 0;i < m_asManager.getTranslaors().size();i++)
        {
            User u(m_asManager.getTranslaors()[i]);
            QLabel* lb = new QLabel;
            QString text = QString("%1的译稿：%2").arg(u.getUserName())
                    .arg(getTrans[u.getID()].getText());
            lb->setText(text);
            //lb->setFixedSize(500, 500);
            //ui->tableWidget->setColumnWidth(0, 800);
            ui->tableWidget->setRowHeight(i, 400);
            ui->tableWidget->setCellWidget(i, 0, lb);
            ui->comboBox->addItem(u.getUserName());
        }
    }
    else {
        for (int i = 0;i < m_asManager.getTranslaors().size();i++)
        {
            User u(m_asManager.getTranslaors()[i]);
            if (m_asManager.getSubAssignment()[u.getID()].getText() == "")
                ui->comboBox->addItem(u.getUserName());
        }
        ui->label->hide();
        ui->textEdit->setPlaceholderText("分配带翻译文本");
        ui->btnChoose->setText("上传文本");
        ui->textEdit->setReadOnly(true);
        ui->lineEdit->setReadOnly(true);
        ui->tableWidget->hide();
        ui->btnDownload->hide();
    }
}

Review_ui::~Review_ui()
{
    delete ui;
}

void Review_ui::on_btnChoose_clicked()
{
    QString userName = ui->comboBox->currentText();
    
    DataBaseUser db;
    User u = db.getUserByName(userName);
    if (!m_iStatus)
    {
        QString review = ui->textEdit->toPlainText();
        if (review.isEmpty())
        {
            m_QInformBox::information(this, "提示", "评价不能为空！");
            return;
        }
        m_asManager.giveReview(u.getID(), review);
        m_QInformBox::information(this, "提示", "添加评价成功！");
    }
    else 
    {
        QString text = ui->textEdit->toPlainText();
        if (text.isEmpty())
        {
            m_QInformBox::information(this, "提示", "子任务不能为空！");
            return;
        }
        m_asManager.allocateAssignment(u.getID(), ui->lineEdit->text());
        ui->comboBox->removeItem(ui->comboBox->currentIndex());
        m_QInformBox::information(this, "提示", "上传成功！");
    }
}

void Review_ui::on_btnDownload_clicked()
{
    QString userName = ui->comboBox->currentText();
    DataBaseUser db;
    User u = db.getUserByName(userName);
    QString filePath = QFileDialog::getSaveFileName(this,tr("Open File"),"/home",tr("Text File(*.txt)"));
    if (filePath.isEmpty())
        return;
    QFile aFile(filePath);
    if (!aFile.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream aStream(&aFile); //用文本流读取文件
    QString str = m_asManager.getSubTranslated()[u.getID()].getText(); //转换为字符串
    aStream<<str; //写入文本流
    aFile.close();//关闭文件
    m_QInformBox::information(this, "提示", "保存成功！");
    return;
}

void Review_ui::on_toolButton_clicked()
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
    QTextStream aStream(&aFile);                                                     //用文本流读取文件
    ui->textEdit->setPlainText(aStream.readAll());
    aFile.close();                                                                  //关闭文件
}

void Review_ui::on_btnOK_clicked()
{
    if (!m_iStatus)
    {
        this->accept();
    }
    else
    {
         int ret =  m_QInformBox::information(this, "提示", "确认分配完毕？");
         if (ret == QMessageBox::Ok)
         {
             m_asManager.setStatusProcess();
         }
         this->accept();
    }
}

void Review_ui::on_btnCancel_clicked()
{
    this->reject();
}
