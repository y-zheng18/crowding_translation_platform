#ifndef M_TABWIDGET_UI_H
#define M_TABWIDGET_UI_H

#include <QDialog>
#include "userplatform.h"
namespace Ui {
class m_tabWidget_ui;
}

class m_tabWidget_ui : public QDialog
{
    Q_OBJECT

public:
    explicit m_tabWidget_ui(UserPlatForm& u, QWidget *parent = nullptr);
    ~m_tabWidget_ui();

private:
    Ui::m_tabWidget_ui *ui;
    UserPlatForm& u_platform;
};

#endif // M_TABWIDGET_UI_H
