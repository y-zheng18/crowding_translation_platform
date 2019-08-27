#ifndef ALLOCATE_UI_H
#define ALLOCATE_UI_H

#include <QDialog>

namespace Ui {
class Allocate_ui;
}

class Allocate_ui : public QDialog
{
    Q_OBJECT

public:
    explicit Allocate_ui(QWidget *parent = nullptr);
    ~Allocate_ui();

private:
    Ui::Allocate_ui *ui;
};

#endif // ALLOCATE_UI_H
