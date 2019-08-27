#include "choosetranslator_ui.h"
#include "ui_choosetranslator_ui.h"

chooseTranslator_ui::chooseTranslator_ui(User& u, AssignmentManager& asm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::chooseTranslator_ui)
{
    ui->setupUi(this);
}

chooseTranslator_ui::~chooseTranslator_ui()
{
    delete ui;
}

void chooseTranslator_ui::on_btnOK_clicked()
{

}
