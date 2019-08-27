#include "choosemanager_ui.h"
#include "ui_choosemanager_ui.h"
#include "usermessage_ui.h"
#include "QFileDialog"
#include "m_QInformbox.h"
#include "database.h"
#include <QGraphicsDropShadowEffect>

/*************************************************************************
【函数名称】        ChooseManager_ui
【函数功能】        展示负责人报名情况、发布者选择负责人，报名截止前发布者可维护任务信息
【参数】
【返回值】
【开发者及日期】     7/31
*************************************************************************/
ChooseManager_ui::ChooseManager_ui(User& u, AssignmentPublisher& asP, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseManager),
    m_asPubl(asP),
    m_user(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(QSize(900, 900));
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(0, 0);
    shadow_effect->setColor(Qt::black);
    shadow_effect->setBlurRadius(10);
    ui->frame->setGraphicsEffect(shadow_effect);
    QPixmap pix = m_asPubl.getPix();
    if (!pix.isNull())
    {
        pix.scaled(ui->label_picture->size(), Qt::KeepAspectRatio);
        ui->label_picture->setScaledContents(true);
        ui->label_picture->setPixmap(pix);
    }
    if (m_asPubl.getDescription() != "")
    {
        ui->textEdit->setText(m_asPubl.getDescription());
    }
    if (m_asPubl.get_currentDDL() > QDateTime::currentDateTime())
    {
        ui->btnChoose->setEnabled(false);
        ui->btnChoose->setText("报名未截至");

    }
    else
    {
        ui->btnText->setEnabled(false);
        ui->btnPic->setEnabled(false);
        ui->textEdit->setEnabled(false);
        ui->LETPic->setEnabled(false);
        ui->LETText->setEnabled(false);
        ui->btnChoose->setEnabled(true);
        ui->btnChoose->setText("选择负责人");
    }
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setRowCount(m_asPubl.getSignUp().size());
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    for (int i = 0;i < m_asPubl.getSignUp().size();i++)
    {
        User u(m_asPubl.getSignUp()[i].getCandidate());
        userMessage_ui * aShow = new userMessage_ui(u, ui->tableWidget);
        aShow->setFixedSize(700, 700);
        ui->tableWidget->setColumnWidth(0, 700);
        ui->tableWidget->setRowHeight(i, 700);
        ui->tableWidget->setCellWidget(i, 0, aShow);
        aShow->show();
        ui->comboBox->addItem(u.getUserName());
    }

    if (m_asPubl.getManagerID() != "")
    {
        ui->btnChoose->setText("您已选择负责人");
        ui->btnChoose->setEnabled(false);
        ui->comboBox->setEnabled("false");
        ui->comboBox->clear();
        ui->comboBox->addItem(User(m_asPubl.getManagerID()).getUserName());
    }
}

ChooseManager_ui::~ChooseManager_ui()
{
    delete ui;
}

void ChooseManager_ui::on_btnOK_clicked()
{
    QPixmap pix;
    if (ui->label_picture->pixmap())
    {
        pix = *ui->label_picture->pixmap();
    }
    if (!pix.isNull())
    {
        m_asPubl.setPix(pix);
    }

    QString filePath = ui->LETText->text();
    if (!filePath.isNull())
    {
        m_asPubl.uploadText(filePath);
    }
    m_asPubl.uploadDescription(ui->textEdit->toPlainText());
    this->accept();
}

void ChooseManager_ui::on_btnCancel_clicked()
{
    this->reject();
}

void ChooseManager_ui::on_btnText_clicked()
{
    QString filePath =
            QFileDialog::getOpenFileName( this,   tr("选择文本"), ".",  "(*.txt);;All files(*.*)");
    ui->LETText->setText(filePath);
    if (filePath == "")
    {
        m_QInformBox::warning(this, "提示", "上传失败！请检查文本格式！");
        return;
    }
}

void ChooseManager_ui::on_btnPic_clicked()
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

void ChooseManager_ui::on_btnChoose_clicked()
{
    QString name = ui->comboBox->currentText();
    DataBaseUser db;
    User u = db.getUserByName(name);
    m_asPubl.chooseManager(u.getID());
    m_QInformBox::information(this, "提示", QString("%1 已成为您的负责人！").arg(name));
    this->accept();
}
