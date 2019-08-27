#ifndef CHOOSETRANS_UI_H
#define CHOOSETRANS_UI_H


/*************************************************************************
【文件名】                 chooseTrans_ui
【功能模块和目的】          选择译者界面
【开发者及日期】           2019/7/31
*************************************************************************/
#include <QDialog>
#include "user.h"
#include "assignmentpublisher.h"
#include "assignmentpublisher.h"
namespace Ui {
class chooseTrans_ui;
}

class chooseTrans_ui : public QDialog
{
    Q_OBJECT

public:
    explicit chooseTrans_ui(User& u, AssignmentManager& a, QWidget *parent = nullptr);
    ~chooseTrans_ui();

private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

    void on_btnChoose_clicked();

    void on_btnChooseTime_clicked();

private:
    Ui::chooseTrans_ui *ui;
    AssignmentManager& m_asManager;
    User& m_user;
};

#endif // CHOOSETRANS_UI_H
