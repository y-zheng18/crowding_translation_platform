#ifndef ASMANAGER_SHOW_UI_H
#define ASMANAGER_SHOW_UI_H

#include "assignmentshow_ui.h"

class asManager_show_ui : public assignmentShow_ui
{
public:
    asManager_show_ui(User& u, AssignmentManager& a);


private:
    AssignmentManager& asManager;
    User& m_user;
};

#endif // ASMANAGER_SHOW_UI_H
