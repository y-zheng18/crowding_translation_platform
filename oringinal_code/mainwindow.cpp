/*************************************************************************
【文件名】                 mainWindow.h
【功能模块和目的】          主界面，用于登陆、任务操作、基本信息更新维护
【开发者及日期】           2019/7/21-2019/8/2
【更新记录】              2019/8/2 排除重大bug
*************************************************************************/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialoglogin_ui.h"
#include "assignmentdetails_ui.h"
#include "assignmentshow_ui.h"
#include "messageinformbox_ui.h"
#include <QMenu>
#include <QPixmap>
#include <QGraphicsDropShadowEffect>
#include "user.h"
#include "database.h"
#include "usermessage_ui.h"
#include "edituserfile_ui.h"
#include "editusermessage_ui.h"
#include "recharge_ui.h"
#include "resetcode_ui.h"
#include "m_tabwidget_ui.h"
#include "publish_ui.h"
#include "platform_manager_ui.h"
#include <QTableWidget>
#include <QMouseEvent>


/*************************************************************************
【函数名称】        ManWindow
【函数功能】        主界面
【参数】
【返回值】
【开发者及日期】     7/29-8/2
【修改记录】         8/1：User MessageInformBox直接作为该窗口成员，防止析构异常Bug
*************************************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setFixedSize(1500, 1000);
    ui->mainToolBar->setVisible(false);

    ui->actionSearch->setCheckable(true);
    ui->lineEdit->addAction(ui->actionSearch, QLineEdit::TrailingPosition);

    ui->btnUser->setText("未登录");
    ui->btnMessage->setEnabled(false);
    QMenu* m_setMenu = new QMenu;
    m_setMenu->addAction(ui->actionBasicPreserved);
    m_setMenu->addAction(ui->actionRealNameAuth);
    m_setMenu->addAction(ui->actionRecharge);
    m_setMenu->addAction(ui->actionResetCode);
    m_setMenu->addAction(ui->actionLogOut);
    m_setMenu->setStyleSheet("border-image: url(:/new/prefix1/C:/Users/z/Desktop/58a6bf16282d2.png);");
    m_setMenu->setIcon(QIcon());
    ui->btnSet->setMenu(m_setMenu);

    m_user = User("");
    m_user.getAllAssignment();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(m_user.all_assignment.size() / 3 + 1);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    for (int i = 0;i < m_user.all_assignment.size();i++)
    {
        assignmentShow_ui* aShow = new assignmentShow_ui(m_user, m_user.all_assignment[i], ui->tableWidget);
        ui->tableWidget->setColumnWidth(i % 3, 350);
        ui->tableWidget->setRowHeight(i / 3, 350);
        ui->tableWidget->setCellWidget(i / 3, i % 3, aShow);
        aShow->show();
    }
    //connect(ui->btnPic, SIGNAL(clicked()), this, SLOT(on_actionBasicPreserved_triggered()));
}


MainWindow::~MainWindow()
{
    delete ui;
}


/*************************************************************************
【函数名称】        logIn
【函数功能】        登陆
【参数】            用户ID
【返回值】
【开发者及日期】     7/29
*************************************************************************/
void MainWindow::logIn(const QString& id)
{
    if (id == "MANAGER")
    {
        QMenu* m_setMenu = new QMenu;
        m_setMenu->addAction(ui->action);
        m_setMenu->addAction(ui->actionLogOut);
        ui->btnSet->setMenu(m_setMenu);
    }
    else
    {
        QMenu* m_setMenu = new QMenu;
        m_setMenu->addAction(ui->actionBasicPreserved);
        m_setMenu->addAction(ui->actionRealNameAuth);
        m_setMenu->addAction(ui->actionRecharge);
        m_setMenu->addAction(ui->actionResetCode);
        m_setMenu->addAction(ui->actionLogOut);
        m_setMenu->setStyleSheet("border-image: url(:/new/prefix1/C:/Users/z/Desktop/58a6bf16282d2.png);");
        m_setMenu->setIcon(QIcon());
        ui->btnSet->setMenu(m_setMenu);
    }
    ui->btnSet->setEnabled(true);
    ui->btnMessage->setEnabled(true);
    m_user = User(id);
    m_box = MessageInformBox(id);
    m_user.getAllAssignment();
    m_user.getUserAssignment();
    ui->btnUser->setText(m_user.getUserName());
    QPixmap pix = m_user.getPix();
    if (!pix.isNull())
    {
        pix.scaled(ui->labelPicture->size(), Qt::KeepAspectRatio);
        ui->labelPicture->setScaledContents(true);
        ui->labelPicture->setPixmap(pix);
    }
    if (m_box.getNew().size() != 0)
    {
        ui->btnMessage->setStyleSheet("#btnMessage{background-color: rgba(255, 255, 255, 255);"
                                       "border-image: url(:/new/prefix1/m_icon/new.png);}");

    }
}


