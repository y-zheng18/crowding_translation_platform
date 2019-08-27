#ifndef USERPLATFORM_H
#define USERPLATFORM_H

#include "user.h"
#include "assignment.h"
#include "assignmentmanager.h"
#include "assignmentpublisher.h"
#include "assignmenttranslator.h"
#include "messageinformbox.h"
#include "QVector"
class UserPlatForm
{
public:
    UserPlatForm();
    ~UserPlatForm();
    User m_user;
    QVector<Assignment> all_assignment;
    QVector<Assignment> Progressing;
    QVector<Assignment> recruitingTran;
    QVector<Assignment> recruitingManager;


    MessageInformBox m_box;
    void setID(const QString& id);
    const QString& getID() const
    {
        return m_sID;
    }

private:
    QString m_sID;
};

#endif // USERPLATFORM_H
