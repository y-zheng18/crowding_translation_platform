#include "user.h"
#include "database.h"
#include <QTime>
#include <QDebug>

User::User()
{
    m_bUserNameChanged = false;
    m_bMoneyChanged = false;
    m_bScoreChanged = false;
    m_bPasswordChanged = false;
    m_bPixChanged = false;
    m_bEmailchanged = false;
}

/*************************************************************************
【函数名称】       User
【函数功能】        加载数据
【参数】           类成员数据
【返回值】
【开发者及日期】     7/21
*************************************************************************/
User::User(const QString& username, const QString& passWord, const int& score, const float& money, const QString& id, const QString& email):
    m_sUserName(username), m_sPassWord(passWord), m_sEmail(email), m_iScore(score), m_fMoney(money)
{
    m_bUserNameChanged = false;
    m_bMoneyChanged = false;
    m_bScoreChanged = false;
    m_bPasswordChanged = false;
    m_bPixChanged = false;
    m_bEmailchanged = false;
    if (id == "")
    {
        QDateTime dt = QDateTime::currentDateTime();
        int year = dt.date().year();
        int month = dt.date().month();
        int day = dt.date().day();
        int hour = dt.time().hour();
        int minute = dt.time().minute();
        int second = dt.time().second();
        QString sYear = QString("%1").arg(year, 4, 10, QLatin1Char('0'));           //自动补0
        QString sMonth = QString("%1").arg(month, 2, 10, QLatin1Char('0'));           //自动补0
        QString sDay = QString("%1").arg(day, 2, 10, QLatin1Char('0'));           //自动补0
        QString sHour = QString("%1").arg(hour, 2, 10, QLatin1Char('0'));           //自动补0
        QString sMinute = QString("%1").arg(minute, 2, 10, QLatin1Char('0'));           //自动补0
        QString sSecond = QString("%1").arg(second, 2, 10, QLatin1Char('0'));           //自动补0
        m_sId = QString("%1%2%3%4%5%6").arg(sYear).arg(sMonth).arg(sDay).arg(sHour).arg(sMinute).arg(sSecond);
    }
    else
    {
        m_sId = id;
    }
    m_certification.set_checked(false);
}
/*************************************************************************
【函数名称】       User
【函数功能】       构造函数， 通过数据库加载数据
【参数】           类成员数据
【返回值】
【开发者及日期】     7/24
*************************************************************************/
User::User(const QString& id)
{
    m_bUserNameChanged = false;
    m_bMoneyChanged = false;
    m_bScoreChanged = false;
    m_bPasswordChanged = false;
    m_bPixChanged = false;
    m_bEmailchanged = false;
    DataBaseUser db;
    *this = db.getUser(id);            //通过数据库直接加载对象
    if (m_sId == "")                                   //数据库不存在该用户
    {
    }
}

/*************************************************************************
【函数名称】       ~User
【函数功能】        写入数据
【参数】           类成员数据
【返回值】
【开发者及日期】     7/25
*************************************************************************/
User::~User()       //析构时存档
{
    if (m_sId == "")
        return;
    DataBaseUser db;
    DataBasePicture db_p;
    if (!db.search(m_sId, "id"))
    {
        db.insertUser(*this);                               //写入数据库
        db_p.insertPictures(m_sId, m_pixPicture);
    }
    else
    {
        if (m_bUserNameChanged)
        {
            db.updateData(m_sId,  m_sUserName, "username");
        }
        if (m_bPasswordChanged)
        {
            db.updateData(m_sId, m_sPassWord, "password");
        }
        if (m_bPixChanged)
        {
            db_p.updataPixture(m_sId, m_pixPicture);
        }
        if (m_bMoneyChanged)
        {
            db.updateFloat(m_sId, m_fMoney);
        }
        if (m_bScoreChanged)
        {
            db.updateInt(m_sId, m_iScore);
        }
        if (m_bEmailchanged)
        {
            db.updateData(m_sId, m_sEmail, "email");
        }
    }
}

/*************************************************************************
【函数名称】       signUpForManager
【函数功能】        负责人报名
【参数】           任务名
【返回值】
【开发者及日期】     7/27
*************************************************************************/
bool User::signUpForManager(const QString& assignmentName)
{
    Assignment asmt(assignmentName);
    if (asmt.get_deadline() < QDateTime::currentDateTime())
    {
        return false;
    }
    if (asmt.getStatus() != RECRUITING_MANAGER)
    {
        return false;
    }
    SignUpInteraction signUp(assignmentName, asmt.getPublisherID(), m_sId);
    signUp.setPlatForm(MANAGER_SIGN_UP);
    DataBaseAssignment db;
    if (!db.updateSignUp(signUp))
    {
        db.insertSignUp(signUp);
    }
    QString messageText = QString("您的任务 %1 有新报名").arg(assignmentName);
    Message m(QDateTime::currentDateTime(), assignmentName,m_sId, asmt.getPublisherID(), messageText);
    return true;
}