/*************************************************************************
【函数名称】        logOut
【函数功能】        用户注销
【参数】
【返回值】
【开发者及日期】     7/29
*************************************************************************/
void MainWindow::logOut()
{
    ui->tableWidget->clear();
    for (int i = 0;i < m_user.m_userAsTrans.size();i++)
    {
        m_user.m_userAsTrans[i] =
                AssignmentTranslator(m_user.getID(), m_user.m_userAsTrans[i].getName());
    }
    for (int i = 0;i < m_user.m_userAsPublisher.size();i++)
    {
        m_user.m_userAsPublisher[i] =
                AssignmentPublisher(m_user.m_userAsPublisher[i].getName());
    }
    for (int i = 0;i < m_user.m_userAsManager.size();i++)
    {
        m_user.m_userAsManager[i] =
                AssignmentManager(m_user.m_userAsManager[i].getName());
    }
   User u = m_user;                                 //确保登出时析构
   m_user = User("");
   u.all_assignment.clear();
   m_box = MessageInformBox("");
   ui->btnUser->setText("未登录");
   ui->btnMessage->setEnabled(false);
   ui->labelPicture->setPixmap(QPixmap());
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event)
{
    m_bWindowMovable = false;
    event->ignore();
}

void MainWindow::mouseMoveEvent(QMouseEvent* event)
{
    if( m_bWindowMovable )
    {
        m_move = event->globalPos();
        this->move( this->pos() + m_move - m_press );
        m_press = m_move;                           //记录当前位置
    }
    event->ignore();

}

void MainWindow::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton &&
            ui->m_toolBar->rect().contains(event->globalPos() - this->frameGeometry().topLeft()))           //m_toolbar包含鼠标所在位置
    {
        m_bWindowMovable = true;
        m_press = event->globalPos();
    }
    event->ignore();                                //继续向下传递事件
}



void MainWindow::on_btnMin_clicked()                //最小化
{
    this->showMinimized();
}

void MainWindow::on_btnClose_clicked()
{
    //logOut();
    this->close();
}

void MainWindow::on_btnMessage_clicked()
{
    ui->btnMessage->setStyleSheet("#btnMessage{background-color: rgba(255, 255, 255, 0);"
                                  "border-image: url(:/new/prefix1/m_icon/bell.png);}"
                                  "#btnMessage:hover{background-color: rgba(255, 255, 255, 0);"
                                  "border-image: url(:/new/prefix1/m_icon/bell_fill.png);}"
                                  "#btnMessage:pressed{background-color: rgba(255, 255, 255, 0);"
                                  "border-image: url(:/new/prefix1/m_icon/bell_fill.png);}");
    MessageInformBox_ui* message = new MessageInformBox_ui(m_box);
    message->exec();
}

void MainWindow::on_btnUser_clicked()
{
    if (m_user.getID() == "")
    {
        DialogLogIn_ui* dia = new DialogLogIn_ui;
        int rec = dia->exec();
        if (rec == DialogLogIn_ui::Accepted)
        {
            logIn(dia->getUser().getID());
        }
    }
    else
    {

    }
}


void MainWindow::on_actionBasicPreserved_triggered()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    EditUserMessage_ui edit(m_user);
    edit.exec();
    ui->btnUser->setText(m_user.getUserName());
    QPixmap pix = m_user.getPix();
    if (!pix.isNull())
    {
        pix.scaled(ui->labelPicture->size(), Qt::KeepAspectRatio);
        ui->labelPicture->setScaledContents(true);
        ui->labelPicture->setPixmap(pix);
    }
}

void MainWindow::on_actionRealNameAuth_triggered()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    EditUserFile_ui* edit = new EditUserFile_ui(m_user);
    edit->exec();
}

void MainWindow::on_actionRecharge_triggered()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    reCharge_ui* recharge = new reCharge_ui(m_user);
    recharge->exec();
}

void MainWindow::on_actionResetCode_triggered()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    resetCode_ui * reset = new resetCode_ui(m_user);
    reset->exec();
}

void MainWindow::on_actionLogOut_triggered()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    logOut();
}

/*************************************************************************
【函数名称】        on_btnAllAssignment_clicked
【函数功能】        加载不同状态任务，以下同
【参数】
【返回值】
【开发者及日期】     7/31
*************************************************************************/
void MainWindow::on_btnAllAssign_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(m_user.all_assignment.size() / 3 + 1);
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->verticalHeader()->hide();
    for (int i = 0;i < m_user.all_assignment.size();i++)
    {
        assignmentShow_ui* aShow = new assignmentShow_ui(m_user, m_user.all_assignment[i], ui->tableWidget);
        ui->tableWidget->setColumnWidth(i % 3, 350);
        ui->tableWidget->setRowHeight(i / 3, 350);
        ui->tableWidget->setCellWidget(i / 3, i % 3, aShow);
        aShow->show();
    }
}

