#include "signupinteraction.h"

/*************************************************************************
【函数名称】        SignUpInteraction
【函数功能】        构造函数
【参数】           类成员值
【返回值】
【开发者及日期】     7/26
*************************************************************************/
SignUpInteraction::SignUpInteraction(const QString& assignmentName, const QString& selectorId,
                               const QString& candidateId, const ISCHOSEN& result):
    m_sAssignmentName(assignmentName), m_sSelectorID(selectorId),
    m_sCandidateID(candidateId), m_eResult(result)
{

}

SignUpInteraction::~SignUpInteraction()
{

}

void SignUpInteraction::setSelector(const QString& id)
{
    m_sSelectorID = id;
}

void SignUpInteraction::setCandidate(const QString& id)
{
    m_sCandidateID = id;
}

void SignUpInteraction::setAssignmentName(const QString& name)
{
    m_sAssignmentName = name;
}

void SignUpInteraction::setResult(const ISCHOSEN& result)
{
    m_eResult = result;
}

void SignUpInteraction::setPlatForm(const SIGNUP& form)
{
    m_ePlatform = form;
}
