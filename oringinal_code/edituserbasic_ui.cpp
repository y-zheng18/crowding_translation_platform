#include "edituserbasic_ui.h"
#include "ui_edituserbasic_ui.h"
#include <QGraphicsDropShadowEffect>
editUserBasic_ui::editUserBasic_ui(User &u, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editUserBasic_ui),
    m_user(u)
{
    ui->setupUi(this);
    ui->setupUi(this);
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(1200, 800);
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    ui->frame->setGeometry(5, 5, this->width() - 5, this->height() - 5);//设置有效范围框
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);

    ui->lETUserName->setText(m_user.getUserName());
    ui->lETMoney->setText(QString("%1元").arg(m_user.getMoney()));
    ui->LETScore->setText(QString("%1").arg(m_user.getScore()));
    ui->LETEmail->setText(m_user.getEmail());
    QPixmap pix = m_user.getPix();
    if (!pix.isNull())
    {
        pix.scaled(ui->label_picture->size(), Qt::KeepAspectRatio);
        ui->label_picture->setScaledContents(true);
        ui->label_picture->setPixmap(pix);
    }
}

editUserBasic_ui::~editUserBasic_ui()
{
    delete ui;
}

void editUserBasic_ui::on_btnClose_clicked()
{
    this->close();
}