void MainWindow::on_btnFindManager_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(m_user.all_assignment.size() / 3 + 1);
    int index = 0;
    for (int i = 0;i < m_user.all_assignment.size();i++)
    {
        if ( m_user.all_assignment[i].getStatus() == RECRUITING_MANAGER)
        {
            assignmentShow_ui* aShow = new assignmentShow_ui(m_user,  m_user.all_assignment[i], ui->tableWidget);
            ui->tableWidget->setColumnWidth(index % 3, 350);
            ui->tableWidget->setRowHeight(index / 3, 350);
            ui->tableWidget->setCellWidget(index / 3, index % 3, aShow);
            aShow->show();
            index++;
        }
    }
}

void MainWindow::on_btnFindTran_clicked()
{

    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(m_user.all_assignment.size() / 3 + 1);
    int index = 0;
    for (int i = 0;i < m_user.all_assignment.size();i++)
    {
        if ( m_user.all_assignment[i].getStatus() == RECRUITING_TRANSLATOR)
        {
            assignmentShow_ui* aShow = new assignmentShow_ui(m_user, m_user.all_assignment[i], ui->tableWidget);
            ui->tableWidget->setColumnWidth(index % 3, 350);
            ui->tableWidget->setRowHeight(index / 3, 350);
            ui->tableWidget->setCellWidget(index / 3, index % 3, aShow);
            aShow->show();
            index++;
        }
    }
}

void MainWindow::on_btnProgressing_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(m_user.all_assignment.size() / 3 + 1);
    int index = 0;
    for (int i = 0;i < m_user.all_assignment.size();i++)
    {
        if ( m_user.all_assignment[i].getStatus() == PROCCESSING)
        {
            assignmentShow_ui* aShow = new assignmentShow_ui(m_user, m_user.all_assignment[i], ui->tableWidget);
            ui->tableWidget->setColumnWidth(index % 3, 350);
            ui->tableWidget->setRowHeight(index / 3, 350);
            ui->tableWidget->setCellWidget(index / 3, index % 3, aShow);
            aShow->show();
            index++;
        }
    }
}


/*************************************************************************
【函数名称】        on_btnMyPub_clicked
【函数功能】        加载用户在参与的任务，以下同
【参数】
【返回值】
【开发者及日期】     7/31
*************************************************************************/
void MainWindow::on_btnMyPub_clicked()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(m_user.m_userAsPublisher.size() / 3 + 1);
    for (int i = 0;i < m_user.m_userAsPublisher.size();i++)
    {
        assignmentShow_ui* aShow = new assignmentShow_ui(m_user, m_user.m_userAsPublisher[i], ui->tableWidget);
        ui->tableWidget->setColumnWidth(i % 3, 400);
        ui->tableWidget->setRowHeight(i / 3, 400);
        ui->tableWidget->setCellWidget(i / 3, i % 3, aShow);
        aShow->show();
    }
}

void MainWindow::on_btnMyManager_clicked()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(m_user.m_userAsManager.size() / 3 + 1);
    for (int i = 0;i < m_user.m_userAsManager.size();i++)
    {
        assignmentShow_ui* aShow = new assignmentShow_ui(m_user, m_user.m_userAsManager[i], ui->tableWidget);
        ui->tableWidget->setColumnWidth(i % 3, 350);
        ui->tableWidget->setRowHeight(i / 3, 350);
        ui->tableWidget->setCellWidget(i / 3, i % 3, aShow);
        aShow->show();
    }
}

void MainWindow::on_btnMyTran_clicked()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(m_user.m_userAsTrans.size() / 3 + 1);
    for (int i = 0;i < m_user.m_userAsTrans.size();i++)
    {
        assignmentShow_ui* aShow = new assignmentShow_ui(m_user, m_user.m_userAsTrans[i], ui->tableWidget);
        ui->tableWidget->setColumnWidth(i % 3, 350);
        ui->tableWidget->setRowHeight(i / 3, 350);
        ui->tableWidget->setCellWidget(i / 3, i % 3, aShow);
        aShow->show();

    }
}

void MainWindow::on_btnMyReview_clicked()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
}


void MainWindow::on_btnPublish_clicked()
{
    if (m_user.getID() == "")
    {
        m_QInformBox::warning(this, "提示", "请先登录！");
        return;
    }
    Publish_ui* publish = new Publish_ui(m_user);
    int ex = publish->exec();
    if (ex == QDialog::Accepted)
    {
         m_QInformBox::information(this, "提示", "发布成功！");
    }
}


/*************************************************************************
【函数名称】        on_actionSearch_triggered
【函数功能】        寻找任务
【参数】           任务名
【返回值】          任务基类对象
【开发者及日期】     8/2
*************************************************************************/
void MainWindow::on_actionSearch_triggered()
{
    QString name = ui->lineEdit->text();
    Assignment a(name);
    if (a.getName() == "")
    {
        m_QInformBox::warning(this, "提示","不存在该任务！");
        return;
    }
    AssignmentDetails_ui aD(m_user, a);
    aD.exec();
}

void MainWindow::on_action_triggered()
{
    PLATFORM_MANAGER_UI* p = new PLATFORM_MANAGER_UI;
    p->exec();
}
