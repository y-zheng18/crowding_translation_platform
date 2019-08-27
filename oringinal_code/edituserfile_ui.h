#ifndef EDITUSERFILE_UI_H
#define EDITUSERFILE_UI_H
/*************************************************************************
【文件名】                 editUserFile.h
【功能模块和目的】          用户资质 实名认证界面
【开发者及日期】           2019/7/30
*************************************************************************/
#include <QDialog>
#include "user.h"
namespace Ui {
class EditUserFile_ui;
}

class EditUserFile_ui : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserFile_ui(User& u, QWidget *parent = nullptr);
    ~EditUserFile_ui();


    void setUser(const User& u);
private slots:

    void on_pushButton_clicked();

    void on_toolButton_clicked();

    void on_toolButton_2_clicked();

private:
    Ui::EditUserFile_ui *ui;
    User& m_user;
};

#endif // EDITUSERFILE_UI_H
