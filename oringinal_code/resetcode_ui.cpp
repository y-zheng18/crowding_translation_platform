/*************************************************************************
【文件名】                resetCode_ui.cpp
【功能模块和目的】         重设密码
【开发者及日期】           2019/7/30
*************************************************************************/
#include "resetcode_ui.h"
#include "ui_resetcode_ui.h"
#include "m_QInformbox.h"
#include <QGraphicsDropShadowEffect>
resetCode_ui::resetCode_ui(User &u, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resetCode_ui),
    m_user(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(600, 400);


    ui->frame->setStyleSheet("QFrame{background-color: rgb(255, 255, 255);border-radius:10px}"); //设置圆角与背景透明
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
}

resetCode_ui::~resetCode_ui()
{
    delete ui;
}

void resetCode_ui::on_btnOK_clicked()
{
    QString oldCode = ui->lineOldCode->text();
    QString newCode = ui->lineNewCode->text();
    QString Repeat = ui->lineCodeRepeat->text();
    if (newCode.size() < 6)
    {
        m_QInformBox::warning(this, "提示", "密码过短！");
        return;
    }
    if (newCode != Repeat)
    {
        m_QInformBox::warning(this, "提示", "两次密码不匹配！");
        return;
    }
    if (!m_user.resetPassWord(oldCode, newCode))
    {
        m_QInformBox::warning(this, "提示", "密码错误！");
        return;
    }
    m_QInformBox::information(this, "提示", "密码设置成功！");
    this->accept();
}

void resetCode_ui::on_btnCancel_clicked()
{
    this->reject();
}
