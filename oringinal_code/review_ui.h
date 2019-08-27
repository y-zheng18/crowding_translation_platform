#ifndef REVIEW_UI_H
#define REVIEW_UI_H
/*************************************************************************
【文件名】                review_ui.h
【功能模块和目的】         负责人分配任务以及评价界面
【开发者及日期】           2019/8/1
*************************************************************************/
#include <QDialog>
#include "m_QInformbox.h"
#include "user.h"
#include "assignmentmanager.h"
namespace Ui {
class Review_ui;
}

class Review_ui : public QDialog
{
    Q_OBJECT

public:
    explicit Review_ui(User& u, AssignmentManager& a, QWidget *parent = nullptr);
    ~Review_ui();

private slots:
    void on_btnChoose_clicked();

    void on_btnDownload_clicked();

    void on_btnOK_clicked();

    void on_toolButton_clicked();

    
    void on_btnCancel_clicked();
    
private:
    Ui::Review_ui *ui;
    AssignmentManager& m_asManager;

    User& m_user;
    int m_iStatus;          //记录分配任务或是上传评价
};

#endif // REVIEW_UI_H
