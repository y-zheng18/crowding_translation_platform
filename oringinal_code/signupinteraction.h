#ifndef SIGNUPPLATFORM_H
#define SIGNUPPLATFORM_H
/*************************************************************************
【文件名】                signupinteraction.h
【功能模块和目的】           报名平台
【开发者及日期】           2019/7/26-27
*************************************************************************/
#include "QString"


//报名与录取平台，功能为：任务发布者招募负责人，负责人报名，上传负责人信息，任务发布者选择负责人；负责人招募译者，译者报名，上传译者信息，负责人选择译者
//储存格式为：任务名+负责选拔者ID+报名者ID+报名者状态（被选中，未被选中，未知）

enum SIGNUP{MANAGER_SIGN_UP, TRANS_SIGN_UP};
enum ISCHOSEN{CHOSEN, NOTCHOSEN, UNKNOWN};
/*************************************************************************
【类名】             SignUpInteraction
【功能】             实现报名信息交互
【接口说明】         set接口：设置类内部私有变量；get接口：获取类内部私有变量
【开发者及日期】      2019/7/26-27
【更改记录】
*************************************************************************/
class SignUpInteraction
{
public:
    SignUpInteraction(const QString& assignmentName = "", const QString& selectorId = "",
                   const QString& candidateId = "", const ISCHOSEN& result = UNKNOWN);

    virtual ~SignUpInteraction();

    QString getName() const
    {
        return m_sAssignmentName;
    }

    QString getSelector() const
    {
        return m_sSelectorID;
    }

    QString getCandidate() const
    {
        return m_sCandidateID;
    }

    SIGNUP getPlatForm() const
    {
        return m_ePlatform;
    }

    ISCHOSEN getResult() const
    {
        return m_eResult;
    }

    void setSelector(const QString& id);
    void setCandidate(const QString& id);
    void setAssignmentName(const QString& name);
    void setResult(const ISCHOSEN& result);
    void setPlatForm(const SIGNUP& form);
private:
    QString  m_sAssignmentName;
    QString  m_sSelectorID;
    QString  m_sCandidateID;
    ISCHOSEN m_eResult;
    SIGNUP   m_ePlatform;
};

#endif // SIGNUPPLATFORM_H
