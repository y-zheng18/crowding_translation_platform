/*************************************************************************
【文件名】                 messageInformBox_ui.h
【功能模块和目的】          消息盒子界面类
【开发者及日期】           2019/8/1
*************************************************************************/
#include "messageinformbox_ui.h"
#include "ui_messageinformbox_ui.h"
#include "QGraphicsDropShadowEffect"
#include "QLabel"
MessageInformBox_ui::MessageInformBox_ui(MessageInformBox& m, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MessageInformBox_ui),
    m_message(m)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(700, 700);
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect* shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);

     ui->tableWidget->setColumnCount(1);
     ui->tableWidget->horizontalHeader()->hide();
     ui->tableWidget->verticalHeader()->hide();
    int n1 = 0;
    int n2 = 0;
    n1 += m_message.getNew().size();
    n2 += m_message.getOld().size();
    ui->tableWidget->setColumnWidth(0, 400);
    ui->tableWidget->setRowCount(n1 + n2);
    for (int i = 0;i < n2;i++)
    {
        QLabel* label = new QLabel;
        label->setText("oldMessage:" +m_message.getOld()[i].get_messageText());
        //btn->setStyleSheet("QPushButton{background-color: rgba(255, 255, 255, 0)}");
        ui->tableWidget->setRowHeight(i, 300);
        ui->tableWidget->setCellWidget(i, 0, label);
        //connect(btn, SIGNAL(clicked()), this, SLOT(on_on_btnUser_clicked(trans.getID())));
    }
    for (int i = 0;i < n1;i++)
    {
        QLabel* label = new QLabel;
        label->setText("newMessage:" + m_message.getNew()[i].get_messageText());
        label->setStyleSheet("border-color: rgb(170, 0, 0);");
        ui->tableWidget->setRowHeight(i + n2, 300);
        ui->tableWidget->setCellWidget(i + n2, 0, label);
        //connect(btn, SIGNAL(clicked()), this, SLOT(on_on_btnUser_clicked(trans.getID())));
    }
}

MessageInformBox_ui::~MessageInformBox_ui()
{
    delete ui;
}

void MessageInformBox_ui::on_btnRead_clicked()
{
    this->accept();
}

void MessageInformBox_ui::on_btnDelete_clicked()
{
    ui->tableWidget->clear();
    m_message.delete_Message();
    this->close();
}
