#include "textinteraction.h"
#include "database.h"
TextInteraction::TextInteraction(const QString& assignmentName, const QString& id, const QString& text, const PLATFORM& form):
    m_sAssignmentName(assignmentName), m_sId(id), m_sFileText(text), m_ePlatform(form)
{

}
/*************************************************************************
【函数名称】        textInteraction
【函数功能】        析构函数，写入数据库
【参数】
【返回值】
【开发者及日期】     7/28
*************************************************************************/
TextInteraction::~TextInteraction()
{
    if (m_ePlatform >= 0 && m_ePlatform <= 4 && m_sAssignmentName != "")
    {
        DataBaseAssignment db;
        if (!db.updateAssignmentText(*this))
        {
            db.insertAssignmentText(*this);
        }
    }
}

void TextInteraction::setID(const QString &id)
{
    m_sId = id;
}

void TextInteraction::setAssignmentName(const QString &name)
{
    m_sAssignmentName = name;
}

void TextInteraction::setFiletext(const QString &text)
{
    m_sFileText = text;
}

void TextInteraction::setPlatForm(const PLATFORM& form)
{
    m_ePlatform = form;
}
