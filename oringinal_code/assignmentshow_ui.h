#ifndef ASSIGNMENTSHOW_UI_H
#define ASSIGNMENTSHOW_UI_H

/*************************************************************************
【文件名】                 assignmentShow_ui
【功能模块和目的】          实现任务抽象展示界面，设置接口跳转到详细任务界面
【开发者及日期】           2019/7/29-8/1
*************************************************************************/
#include <QDialog>
#include "assignment.h"
#include "user.h"
namespace Ui {
class assignmentShow_ui;
}

class assignmentShow_ui : public QDialog
{
    Q_OBJECT

public:
    explicit assignmentShow_ui(User& u, Assignment& a, QWidget *parent = nullptr);
    ~assignmentShow_ui();
    Assignment& getAssignment()
    {
        return m_assignment;
    }
protected slots:
    void on_btnShowDetails_clicked();                               //实现界面跳转
protected:
    Ui::assignmentShow_ui *ui;
    Assignment& m_assignment;
    User& m_user;
};

#endif // ASSIGNMENTSHOW_UI_H
