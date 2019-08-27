#ifndef PLATFORM_MANAGER_UI_H
#define PLATFORM_MANAGER_UI_H
/*************************************************************************
【文件名】                 PLATFORM_MANAGER_UI.h
【功能模块和目的】          平台管理员界面
【开发者及日期】           2019/8/2
*************************************************************************/
#include <QDialog>
#include "user.h"
namespace Ui {
class PLATFORM_MANAGER_UI;
}

class PLATFORM_MANAGER_UI : public QDialog
{
    Q_OBJECT

public:
    explicit PLATFORM_MANAGER_UI(QWidget *parent = nullptr);
    ~PLATFORM_MANAGER_UI();

private slots:
    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_btnChoose_clicked();

private:
    Ui::PLATFORM_MANAGER_UI *ui;
    QVector<User> all_user;
};

#endif // PLATFORM_MANAGER_UI_H
