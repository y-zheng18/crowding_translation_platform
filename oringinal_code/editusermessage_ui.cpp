#include "editusermessage_ui.h"
#include "ui_editusermessage_ui.h"
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include "recharge_ui.h"
/*************************************************************************
【文件名】                 editUserMessage.h
【功能模块和目的】          用户基本信息维护
【开发者及日期】           2019/7/30
*************************************************************************/
EditUserMessage_ui::EditUserMessage_ui(User& u, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserMessage_ui),
    m_user(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(900, 600);
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);

    ui->lETUserName->setText(m_user.getUserName());
    ui->lETUserName->setReadOnly(true);
    ui->lETMoney->setText(QString("%1元").arg(m_user.getMoney()));
    ui->lETMoney->setReadOnly(true);
    ui->LETScore->setText(QString("%1").arg(m_user.getScore()));
    ui->LETScore->setReadOnly(true);
    ui->LETEmail->setText(m_user.getEmail());
    ui->LETEmail->setReadOnly(true);
    QPixmap pix = m_user.getPix();
    if (!pix.isNull())
    {
        pix.scaled(ui->label_picture->size(), Qt::KeepAspectRatio);
        ui->label_picture->setScaledContents(true);
        ui->label_picture->setPixmap(pix);
    }
}
EditUserMessage_ui::~EditUserMessage_ui()
{
    delete ui;
}

void EditUserMessage_ui::on_btnClose_clicked()
{
    this->close();
}

void EditUserMessage_ui::on_toolButton_clicked()
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
    m_user.setPix(pix);
    pix.scaled(ui->label_picture->size(), Qt::KeepAspectRatio);
    ui->label_picture->setScaledContents(true);
    ui->label_picture->setPixmap(pix);
}

void EditUserMessage_ui::on_pushButton_clicked()
{
    if (ui->lETUserName->text() != m_user.getUserName())
    {
        if (!m_user.resetUserName(ui->lETUserName->text()))
        {
            m_QInformBox::warning(this, "提示", "设置失败！用户名已经存在！");
        }
    }
    m_user.setEmail(ui->LETEmail->text());
    this->accept();
}

void EditUserMessage_ui::on_btnEditName_clicked()
{
    ui->lETUserName->setReadOnly(false);
}

void EditUserMessage_ui::on_btnEmail_clicked()
{
    ui->LETEmail->setReadOnly(false);
}

void EditUserMessage_ui::on_btnCharge_clicked()
{
    reCharge_ui* recharge = new reCharge_ui(m_user);
    recharge->exec();
}
