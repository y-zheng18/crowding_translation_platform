#ifndef RESETCODE_UI_H
#define RESETCODE_UI_H
/*************************************************************************
【文件名】                resetCode_ui.h
【功能模块和目的】         重设密码
【开发者及日期】           2019/7/30
*************************************************************************/
#include <QDialog>
#include "user.h"
namespace Ui {
class resetCode_ui;
}

class resetCode_ui : public QDialog
{
    Q_OBJECT

public:
    explicit resetCode_ui(User& u, QWidget *parent = nullptr);
    ~resetCode_ui();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

private:
    Ui::resetCode_ui *ui;
    User& m_user;
};

#endif // RESETCODE_UI_H
