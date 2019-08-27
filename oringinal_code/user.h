#ifndef USER_H
#define USER_H
/*************************************************************************
【文件名】               user.h
【功能模块和目的】         用户基本操作
【开发者及日期】           2019/7/21-31
*************************************************************************/
#include <QString>
#include <QMessageBox>
#include <QPixmap>
#include "certification.h"
#include "assignment.h"
#include "assignmentmanager.h"
#include "assignmentpublisher.h"
#include "assignmenttranslator.h"
#include <QVector>

/*************************************************************************
【类名】            User
【功能】            实现用户基本功能
【接口说明】         set接口：设置类内部私有变量；get接口：获取类内部私有变量；SignUp报名接口
【开发者及日期】     2019/7/21-31
【更改记录】        2019/7/31 更新重大BUG
*************************************************************************/
class User
{
public:
    User();
    User(const QString& username, const QString& passWord, const int& score = 10, const float& money = 0,
         const QString& id = "", const QString& email = "");                         //仅在注册时使用
    User(const QString& id);      //调用时使用
    virtual ~User();

    certification m_certification;
    QVector<Assignment>           all_assignment;
    QVector<AssignmentManager>    m_userAsManager;
    QVector<AssignmentPublisher>  m_userAsPublisher;
    QVector<AssignmentTranslator> m_userAsTrans;

    bool signUpForManager(const QString& assignmentName);
    bool signUpForTran(const QString& assignmentName);
    void signUpForPublisher(const AssignmentPublisher& assPublisher);

    void getAllAssignment();
    void getAllAssignment(const QVector<Assignment>& alist);
    void getUserAssignment();
    bool getUserCertification();

    inline QString getID() const
    {
        return m_sId;
    }

    inline QString getUserName() const
    {
        return m_sUserName;
    }

    inline int getScore() const
    {
        return m_iScore;
    }

    inline float getMoney() const
    {
        return m_fMoney;
    }

    inline QString getPassword() const
    {
        return m_sPassWord;
    }

    inline QString getEmail() const
    {
        return m_sEmail;
    }

    inline QPixmap getPix() const
    {
        return m_pixPicture;
    }

    inline void setMoney(const float& m)
    {
        m_bMoneyChanged = true;
        m_fMoney = m;
    }

    inline void setScore(const int& s)
    {
        m_bScoreChanged = true;
        m_iScore = s;
    }

    bool resetUserName(const QString& newUserName);
    bool resetPassWord(const QString& oldPassWord, const QString& newPassWord);
    void setPix(const QPixmap& pix);
    void setEmail(const QString& email);
private:
    QString m_sId;
    QString m_sUserName;
    QString m_sPassWord;
    QString m_sEmail;
    int     m_iScore;                   //积分
    float   m_fMoney;                   //余额
    QPixmap m_pixPicture;

    bool    m_bUserNameChanged;
    bool    m_bPasswordChanged;
    bool    m_bScoreChanged;
    bool    m_bMoneyChanged;
    bool    m_bPixChanged;
    bool    m_bEmailchanged;
};

#endif // USER_H
