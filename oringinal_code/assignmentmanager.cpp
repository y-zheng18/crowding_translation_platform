#include "assignmentmanager.h"
#include "database.h"

AssignmentManager::AssignmentManager()
{

}
/*************************************************************************
【函数名称】         AssignmentManager
【函数功能】        构造函数，用于从数据库加载数据
【参数】            任务名
【返回值】
【开发者及日期】     7/29
*************************************************************************/
AssignmentManager::AssignmentManager(const QString& assignmentName):
    Assignment(assignmentName)
{
    m_sUserId = m_sManagerID;
    DataBaseAssignment db;
    m_subAssignment = QMap<QString, TextInteraction>();
    m_subTranlatedAssignment = QMap<QString, TextInteraction>();
    m_review = QMap<QString, TextInteraction>();
    for (int i = 0;i < m_slTranslatorID.size();i++)
    {
        TextInteraction p = db.getAssignmentText(m_sAssignmentName, m_slTranslatorID[i], TRANS_DOWNLOAD);
        if (p.getName() != "")
        {
            m_subAssignment.insert(m_slTranslatorID[i], p);
        }
        p = db.getAssignmentText(m_sAssignmentName, m_slTranslatorID[i], TRANS_UPLOAD);
        if (p.getName() != "")
        {
            m_subTranlatedAssignment.insert(m_slTranslatorID[i], p);
        }
        p = db.getAssignmentText(m_sAssignmentName, m_slTranslatorID[i], MANAGER_REVIEW);
        if (p.getName() != "")
        {
            m_review.insert(m_slTranslatorID[i], p);
        }
    }
    m_translatorSignUp = db.getSignUp(m_sAssignmentName, m_sManagerID, TRANS_SIGN_UP);
}

/*************************************************************************
【函数名称】         ~AssignmentManager
【函数功能】        析构函数，写入数据
【参数】
【返回值】
【开发者及日期】     7/29
*************************************************************************/
AssignmentManager::~AssignmentManager()
{
    if (m_sAssignmentName == "")
        return;
    DataBaseAssignment db;
    db.setTableName("translatorSignUp");
    for (int i = 0;i < m_translatorSignUp.size();i++)
    {
        db.updateSignUp(m_translatorSignUp[i]);
    }
}


/*************************************************************************
【函数名称】         setCurrentDDL
【函数功能】        设置译者报名ddl
【参数】            时间
【返回值】
【开发者及日期】     7/30
*************************************************************************/
void AssignmentManager::setCurrentDDL(const QDateTime& ddl)
{
    m_eStatus = RECRUITING_TRANSLATOR;
    m_currentDDL = ddl;
}

void AssignmentManager::setDDL(const QDateTime &ddl)
{
    m_currentDDL = ddl;
    for (int i = 0;i < m_translatorSignUp.size();i++)
    {
        if (m_translatorSignUp[i].getResult() != CHOSEN)
        {
            m_translatorSignUp[i].setResult(NOTCHOSEN);
            QString messageText = QString("很遗憾你在任务 %1 中未被选为译者.").arg(m_sAssignmentName);
            Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sManagerID,
                      m_translatorSignUp[i].getCandidate(), messageText);
            //messageBox
        }
        else
        {
            QString messageText = QString("任务状态变更提醒：任务 %1 翻译提交截至日期为：\n %2").arg(m_sAssignmentName).arg(ddl.toString());
            Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sManagerID,
                      m_translatorSignUp[i].getCandidate(), messageText);
        }
    }
}


/*************************************************************************
【函数名称】         chooseTranslator
【函数功能】        选择译者
【参数】            译者ID
【返回值】
【开发者及日期】     7/30
*************************************************************************/
bool AssignmentManager::chooseTranslator(const QString &tranID)
{
    for (int i = 0;i < m_translatorSignUp.size();i++)
    {
        if (m_translatorSignUp[i].getCandidate() == tranID
                && m_translatorSignUp[i].getResult() != CHOSEN)
        {
            QString messageText = QString("任务状态变更提醒：您已被任务 %1 负责人选为译者").arg(m_sAssignmentName);
            Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sManagerID, tranID, messageText);
            m_translatorSignUp[i].setResult(CHOSEN);
            m_slTranslatorID.push_back(tranID);
            return true;
            //messageBox
        }
    }
    return false;
}


