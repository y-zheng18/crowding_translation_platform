/*************************************************************************
【文件名】                Register_ui.cpp
【功能模块和目的】         注册界面
【开发者及日期】           2019/7/30
*************************************************************************/
#include "register_ui.h"
#include "ui_register_ui.h"
#include "m_QInformbox.h"
#include "database.h"
#include "editusermessage_ui.h"
#include <QGraphicsDropShadowEffect>
#include "edituserfile_ui.h"
Register_ui::Register_ui(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::Register_ui)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(500, 850);
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
}

Register_ui::~Register_ui()
{
    delete ui;
}

void Register_ui::on_btnRegister_clicked()
{
    QString code0 = ui->lineCode->text();
    QString code1 = ui->lineCodeRepeat->text();
    if (code0 != code1)
    {
        m_QInformBox::warning(this, "提示", "两次输入密码不匹配！");
        return;
    }
    if (code0 == "")
    {
        m_QInformBox::warning(this, "提示", "密码不能为空！");
        return;
    }
    if (code0.size() < 6)
    {
        m_QInformBox::warning(this, "提示", "密码过短！");
        return;
    }
    DataBaseUser db;
    QString name = ui->lineUserName->text();
    if (name == "")
    {
        m_QInformBox::warning(this, "提示", "用户名不能为空！");
        return;
    }
    if (db.search(name))
    {
        m_QInformBox::warning(this, "提示", "该用户名已被注册！");
        return;
    }
    m_user = User(name, code0);
    m_QInformBox::information(this, "提示", "注册成功！请完善基本信息");
    this->accept();
    EditUserFile_ui edit(m_user);
    //edit.setUser(m_user);
    qDebug()<<" ";
    edit.exec();
    m_user = User(m_user.getID());
    m_user.getUserCertification();
}

void Register_ui::on_btnCancel_clicked()
{
    this->close();
}
