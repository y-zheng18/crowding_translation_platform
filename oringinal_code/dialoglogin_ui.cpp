#include "dialoglogin_ui.h"
#include "ui_dialoglogin.h"
#include <QGraphicsDropShadowEffect>
#include <QFrame>
#include "database.h"
#include "m_QInformbox.h"
#include "register_ui.h"
DialogLogIn_ui::DialogLogIn_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLogIn)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(800, 1050);

    ui->frame->setStyleSheet("QFrame{background-color: rgb(255, 255, 255);border-radius:10px}"); //设置圆角与背景透明
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
}

DialogLogIn_ui::~DialogLogIn_ui()
{
    delete ui;
}


void DialogLogIn_ui::on_btnClose_clicked()
{
    this->close();
}

void DialogLogIn_ui::on_btnLogIn_clicked()
{
    QString name = ui->lineUserName->text();
    QString password = ui->lineCode->text();
    if (name == "")
    {
        m_QInformBox::warning(this, "提示", "用户名不能为空！");
        ui->lineUserName->setPlaceholderText("请输入用户名");
        ui->lineCode->setPlaceholderText("请输入密码");
        return;
    }
    if (password == "")
    {
        m_QInformBox::warning(this, "提示", "请输入密码！");
        ui->lineUserName->setPlaceholderText("请输入用户名");
        ui->lineCode->setPlaceholderText("请输入密码");
        return;
    }
    DataBaseUser db;
    User u = db.getUserByName(name);
    if (u.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "用户不存在！");
        ui->lineUserName->setPlaceholderText("请输入用户名");
        ui->lineCode->setPlaceholderText("请输入密码");
        return;
    }
    else if (u.getPassword() != password)
    {
        m_QInformBox::warning(this, "提示", "用户名或密码不正确！");
        ui->lineUserName->setPlaceholderText("请输入用户名");
        ui->lineCode->setPlaceholderText("请输入密码");
        return;
    }
    else if (u.getPassword() == password)
    {
        m_user = u;
        this->accept();
        m_QInformBox::information(this, "提示", "登录成功！");
    }
}

void DialogLogIn_ui::on_btnRegister_clicked()
{
    Register_ui* m_register = new Register_ui;
    m_register->exec();
}
