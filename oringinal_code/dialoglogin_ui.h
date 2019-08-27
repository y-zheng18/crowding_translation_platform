#ifndef DIALOGLOGIN_H
#define DIALOGLOGIN_H

#include <QDialog>
#include "user.h"
namespace Ui {
class DialogLogIn;
}

class DialogLogIn_ui : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogIn_ui(QWidget *parent = nullptr);
    ~DialogLogIn_ui();
    void setUser(const User& user)
    {
        m_user = user;
    }

    const User& getUser()
    {
        return m_user;
    }
private slots:

    void on_btnClose_clicked();

    void on_btnLogIn_clicked();

    void on_btnRegister_clicked();

private:
    Ui::DialogLogIn *ui;
    User m_user;
};

#endif // DIALOGLOGIN_H
