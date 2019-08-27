#ifndef CHOOSETRANSLATOR_UI_H
#define CHOOSETRANSLATOR_UI_H

#include <QDialog>
#include"user.h"
#include"assignmentmanager.h"

namespace Ui {
class chooseTranslator_ui;
}

class chooseTranslator_ui : public QDialog
{
    Q_OBJECT

public:
    explicit chooseTranslator_ui(User& u, AssignmentManager& asm, QWidget *parent = nullptr);
    ~chooseTranslator_ui();

private slots:
    void on_btnOK_clicked();

private:
    Ui::chooseTranslator_ui *ui;
    AssignmentManager& asManager;
    User& m_user;
};

#endif // CHOOSETRANSLATOR_UI_H
