/*************************************************************************
【文件名】                usermessage_ui.cpp
【功能模块和目的】         用户数据详细平台
【开发者及日期】           2019/7/26
*************************************************************************/
#include "usermessage_ui.h"
#include "ui_usermessage_ui.h"
#include <QGraphicsDropShadowEffect>


userMessage_ui::userMessage_ui(User& u, QWidget *parent):
    QDialog(parent),
    ui(new Ui::userMessage_ui),
    m_user(u)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(650, 500));
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);

    ui->labelName->setText(QString("用户名：    %1").arg(m_user.getUserName()));
    ui->label_email->setText(QString("email：    %1").arg(m_user.getEmail()));
    ui->label_score->setText(QString("用户积分：    %1").arg(m_user.getScore()));
    QPixmap pix = m_user.getPix();
    if (pix.width() != 0)
    {
        pix.scaled(ui->label_picture->size(), Qt::KeepAspectRatio);
        ui->label_picture->setScaledContents(true);
        ui->label_picture->setPixmap(pix);
    }

    m_user.getUserCertification();
    ui->label_language->setText(QString("用户语言资质：    %1").arg(m_user.m_certification.getQualText()));
    if (m_user.m_certification.getIsChecked() == true)
    {
        ui->label_Proved->setText(QString("资质认证：已认证"));
    }
    else
    {
        ui->label_Proved->setText(QString("资质认证：未认证"));
    }
    m_user.getUserAssignment();
    QString assignmentName = "";
    for (int i = 0;i < m_user.m_userAsPublisher.size();i++)
    {
        assignmentName += m_user.m_userAsPublisher[i].getName();
        assignmentName += "\n";
    }
    ui->labelPublisher->setText(QString("%1").arg(assignmentName));
    assignmentName = "";

    for (int i = 0;i < m_user.m_userAsManager.size();i++)
    {
        assignmentName += m_user.m_userAsManager[i].getName();
        assignmentName += "\n";
    }
    ui->labelManager->setText(QString("%1").arg(assignmentName));

    assignmentName = "";
    for (int i = 0;i < m_user.m_userAsTrans.size();i++)
    {
        assignmentName += m_user.m_userAsTrans[i].getName();
        assignmentName += "\n";
    }
    ui->labelTrans->setText(QString("%1").arg(assignmentName));
}

userMessage_ui::~userMessage_ui()
{
    delete ui;
}

void userMessage_ui::on_btnClose_clicked()
{
    this->close();
}


