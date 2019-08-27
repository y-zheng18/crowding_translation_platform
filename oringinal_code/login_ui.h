#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include <QDialog>

namespace Ui {
class LogIn_ui;
}

class LogIn_ui : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn_ui(QWidget *parent = nullptr);
    ~LogIn_ui();

private slots:
    void on_btnLogIn_clicked();

private:
    Ui::LogIn_ui *ui;
};

#endif // LOGIN_UI_H
