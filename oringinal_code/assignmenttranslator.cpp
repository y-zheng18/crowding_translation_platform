#include "assignmenttranslator.h"
#include "database.h"

AssignmentTranslator::AssignmentTranslator()
{

}

/*************************************************************************
【函数名称】        AssignmentTranslator
【函数功能】        仅加载数据使用，加载译者翻译情况及评价
【参数】
【返回值】
【开发者及日期】     7/29-30
*************************************************************************/
AssignmentTranslator::AssignmentTranslator(const QString& tranID, const QString &assignmentName):Assignment (assignmentName)
{
    m_sUserId = tranID;
    DataBaseAssignment db;
    TextInteraction p = db.getAssignmentText(m_sAssignmentName, tranID, TRANS_DOWNLOAD);
    if (p.getName() != "")
    {
        m_subAssignment = p;
    }
    p = db.getAssignmentText(m_sAssignmentName, tranID, TRANS_UPLOAD);
    if (p.getName() != "")
    {
        m_translatedText = p;
    }
    p = db.getAssignmentText(m_sAssignmentName, tranID, MANAGER_REVIEW);
    if (p.getName() != "")
    {
        m_managerReview = p;
    }
}

AssignmentTranslator::~AssignmentTranslator()
{

}


/*************************************************************************
【函数名称】        uploadText
【函数功能】        上传翻译文本
【参数】           文本路径
【返回值】          上传是否成功
【开发者及日期】     7/30
*************************************************************************/
bool AssignmentTranslator::uploadText(const QString& filePath)
{
    QFile m_file(filePath);
    if (!m_file.exists())
    {
        qDebug()<<"file open error!";
        return false;
    }
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"file read error!";
        return false;
    }
    QTextStream m_stream(&m_file);
    QString text = m_stream.readAll();
    m_translatedText = TextInteraction(m_sAssignmentName, m_sUserId, text);
    m_translatedText.setPlatForm(TRANS_UPLOAD);
    QString messageText = QString("任务状态变更提醒：任务 %1 译者已提交译文").arg(m_sAssignmentName);
    Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sUserId, m_sManagerID, messageText);
    //qDebug()<<" ";
    //messageBox机制
    return true;
}

/*************************************************************************
【函数名称】        editTextOnline
【函数功能】        在线编辑，暂存文本
【参数】           文本内容
【返回值】
【开发者及日期】     7/30
*************************************************************************/
void AssignmentTranslator::editTextOnline(const QString& text)
{
    m_translatedText = TextInteraction(m_sAssignmentName, m_sUserId, text);
    m_translatedText.setPlatForm(TRANS_UPLOAD);
    QString messageText = QString("任务状态变更提醒：任务 %1 译者已暂存译文").arg(m_sAssignmentName);
    Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sUserId, m_sManagerID, messageText);
}
