#ifndef USERMESSAGE_UI_H
#define USERMESSAGE_UI_H
/*************************************************************************
【文件名】                usermessage_ui.h
【功能模块和目的】         用户数据详细平台
【开发者及日期】           2019/7/26
*************************************************************************/
#include <QDialog>
#include "user.h"

namespace Ui {
class userMessage_ui;
}

class userMessage_ui : public QDialog
{
    Q_OBJECT

public:
    explicit userMessage_ui(User& u, QWidget *parent = nullptr);
    ~userMessage_ui();

private slots:
    void on_btnClose_clicked();
private:
    Ui::userMessage_ui *ui;
    User& m_user;
};

#endif // USERMESSAGE_UI_H
