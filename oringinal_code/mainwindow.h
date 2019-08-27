#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*************************************************************************
【文件名】                 mainWindow.h
【功能模块和目的】          主界面，用于登陆、任务操作、基本信息更新维护
【开发者及日期】           2019/7/21-2019/8/2
*************************************************************************/
#include <QMainWindow>
#include "userplatform.h"
#include <QPoint>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void logIn(const QString& id);
    void logOut();
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent*e);
    void mousePressEvent(QMouseEvent* e);
private slots:
    void on_btnMin_clicked();

    void on_btnClose_clicked();

    void on_btnMessage_clicked();

    void on_btnUser_clicked();


    void on_actionBasicPreserved_triggered();

    void on_actionRealNameAuth_triggered();

    void on_actionRecharge_triggered();

    void on_actionResetCode_triggered();

    void on_actionLogOut_triggered();

    void on_btnAllAssign_clicked();

    void on_btnFindManager_clicked();

    void on_btnFindTran_clicked();

    void on_btnProgressing_clicked();

    void on_btnMyPub_clicked();

    void on_btnMyManager_clicked();

    void on_btnMyTran_clicked();

    void on_btnMyReview_clicked();

    void on_btnPublish_clicked();

    void on_actionSearch_triggered();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    User m_user;
    MessageInformBox m_box;
    bool m_bWindowMovable;             //记录鼠标状态，点击表示可移动
    QPoint m_move;                     //记录鼠标移动
    QPoint m_press;                    //记录鼠标点击位置
};

#endif // MAINWINDOW_H
