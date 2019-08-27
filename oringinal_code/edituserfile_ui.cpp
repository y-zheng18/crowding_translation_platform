#include "edituserfile_ui.h"
#include "ui_edituserfile_ui.h"
#include "m_QInformbox.h"
#include <QGraphicsDropShadowEffect>
#include <QDir>
#include <QFileDialog>

/*************************************************************************
【文件名】                 editUserFile.cpp
【功能模块和目的】          用户资质 实名认证界面
【开发者及日期】           2019/7/30
*************************************************************************/
EditUserFile_ui::EditUserFile_ui(User& u, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditUserFile_ui),
    m_user(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(800, 600);
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);

    if (m_user.getEmail() != "")
    {
        ui->labelpic->setVisible(false);
        ui->LETPic->setVisible(false);
        ui->toolButton->setVisible(false);
        ui->label_email->setVisible(false);
        ui->LETEmail->setText(" ");
        ui->LETEmail->setVisible(false);      
        ui->label_email_star->setVisible(false);
    }

    QPixmap pix = m_user.getPix();
    if (!pix.isNull())
    {
        pix.scaled(ui->label_picture->size(), Qt::KeepAspectRatio);
        ui->label_picture->setScaledContents(true);
        ui->label_picture->setPixmap(pix);
    }
    if (m_user.m_certification.getName() == "")
    {
        m_user.getUserCertification();
    }
    certification certi = m_user.m_certification;
    if (certi.getIDNum() != "")
    {
        ui->lETIDnum->setText(certi.getIDNum());
        ui->lETIDnum->setFocusPolicy(Qt::NoFocus);
    }
    if (certi.getName() != "")
    {
        ui->lETrealName->setText(certi.getName());
        ui->lETrealName->setFocusPolicy(Qt::NoFocus);
    }
    ui->textEdit->setText(certi.getQualText());
}

EditUserFile_ui::~EditUserFile_ui()
{
    delete ui;
}

void EditUserFile_ui::setUser(const User &u)
{
    m_user = u;
}

void EditUserFile_ui::on_pushButton_clicked()
{
    QString realName = ui->lETrealName->text();
    if (realName == "")
    {
        m_QInformBox::warning(this, "提示", "真实姓名不能为空！");
        return;
    }
    QString email = ui->LETEmail->text();
    if (email == "")
    {
        m_QInformBox::warning(this, "提示", "邮箱不能为空！");
        return;
    }
    QString IDnum = ui->lETIDnum->text();
    if (IDnum == "")
    {
        m_QInformBox::warning(this, "提示", "证件号码不能为空！");
        return;
    }
    QString description = ui->textEdit->document()->toPlainText();

    QPixmap certiPix;
    QString filePath = ui->LETPicLanguage->text();
    if (filePath != "")
    {
        if (!certiPix.load(filePath))
        {
            m_QInformBox::warning(this, "提示", "语言资质证明上传失败！请检查图片格式与大小！");
            return;
        }
    }
    if (m_user.getEmail() == "")
    {
        m_user.setEmail(email);
    }
    m_user.m_certification.set_UserId(m_user.getID());
    m_user.m_certification.set_IDNum(IDnum);
    m_user.m_certification.set_RealName(realName);
    m_user.m_certification.set_Qualification(description);
    User u = m_user;
    certification c = m_user.m_certification;
    if(ui->label_picture->pixmap())
    {
        m_user.setPix(*ui->label_picture->pixmap());
    }
    //邮箱空格表示标记资质上传为更新记录
    if (ui->LETEmail->text() != " ")
    {

        m_QInformBox::information(this, "提示", "实名认证与资质证明上传成功！");
    }
    this->accept();
}

void EditUserFile_ui::on_toolButton_clicked()
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

void EditUserFile_ui::on_toolButton_2_clicked()
{
    QString filePath =
            QFileDialog::getOpenFileName( this,   tr("选择图片"), ".",  "(*.png);;All files(*.*)");
    ui->LETPicLanguage->setText(filePath);

}
