#include "login_ui.h"
#include "ui_login_ui.h"

LogIn_ui::LogIn_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogIn_ui)
{
    ui->setupUi(this);
}

LogIn_ui::~LogIn_ui()
{
    delete ui;
}

void LogIn_ui::on_btnLogIn_clicked()
{

}
