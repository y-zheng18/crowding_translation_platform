/*************************************************************************
【文件名】                 recharge_ui.cpp
【功能模块和目的】          支付界面
【开发者及日期】           2019/7/31
*************************************************************************/
#include "recharge_ui.h"
#include "ui_recharge_ui.h"
#include <QGraphicsDropShadowEffect>
#include "m_QInformbox.h"
reCharge_ui::reCharge_ui(User &u, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reCharge_ui),
    m_user(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(500, 600);
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
}

reCharge_ui::~reCharge_ui()
{
    delete ui;
}

void reCharge_ui::on_btnOK_clicked()
{
    float money = ui->lETMoney->text().toFloat();
    if (money <= 0 || money > 9999)
    {
        m_QInformBox::warning(this, "提示", "充值失败！请输入有效充值金额！");
        return;
    }
    m_user.setMoney(money + m_user.getMoney());
    m_QInformBox::information(this, "提示", "充值成功！");
    this->accept();
}

void reCharge_ui::on_btnCancel_clicked()
{
    this->reject();
}
