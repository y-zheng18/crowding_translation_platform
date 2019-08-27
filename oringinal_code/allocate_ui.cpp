#include "allocate_ui.h"
#include "ui_allocate_ui.h"

Allocate_ui::Allocate_ui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Allocate_ui)
{
    ui->setupUi(this);
}

Allocate_ui::~Allocate_ui()
{
    delete ui;
}
