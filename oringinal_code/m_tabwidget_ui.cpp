#include "m_tabwidget_ui.h"
#include "ui_m_tabwidget_ui.h"
#include "assignmentshow_ui.h"

m_tabWidget_ui::m_tabWidget_ui(UserPlatForm &u, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::m_tabWidget_ui),
    u_platform(u)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->hide();
    ui->tableWidget->setColumnCount(4);
    for (int i = 0;i < u_platform.all_assignment.size();i++)
    {
        assignmentShow_ui* aShow = new assignmentShow_ui(u_platform.m_user, u_platform.all_assignment[i]);
        ui->tableWidget->setCellWidget(i / 4, i % 4, aShow);
    }

}

m_tabWidget_ui::~m_tabWidget_ui()
{
    delete ui;
}
