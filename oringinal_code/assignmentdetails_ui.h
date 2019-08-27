#ifndef ASSIGNMENTDETAILS_UI_H
#define ASSIGNMENTDETAILS_UI_H

/*************************************************************************
【文件名】                 AssignmentDetails_ui
【功能模块和目的】          实现任务类基本属性展示
【开发者及日期】           2019/7/31
*************************************************************************/
#include <QDialog>
#include "assignment.h"
#include "user.h"

/*************************************************************************
【类名】             AssignmentDetails_ui
【功能】             实现任务基本功能，展示任务基本属性（如ddl、发布者等）
【接口说明】         get接口：获取类内部引用对象；槽函数等
【开发者及日期】     2019/7/31
【更改记录】
*************************************************************************/
namespace Ui {
class AssignmentDetails_ui;
}

class AssignmentDetails_ui : public QDialog
{
    Q_OBJECT

public:
    explicit AssignmentDetails_ui(User& u, Assignment& a, QWidget *parent = nullptr);
    ~AssignmentDetails_ui();

    void setAssignment(const Assignment& assignment);



    const Assignment& getAssignment() const
    {
        return m_assignment;
    }

    const User& getUser() const
    {
        return m_User;
    }
private slots:
    void on_btnClose_clicked();

    void on_btnSignUp_clicked();

    void on_btnPublisher_clicked();

    void on_btnManager_clicked();

protected:
    Ui::AssignmentDetails_ui *ui;
    Assignment& m_assignment;
    User& m_User;
private slots:
    void on_btndownload_clicked();
};

#endif // ASSIGNMENTDETAILS_UI_H