/*************************************************************************
【函数名称】       signUpForTran
【函数功能】        译者报名
【参数】           任务名
【返回值】
【开发者及日期】     7/27
*************************************************************************/
bool User::signUpForTran(const QString& assignmentName)
{
    Assignment asmt(assignmentName);
    if (asmt.get_deadline() < QDateTime::currentDateTime())
    {
        return false;
    }
    if (asmt.getStatus() != RECRUITING_TRANSLATOR)
    {
        return false;
    }
    SignUpInteraction signUp(asmt.getName(), asmt.getManagerID(), m_sId);
    signUp.setPlatForm(TRANS_SIGN_UP);
    DataBaseAssignment db;
    if (!db.updateSignUp(signUp))
    {
        db.insertSignUp(signUp);
    }
    QString messageText = QString("您的任务 %1 有新报名").arg(assignmentName);
    Message m(QDateTime::currentDateTime(), assignmentName, m_sId, asmt.getManagerID(), messageText);
    return true;

}

/*************************************************************************
【函数名称】       signUpForPublisher
【函数功能】        发布任务
【参数】           任务发布者引用
【返回值】
【开发者及日期】     7/27
*************************************************************************/
void User::signUpForPublisher(const AssignmentPublisher& assPublisher)
{
    m_userAsPublisher.push_back(assPublisher);
    Assignment assgnmnt = assPublisher;
    all_assignment.push_back(assgnmnt);
}

/*************************************************************************
【函数名称】       getAllAssignment
【函数功能】       获取所有任务
【参数】
【返回值】
【开发者及日期】     7/31
*************************************************************************/
void User::getAllAssignment()
{
    if (all_assignment.size() == 0)
    {
        DataBaseAssignment dba;
        all_assignment = dba.getAllAssignment();
    }
}

void User::getAllAssignment(const QVector<Assignment>& alist)
{
    all_assignment = alist;
}

/*************************************************************************
【函数名称】       getUserAssignment
【函数功能】       获取用户参与任务
【参数】
【返回值】
【开发者及日期】     7/27
*************************************************************************/
void User::getUserAssignment()
{
    if (all_assignment.size() == 0)
    {
        DataBaseAssignment dba;
        all_assignment = dba.getAllAssignment();
    }
    m_userAsTrans.clear();
    m_userAsManager.clear();
    m_userAsPublisher.clear();
    for (int i = 0;i < all_assignment.size();i++)
    {
        if (all_assignment[i].getPublisherID() == m_sId)
        {
            m_userAsPublisher.push_back(AssignmentPublisher(all_assignment[i].getName()));
        }
        else if (all_assignment[i].getManagerID() == m_sId)
        {
            m_userAsManager.push_back(AssignmentManager(all_assignment[i].getName()));
        }
        else
        {
            QStringList trans = all_assignment[i].getTranslaors();
            for (int j = 0;j < trans.size();j++)
            {
                if (trans[j] == m_sId)
                {
                    m_userAsTrans.push_back(AssignmentTranslator(m_sId, all_assignment[i].getName()));
                }
            }
        }
    }
}

bool User::getUserCertification()
{

    m_certification = certification(m_sId);
}

/*************************************************************************
【函数名称】       resetUserName
【函数功能】      重设用户名，判断合法性
【参数】
【返回值】
【开发者及日期】     7/25
*************************************************************************/
bool User::resetUserName(const QString& newUserName)
{
    DataBaseUser db;
    if (!db.search(newUserName))
    {
        m_sUserName = newUserName;
        m_bUserNameChanged = true;
        return true;
    }
    //qDebug()<<m_sUserName<<" "<< newUserName<<endl;
    return false;
}

bool User::resetPassWord(const QString &oldPassWord, const QString &newPassWord)
{
    if (QString::localeAwareCompare(oldPassWord, m_sPassWord) == 0)     //密码匹配
    {
        m_sPassWord = newPassWord;
        m_bPasswordChanged = true;
        return true;
    }
    qDebug()<<"WrongPASSWORD!";
    return false;
}

void User::setPix(const QPixmap& pix)
{
    m_bPixChanged = true;
    m_pixPicture = pix;
}

void User::setEmail(const QString& email)
{
    m_sEmail = email;
    m_bEmailchanged = true;
}
