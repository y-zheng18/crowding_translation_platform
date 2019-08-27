#ifndef RECHARGE_UI_H
#define RECHARGE_UI_H
/*************************************************************************
【文件名】                 recharge_ui.h
【功能模块和目的】          支付界面
【开发者及日期】           2019/7/31
*************************************************************************/
#include <QDialog>
#include "user.h"
namespace Ui {
class reCharge_ui;
}

class reCharge_ui : public QDialog
{
    Q_OBJECT

public:
    explicit reCharge_ui(User& u, QWidget *parent = nullptr);
    ~reCharge_ui();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::reCharge_ui *ui;
    User& m_user;
};

#endif // RECHARGE_UI_H
