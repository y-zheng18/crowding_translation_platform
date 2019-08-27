#ifndef ASSIGNMENTPUBLISHER_UI_H
#define ASSIGNMENTPUBLISHER_UI_H
#include "assignmentdetails_ui.h"

class assignmentPublisher_ui:public AssignmentDetails_ui
{
public:
    assignmentPublisher_ui(User& u, Assignment& a, QWidget *parent = nullptr);
private slots:
    void on_btnSignUp_clicked();
};

#endif // ASSIGNMENTPUBLISHER_UI_H
