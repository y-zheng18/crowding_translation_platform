#include "assignment.h"
#include "database.h"

Assignment::Assignment()
{

}

/*************************************************************************
【函数名称】         Assignment
【函数功能】       构造函数，用于加载数据
【参数】           类各属性
【返回值】
【开发者及日期】   7/23
*************************************************************************/
Assignment::Assignment(const QString &assignmentName, const QString &publisherID,
                       const QString &managerID, const QStringList &translatorID,
                       const QString &description, const int &status,
                       const int &form, const float &reward,
                       const QString &assignmentText, const QStringList& keywords,
                       const QPixmap &pix):
    m_sAssignmentName(assignmentName), m_sPublisherID(publisherID),
    m_sManagerID(managerID), m_slTranslatorID(translatorID),
    m_sDescription(description), m_eStatus(STATUS(status)),
    m_eTranslationForm(LANGUAGE(form)), m_fReward(reward),
    m_sAssignmentText(assignmentText), m_pixPicture(pix),
    m_keyWords(keywords)
{

}


/*************************************************************************
【函数名称】         Assignment
【函数功能】        构造函数，用于从数据库加载数据
【参数】            类各属性
【返回值】
【开发者及日期】    7/26
*************************************************************************/
Assignment::Assignment(const QString &assignmentName)           //
{
    DataBaseAssignment db;
    Assignment assmnt = db.getAssignment(assignmentName);
    if (assmnt.getName() != "")
    {
        *this = assmnt;
    }
    DataBasePicture dbp;
    dbp.setTableName("assignmentPicture");
    dbp.getPictures(assignmentName, m_pixPicture);
}

Assignment::Assignment(const QString &id, const QString &assignmentName):
    m_sAssignmentName(assignmentName), m_sUserId(id)
{

}


/*************************************************************************
【函数名称】         ~Assignment
【函数功能】        析构函数，用于写入数据
【参数】
【返回值】
【开发者及日期】     7/28
*************************************************************************/
Assignment::~Assignment()               //将assignment基本数据存入数据库"assignment"（文本内容另存在"assignmentPublisher"）
{
    if (m_sAssignmentName == "")
        return;
    DataBaseAssignment db;
    db.setTableName("assignment");
    if (!db.search(m_sAssignmentName, "assignmentName"))
    {
        db.insertAssignment(*this);
    }
    else
    {
        db.updateAssignment(*this);
    }
}

void Assignment::setTranslators(const QStringList &l)
{
    m_slTranslatorID = l;
}

QString Assignment::getPublisherID() const
{
    return m_sPublisherID;
}

QString Assignment::getManagerID() const
{
    return m_sManagerID;
}

QStringList Assignment::getTranslaors() const
{
    return m_slTranslatorID;
}

QStringList Assignment::getKeywords() const
{
    return m_keyWords;
}

int Assignment::getStatus() const
{
    return m_eStatus;
}

int Assignment::getTranslationForm() const
{
    return m_eTranslationForm;
}

void Assignment::setPix(const QPixmap &pix)
{
    m_pixPicture = pix;
}

bool Assignment::uploadText(const QString &)
{
    return true;
}

bool Assignment::downloadText()  //子类中重写
{
    return true;
}

void Assignment::setDDL(const QDateTime& ddl)
{
    m_deadline = ddl;
}

void Assignment::setCurrentDDL(const QDateTime &ddl)
{
    m_currentDDL = ddl;
}

