#include "userplatform.h"

UserPlatForm::UserPlatForm()
{
}

UserPlatForm::~UserPlatForm()
{

}

void UserPlatForm::setID(const QString &id)
{
    m_sID = id;
    m_user = User(id);
    m_user.getUserCertification();
    m_box = MessageInformBox(id);
    m_user.getAllAssignment();
    m_user.getUserAssignment();
    all_assignment = m_user.all_assignment;
    recruitingManager.clear();
    for (int i = 0;i < all_assignment.size();i++)
    {
        if (all_assignment[i].getStatus() == RECRUITING_MANAGER)
        {
            recruitingManager.push_back(all_assignment[i]);
        }
    }
    recruitingTran.clear();
    for (int i = 0;i < all_assignment.size();i++)
    {
        if (all_assignment[i].getStatus() == RECRUITING_TRANSLATOR)
        {
            recruitingTran.push_back(all_assignment[i]);
        }
    }
    Progressing.clear();
    for (int i = 0;i < all_assignment.size();i++)
    {
        if (all_assignment[i].getStatus() == PROCCESSING)
        {
            Progressing.push_back(all_assignment[i]);
        }
    }
}



