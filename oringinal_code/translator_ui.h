#ifndef TRANSLATOR_UI_H
#define TRANSLATOR_UI_H
/*************************************************************************
【文件名】                Translator_ui.h
【功能模块和目的】         译者操作平台
【开发者及日期】           2019/7/31
*************************************************************************/
#include <QDialog>
#include "assignmenttranslator.h"
#include "user.h"
namespace Ui {
class translator_ui;
}

class translator_ui : public QDialog
{
    Q_OBJECT

public:
    explicit translator_ui(AssignmentTranslator& a, QWidget *parent = 0);
    ~translator_ui();

private slots:

    void on_toolButton_clicked();

    void on_btnOK_clicked();

    void on_btnCancel_clicked();

    void on_btnFinal_clicked();

private:
    Ui::translator_ui *ui;
    AssignmentTranslator& m_asTran;
};

#endif // TRANSLATOR_UI_H
