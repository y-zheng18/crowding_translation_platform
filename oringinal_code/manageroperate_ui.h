#ifndef MANAGEROPERATE_UI_H
#define MANAGEROPERATE_UI_H
/*************************************************************************
【文件名】                 ManagerOperate_ui.h
【功能模块和目的】          负责人操作界面
【开发者及日期】           2019/8/1
*************************************************************************/
#include <QDialog>
#include "assignment.h"
#include "user.h"
#include "m_QInformbox.h"
namespace Ui {
class ManagerOperate_ui;
}

class ManagerOperate_ui : public QDialog
{
    Q_OBJECT

public:
    explicit ManagerOperate_ui(User& u, AssignmentManager& a, QWidget *parent = nullptr);
    ~ManagerOperate_ui();

private slots:
    void on_btnOK_clicked();

    void on_btnload_clicked();

    void on_toolButton_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ManagerOperate_ui *ui;
    AssignmentManager& asManager;
    User& m_user;
};

#endif // MANAGEROPERATE_UI_H
