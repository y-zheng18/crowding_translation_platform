#include "asmanager_show_ui.h"

asManager_show_ui::asManager_show_ui(User& u, AssignmentManager& a) : assignmentShow_ui (u, a),
    asManager(a), m_user(u)
{
}
