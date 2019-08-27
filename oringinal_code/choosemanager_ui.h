#ifndef CHOOSEMANAGER_H
#define CHOOSEMANAGER_H


/*************************************************************************
【文件名】                 ChooseManager
【功能模块和目的】          发布者选择负责人界面
【开发者及日期】           2019/7/31
*************************************************************************/
#include <QDialog>
#include "assignmentpublisher.h"
#include "user.h"
namespace Ui {
class ChooseManager;
}

class ChooseManager_ui : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseManager_ui(User& u, AssignmentPublisher& asP, QWidget *parent = nullptr);
    ~ChooseManager_ui();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_btnText_clicked();

    void on_btnPic_clicked();

    void on_btnChoose_clicked();

private:
    Ui::ChooseManager *ui;
    AssignmentPublisher& m_asPubl;
    User& m_user;
};

#endif // CHOOSEMANAGER_H
