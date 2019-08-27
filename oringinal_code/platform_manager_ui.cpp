/*************************************************************************
【文件名】                 PLATFORM_MANAGER_UI.h
【功能模块和目的】          平台管理员界面
【开发者及日期】           2019/8/2
*************************************************************************/
#include "platform_manager_ui.h"
#include "ui_platform_manager_ui.h"
#include "QGraphicsDropShadowEffect"
#include "database.h"
#include "edituserfile_ui.h"
#include "m_QInformbox.h"
#include "messageinformbox.h"
PLATFORM_MANAGER_UI::PLATFORM_MANAGER_UI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PLATFORM_MANAGER_UI)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(1000, 1000));
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);

    DataBaseUser db;
    all_user = db.getUser();
    ui->tableWidget->setRowCount(all_user.size());
    ui->tableWidget->setColumnCount(2);
    int index = 0;
    for (int i = 0;i <all_user.size();i++)
    {
        all_user[i].getUserCertification();

        if (all_user[i].m_certification.getIDNum() != "")
        {
            QLabel* lb = new QLabel;
            lb->setText(all_user[i].getID());
            ui->comboBox->addItem(all_user[i].getID());
            EditUserFile_ui* edu = new EditUserFile_ui(all_user[i], ui->tableWidget);
            edu->setFixedSize(500,500);
            ui->tableWidget->setRowHeight(index, 600);
            ui->tableWidget->setColumnWidth(1, 600);
            ui->tableWidget->setCellWidget(index, 0, lb);
            ui->tableWidget->setCellWidget(index, 1, edu);
            edu->show();
            index++;
        }
    }
}

PLATFORM_MANAGER_UI::~PLATFORM_MANAGER_UI()
{
    delete ui;
}

void PLATFORM_MANAGER_UI::on_btnOK_clicked()
{
    this->accept();
}

void PLATFORM_MANAGER_UI::on_btnCancel_clicked()
{
    this->close();
}

void PLATFORM_MANAGER_UI::on_btnChoose_clicked()
{
    int s = ui->spinBox->value();
    QString id = ui->comboBox->currentText();
    User u (id);
    u.getUserCertification();
    u.m_certification.set_checked(true);
    u.setScore(u.getScore() + s);
    for (int i = 0;i < all_user.size();i++)
    {
        if (id == all_user[i].getID())
        {
            all_user[i].setScore(u.getScore() + s);
        }
    }
    m_QInformBox::information(this, "提示", "认证成功！");
    Message m(QDateTime::currentDateTime(), "认证平台", "MANAGER", id,
              "您的认证已更新");
    return;
}
