#ifndef EDITUSERMESSAGE_UI_H
#define EDITUSERMESSAGE_UI_H
/*************************************************************************
【文件名】                 editUserMessage.h
【功能模块和目的】          用户基本信息维护
【开发者及日期】           2019/7/30
*************************************************************************/
#include <QDialog>
#include "user.h"
#include "database.h"
#include "m_QInformbox.h"


namespace Ui {
class EditUserMessage_ui;
}

class EditUserMessage_ui : public QDialog
{
    Q_OBJECT

public:
    explicit EditUserMessage_ui(User& u, QWidget *parent = nullptr);
    ~EditUserMessage_ui();

private slots:
    void on_btnClose_clicked();

    void on_toolButton_clicked();

    void on_pushButton_clicked();

    void on_btnEditName_clicked();

    void on_btnEmail_clicked();

    void on_btnCharge_clicked();

private:
    Ui::EditUserMessage_ui *ui;
    User& m_user;
};

#endif // EDITUSERMESSAGE_UI_H
