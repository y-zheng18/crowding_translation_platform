#include "assignmentpublisher.h"
#include "database.h"

AssignmentPublisher::AssignmentPublisher()
{
}

/*************************************************************************
【函数名称】        AssignmentPublisher
【函数功能】        构造函数，仅第一次发布任务使用
【参数】           发布者ID，任务名
【返回值】
【开发者及日期】     7/28
*************************************************************************/
AssignmentPublisher::AssignmentPublisher(const QString& id, const QString& assignmentName)
{
    m_sUserId = id;
    m_sAssignmentName = assignmentName;
    m_sPublisherID = id;
    m_eStatus = RECRUITING_MANAGER;
    m_keyWords = QStringList();
}

/*************************************************************************
【函数名称】        AssignmentPublisher
【函数功能】        构造函数，加载任务属性、报名情况等
【参数】           任务名
【返回值】
【开发者及日期】     7/28-7/29
*************************************************************************/
AssignmentPublisher::AssignmentPublisher(const QString &assignmentName) : Assignment(assignmentName)
{
    /*m_textManagment = TextInteraction(m_sAssignmentName, m_sPublisherID, m_sAssignmentText);
    m_textManagment.setPlatForm(MANAGER_DOWNLOAD);*/
    DataBaseAssignment db;
    TextInteraction p = db.getAssignmentText(m_sAssignmentName, m_sPublisherID, MANAGER_DOWNLOAD);
    if (p.getName() != "")
    {
        m_textManagement = p;
    }
    m_managerSignUp = db.getSignUp(m_sAssignmentName, m_sPublisherID, MANAGER_SIGN_UP);
    //db.setTableName("assignmentPublisher");
    //m_sAssignmentText = db.getAssignmentText(assignmentName, m_sPublisherID);
}


/*************************************************************************
【函数名称】        ~AssignmentPublisher
【函数功能】        析构函数,将任务名、发布者id、任务文本写入数据库
【参数】           发布者ID，任务名
【返回值】
【开发者及日期】     7/28
*************************************************************************/
AssignmentPublisher::~AssignmentPublisher()         //析构时将任务名、发布者id、任务文本写入数据库
{
    if (m_sAssignmentName == "")
        return;
    DataBasePicture dbp;
    //qDebug()<<this->getReward();
    dbp.setTableName("assignmentPicture");
    if (!dbp.search(m_sAssignmentName))
    {
        dbp.insertPictures(m_sAssignmentName, m_pixPicture);
    }
    else
    {
        dbp.updataPixture(m_sAssignmentName, m_pixPicture);
    }

    DataBaseAssignment db;
    for (int i = 0;i < m_managerSignUp.size();i++)
    {
        if (!db.updateSignUp(m_managerSignUp[i]))               //更新相当于查询是否存在，不存在则新插入
        {
            db.insertSignUp(m_managerSignUp[i]);
        }
    }
}

/*************************************************************************
【函数名称】        chooseManager
【函数功能】        选择负责人
【参数】           负责人ID
【返回值】
【开发者及日期】     7/28
*************************************************************************/
void AssignmentPublisher::chooseManager(const QString& managerID)
{
    m_sManagerID = managerID;
    DataBaseAssignment db;
    for (int i = 0;i < m_managerSignUp.size();i++)
    {
        if (m_managerSignUp[i].getCandidate() == managerID)
        {
            m_managerSignUp[i].setResult(CHOSEN);
            //messageBox机制
            QString messageText = QString("您在任务 %1 中被选为负责人！").arg(m_sAssignmentName);
            Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sPublisherID, managerID, messageText);

        }
        else
        {
            //messageBox机制
            QString messageText = QString("很遗憾您在任务 %1 中未能被选为负责人！").arg(m_sAssignmentName);
            Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sPublisherID,
                      m_managerSignUp[i].getCandidate(), messageText);
            m_managerSignUp[i].setResult(NOTCHOSEN);
        }
    }
    m_eStatus = MANAGER_RECUIT_DONE;

}

/*************************************************************************
【函数名称】        uploadText(
【函数功能】        上传任务文本
【参数】           文本路径
【返回值】
【开发者及日期】     7/28
*************************************************************************/
bool AssignmentPublisher::uploadText(const QString& filePath)
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
    m_textManagement = TextInteraction(m_sAssignmentName, m_sPublisherID, m_sAssignmentText);
    m_textManagement.setPlatForm(MANAGER_DOWNLOAD);
    //qDebug()<<" ";
    //messageBox机制
    return true;
}


