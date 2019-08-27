#ifndef ASMANAGER_UI_H
#define ASMANAGER_UI_H

#include "assignmentshow_ui.h"

namespace Ui {
class assignmentShow_ui;
}
class asManager_ui:public assignmentShow_ui
{
public:
    asManager_ui(User& u, AssignmentManager& a);

private:
    AssignmentManager& asManager;
    User& m_user;
};

#endif // ASMANAGER_UI_H
