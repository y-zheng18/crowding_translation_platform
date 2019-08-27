#ifndef MESSAGEINFORMBOX_UI_H
#define MESSAGEINFORMBOX_UI_H
/*************************************************************************
【文件名】                 messageInformBox_ui.h
【功能模块和目的】          消息盒子界面类
【开发者及日期】           2019/8/1
*************************************************************************/
#include <QDialog>
#include "messageinformbox.h"

namespace Ui {
class MessageInformBox_ui;
}

class MessageInformBox_ui : public QDialog
{
    Q_OBJECT

public:
    explicit MessageInformBox_ui(MessageInformBox& m, QWidget *parent = nullptr);
    ~MessageInformBox_ui();

private slots:
    void on_btnRead_clicked();

    void on_btnDelete_clicked();

private:
    Ui::MessageInformBox_ui *ui;
    MessageInformBox& m_message;
};

#endif // MESSAGEINFORMBOX_UI_H
