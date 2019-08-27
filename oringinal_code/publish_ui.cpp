/*************************************************************************
【文件名】                 publish.h
【功能模块和目的】          发布任务界面
【开发者及日期】           2019/7/31
*************************************************************************/
#include "publish_ui.h"
#include "ui_publish_ui.h"
#include "m_QInformbox.h"
#include <QFileDialog>
#include <QGraphicsDropShadowEffect>

Publish_ui::Publish_ui(User& user, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Publish_ui),
    m_user(user)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(600, 900));
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
    ui->dateEditFinal->setDateTime(QDateTime::currentDateTime());
    ui->dateEditCurrent->setDateTime(QDateTime::currentDateTime());
}

Publish_ui::~Publish_ui()
{
    delete ui;
}

void Publish_ui::on_btnCancel_clicked()
{
    this->reject();
}

void Publish_ui::on_btnOK_clicked()
{
    QString Name = ui->lETName->text();
   if (Name == "")
   {
       m_QInformBox::warning(this, "提示", "任务名不能为空！");
       return;
   }
   Assignment aTest(Name);
   if (aTest.getName() != "")
   {
       m_QInformBox::warning(this, "提示", "任务已存在！请更换任务名！");
       return;
   }
   QString description = ui->textEdit->toPlainText();
   if (description == "")
   {
       m_QInformBox::warning(this, "提示", "任务描述不能为空！");
       return;
   }
   LANGUAGE form;
   if (ui->comboBoxLanguageForm->currentText() == "汉译英")
   {
       form = CHINESE_TO_ENGLISH;
   }
   else
   {
       form = ENGLISH_TO_CHINESE;
   }
   float reward = ui->doubleSpinBoxMoney->value();
   if (reward <= 0)
   {
       m_QInformBox::warning(this, "提示", "任务金额不能小于0！");
       return;
   }
   if (reward > m_user.getMoney())
   {
       m_QInformBox::warning(this, "提示", "余额不足！");
       return;
   }
   QDateTime dt;
   dt.setDate(ui->dateEditFinal->date());
   dt.setTime(ui->timeEditFinal->time());
   QDateTime c_dt;
   c_dt.setDate(ui->dateEditCurrent->date());
   c_dt.setTime(ui->timeEditCurrent->time());
   if (c_dt > dt)
   {
       m_QInformBox::warning(this, "提示", "招募截至时间不能在任务截至之后！");
       return;
   }
   if (c_dt < QDateTime::currentDateTime() || dt < QDateTime::currentDateTime())
   {
       m_QInformBox::warning(this, "提示", "截至时间不能在当下时间之前！");
       return;
   }
   QString keyword = ui->lETKeys->text();
   QString filePath = ui->LETText->text();
   QString picPath = ui->LETPic->text();
   AssignmentPublisher* asP = new AssignmentPublisher(m_user.getID(), Name);
   asP->setReward(reward);
   asP->setStatus(RECRUITING_MANAGER);
   asP->setTranlationForm(form);
   asP->uploadText(filePath);
   asP->setCurrentDDL(c_dt);
   asP->setDDL(dt);
   asP->uploadDescription(description);
   asP->addKeywords(keyword);
   if (!picPath.isNull())
   {
       asP->uploadPictureMessage(picPath);
   }
   m_user.signUpForPublisher(*asP);
   this->accept();
}

void Publish_ui::on_btnPic_clicked()
{
    QString filePath =
            QFileDialog::getOpenFileName( this,   tr("选择图片"), ".",  "(*.png);;All files(*.*)");
    ui->LETPic->setText(filePath);
    if (filePath == "")
        return;
    QPixmap pix;
    if (!pix.load(filePath))
    {
        m_QInformBox::warning(this, "提示", "上传失败！请检查图片格式与大小！");
        return;
    }
    pix.scaled(ui->label_picture->size(), Qt::KeepAspectRatio);
    ui->label_picture->setScaledContents(true);
    ui->label_picture->setPixmap(pix);
}

void Publish_ui::on_btnText_clicked()
{
    QString filePath =
            QFileDialog::getOpenFileName( this,   tr("选择文本"), ".",  "(*.txt);;All files(*.*)");
    ui->LETText->setText(filePath);
    if (filePath == "")
    {
        m_QInformBox::warning(this, "提示", "上传失败！请检查文本格式！");
        return;
    }
}
