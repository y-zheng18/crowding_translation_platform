#ifndef PUBLISH_UI_H
#define PUBLISH_UI_H
/*************************************************************************
【文件名】                 publish.h
【功能模块和目的】          发布任务界面
【开发者及日期】           2019/7/31
*************************************************************************/
#include <QDialog>
#include "assignmentpublisher.h"
#include "user.h"
namespace Ui {
class Publish_ui;
}

class Publish_ui : public QDialog
{
    Q_OBJECT

public:
    explicit Publish_ui(User& user, QWidget *parent = nullptr);
    ~Publish_ui();
private slots:
    void on_btnCancel_clicked();

    void on_btnOK_clicked();

    void on_btnPic_clicked();

    void on_btnText_clicked();

private:
    Ui::Publish_ui *ui;
    User& m_user;
};

#endif // PUBLISH_UI_H
