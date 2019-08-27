#ifndef REGISTER_UI_H
#define REGISTER_UI_H
/*************************************************************************
【文件名】                Register_ui.h
【功能模块和目的】         注册界面
【开发者及日期】           2019/7/30
*************************************************************************/
#include <QDialog>
#include "user.h"
namespace Ui {
class Register_ui;
}

class Register_ui : public QDialog
{
    Q_OBJECT

public:
    explicit Register_ui(QWidget *parent = nullptr);
    ~Register_ui();
    const User& getUser()const
    {
        return m_user;
    }

private slots:
    void on_btnRegister_clicked();

    void on_btnCancel_clicked();

private:
    Ui::Register_ui *ui;
    User m_user;
};

#endif // REGISTER_UI_H
