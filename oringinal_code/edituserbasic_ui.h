#ifndef EDITUSERBASIC_UI_H
#define EDITUSERBASIC_UI_H

#include <QDialog>
#include "user.h"
namespace Ui {
class editUserBasic_ui;
}

class editUserBasic_ui : public QDialog
{
    Q_OBJECT

public:
    explicit editUserBasic_ui(User& u, QWidget *parent = nullptr);
    ~editUserBasic_ui();

private slots:

    void on_btnClose_clicked();

private:
    Ui::editUserBasic_ui *ui;
    User& m_user;
};

#endif // EDITUSERBASIC_UI_H