/*************************************************************************
【函数名称】        downloadText
【函数功能】        下载最终文本
【参数】
【返回值】
【开发者及日期】     7/28
*************************************************************************/
bool AssignmentPublisher::downloadText()
{
    DataBaseAssignment db;
    TextInteraction text = db.getAssignmentText(m_sAssignmentName, m_sManagerID, MANAGER_UPLOAD);
    if (text.getName() != "")
    {
        m_finalText = text;
        return true;
    }
    return false;
}

/*************************************************************************
【函数名称】        getFinalTranslation
【函数功能】        下载最终文本
【参数】
【返回值】
【开发者及日期】     7/28
*************************************************************************/
QString AssignmentPublisher::getFinalTranslation()
{
    if (downloadText())
    {
        return m_finalText.getText();
    }
    return "";
}


/*************************************************************************
【函数名称】        getSignUp
【函数功能】        获得报名情况
【参数】
【返回值】
【开发者及日期】     7/29
*************************************************************************/
const QVector<SignUpInteraction>& AssignmentPublisher::getSignUp() const
{
    return m_managerSignUp;
}


bool AssignmentPublisher::setStatus(const int& status)
{
    if (status == 0)
    {
        m_eStatus = RECRUITING_MANAGER;
        return true;
    }
    if (status == 3)
    {
        m_eStatus = ASSIGNMENT_DONE;
        return true;
    }
    return false;
}

/*************************************************************************
【函数名称】        setreward
【函数功能】        设置酬金
【参数】
【返回值】
【开发者及日期】     7/29
*************************************************************************/
bool AssignmentPublisher::setReward(const float& money)
{
    DataBaseUser db;
    if (!db.search(m_sPublisherID, "id"))
    {
        qDebug()<<"publisher doesn't exist!";
        return false;
    }
    float publisher_money = db.getUser(m_sPublisherID).getMoney();
    if (publisher_money < money)
    {
        qDebug()<<"publisher doesn't have enough money!";
        return false;
    }
    m_fReward = money;
    return true;
}

bool AssignmentPublisher::setTranlationForm(const int& form)
{
    if (form == 1)
    {
        m_eTranslationForm = ENGLISH_TO_CHINESE;
        return true;
    }
    if (form == 0)
    {
        m_eTranslationForm = CHINESE_TO_ENGLISH;
        return true;
    }
    return false;
}

/*************************************************************************
【函数名称】        setDDL
【函数功能】        设置总任务截止时间
【参数】
【返回值】
【开发者及日期】     7/29
*************************************************************************/
void AssignmentPublisher::setDDL(const QDateTime &ddl)
{
    m_deadline = ddl;
}

/*************************************************************************
【函数名称】        setCurrentDDL
【函数功能】        设置当前报名截止时间
【参数】
【返回值】
【开发者及日期】     7/29
*************************************************************************/
void AssignmentPublisher::setCurrentDDL(const QDateTime &ddl)
{
    m_eStatus= RECRUITING_MANAGER;
    m_currentDDL = ddl;
}

bool AssignmentPublisher::uploadPictureMessage(const QString& fileName)
{
    QPixmap pix;
    if (!pix.load(fileName))
    {
        qDebug()<<"load picture error!";
        return false;
    }
    m_pixPicture = pix;
    return true;
}

void AssignmentPublisher::addKeywords(const QString &key)
{
    m_keyWords.push_back(key);
}


/*************************************************************************
【函数名称】        payReward
【函数功能】        支付
【参数】
【返回值】
【开发者及日期】     7/29
*************************************************************************/
float AssignmentPublisher::payReward()          //扣钱
{
    DataBaseUser db;
    if (!db.search(m_sPublisherID, "id"))
    {
        qDebug()<<"publisher doesn't exist!";
        return -1;
    }
    User publisher = db.getUser(m_sPublisherID);
    if (publisher.getUserName() == "")
    {
        return -1;
    }
    float money = publisher.getMoney();
    if (money < m_fReward)
        return -1;
    money -= m_fReward;
    publisher.setMoney(money);
    User manager = db.getUser(m_sManagerID);
    if (manager.getUserName() == "")
        return -1;
    money = manager.getMoney();
    money += m_fReward;
    manager.setMoney(money);
    m_eStatus = ASSIGNMENT_DONE;
    QString messageText = QString("任务状态变更提醒：任务 %1 发布者已下发酬金，请注意查收并分配酬金").arg(m_sAssignmentName);
    Message m(QDateTime::currentDateTime(), m_sAssignmentName, m_sPublisherID, m_sManagerID, messageText);
    //messageBox机制
    return m_fReward;
}