/*************************************************************************
【函数名称】        allocateAssignment
【函数功能】        分配任务
【参数】            译者ID、任务文本路径
【返回值】
【开发者及日期】     7/30
*************************************************************************/
bool AssignmentManager::allocateAssignment(const QString& tranID, const QString& filePath)
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
    QString subText = m_stream.readAll();
    TextInteraction text(m_sAssignmentName, tranID,  subText, TRANS_DOWNLOAD);
    if (m_subAssignment[tranID].getName() == "")
    {
        m_subAssignment.insert(tranID, text);
    }
    else
    {
        m_subAssignment[tranID] = text;
    }
    QString messageText = QString("任务状态变更提醒：任务 %1 负责人已下发任务").arg(m_sAssignmentName);
    Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sManagerID, tranID, messageText);
    //messageBox机制
    return true;

}


/*************************************************************************
【函数名称】        giveReview
【函数功能】        给予评价
【参数】           译者ID、评价文本
【返回值】
【开发者及日期】     7/30
*************************************************************************/
void AssignmentManager::giveReview(const QString& tranID, const QString& review)
{
    if (m_review[tranID].getName() == "")
    {
        TextInteraction text(m_sAssignmentName, tranID,  review, MANAGER_REVIEW);
        m_review.insert(tranID, text);
    }
    else
    {
        QString all_review = m_review[tranID].getText();
        all_review += "\n";
        all_review += "\n";
        all_review += review;
        m_review[tranID].setFiletext(all_review);
    }
    QString messageText = QString("任务状态变更提醒：任务 %1 负责人对你的翻译任务有新的评价").arg(m_sAssignmentName);
    Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sManagerID, tranID, messageText);
    //messageBox机制
}

/*************************************************************************
【函数名称】        setStatusProcess
【函数功能】        设置任务翻译开始
【返回值】
【开发者及日期】     7/30
*************************************************************************/
void AssignmentManager::setStatusProcess()
{
    m_eStatus = PROCCESSING;
}

void AssignmentManager::setStatusDone()
{
    m_eStatus = ASSIGNMENT_DONE;
}

/*************************************************************************
【函数名称】        payReward
【函数功能】        支付
【返回值】
【开发者及日期】     7/30
*************************************************************************/
float AssignmentManager::payReward()
{
    DataBaseUser db;
    if (!db.search(m_sPublisherID, "id"))
    {
        qDebug()<<"manager doesn't exist!";
        return -1;
    }
    User manager = db.getUser(m_sManagerID);
    if (manager.getUserName() == "")
    {
        return -1;
    }
    float money = manager.getMoney();
    float money_to_pay = m_fReward * 3 / 4;
    if (money < money_to_pay)
        return -1;
    money -= money_to_pay;
    manager.setMoney(money);
    for (int i = 0;i < m_slTranslatorID.size();i++)
    {
        User trans;
        trans = db.getUser(m_slTranslatorID[i]);
        if (trans.getUserName() == "")
        {
            continue;
        }
        money = trans.getMoney();
        money += money_to_pay / m_slTranslatorID.size();
        trans.setMoney(money);
        int score = trans.getScore();
        trans.setScore(score + 1);
        QString messageText = QString("任务状态变更提醒：任务 %1 负责人已下发酬金，请注意查收").arg(m_sAssignmentName);
        Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sManagerID, m_slTranslatorID[i], messageText);
        //messageBox机制，即使提醒
    }
    return money_to_pay;
}

/*************************************************************************
【函数名称】        uploadText
【函数功能】        上传最终文本
【参数】           文本路径
【返回值】
【开发者及日期】     7/30
*************************************************************************/
bool AssignmentManager::uploadText(const QString& filePath)
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
    m_sAssignmentText = m_stream.readAll();
    m_finalText = TextInteraction(m_sAssignmentName, m_sManagerID, m_sAssignmentText);
    m_finalText.setPlatForm(MANAGER_UPLOAD);
    //qDebug()<<" ";
    QString messageText = QString("任务状态变更提醒：任务 %1 负责人已上传最终译稿").arg(m_sAssignmentName);
    Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sManagerID, m_sPublisherID, messageText);
    //messageBox机制，即使提醒
    return true;
}



