#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H
/*************************************************************************
【文件名】                 assignment
【功能模块和目的】          实现抽象任务类基本要求
【开发者及日期】           2019/7/23-8/1
*************************************************************************/

#include <QString>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QPixmap>
#include <QDateTime>
#include "messageinformbox.h"

enum STATUS{RECRUITING_MANAGER, RECRUITING_TRANSLATOR, PROCCESSING, ASSIGNMENT_DONE, MANAGER_RECUIT_DONE};
enum LANGUAGE{CHINESE_TO_ENGLISH, ENGLISH_TO_CHINESE};


/*************************************************************************
【类名】             Assignment
【功能】             实现任务基本功能，展示任务基本属性（如ddl、发布者等）
【接口说明】         set接口：设置类内部私有变量；get接口：获取类内部私有变量；虚函数setDDL、downloadText等便于子类重载，利于实现多态
【开发者及日期】     2019/7/23-8/1
【更改记录】         2019/7/28 新增set等设置接口，便于操作，2019/8/1 新增set等设置接口，便于操作
*************************************************************************/

class Assignment
{
public:
    Assignment();
    Assignment(const QString& assignmentName,
               const QString& publisherID,
               const QString& managerID,
               const QStringList& translatorID,
               const QString& description,
               const int&   status,
               const int& form,
               const float& reward,
               const QString& assignmentText,
               const QStringList& keywords = QStringList(),
               const QPixmap& pix = QPixmap());                    //加载数据时使用
    Assignment(const QString& assignmentName);                  //加载数据时使用
    Assignment(const QString& id,const QString& assignmentName);//第一次定义时使用
    virtual ~Assignment();

    inline QString getName() const
    {
        return m_sAssignmentName;
    }

    inline QString getText() const
    {
        return m_sAssignmentText;
    }

    inline float getReward() const
    {
        return m_fReward;
    }

    inline QString getDescription() const
    {
        return m_sDescription;
    }

    inline QPixmap getPix() const
    {
        return m_pixPicture;
    }

    inline QDateTime get_deadline() const
    {
        return m_deadline;
    }

    inline QDateTime get_currentDDL() const
    {
        return m_currentDDL;
    }

    void setStatus(const STATUS s);
    void setTranslators(const QStringList& l);
    QString getPublisherID ()const;
    QString getManagerID() const;
    QStringList getTranslaors() const;
    QStringList getKeywords() const;
    int getStatus() const;
    int getTranslationForm() const;
    void setPix(const QPixmap& pix);
    virtual bool uploadText(const QString&);                  //上传文本，不同身份不同上传方式，方便实现多
    virtual bool downloadText();                              //从数据库中下载

    virtual void setDDL(const QDateTime& ddl);               //任务ddl
    virtual void setCurrentDDL(const QDateTime& ddl);        //报名ddl、子任务ddl等

protected:
    QString       m_sAssignmentName;

    QString       m_sUserId;                //利用userID进行存储操作,此处userID为登录者，其身份可以是负责人、翻译者、发布者等
    QString       m_sPublisherID;           //该任务发布者ID
    QString       m_sManagerID;             //该任务负责人ID
    QStringList   m_slTranslatorID;         //译者ID

    QString       m_sAssignmentText;
    QString       m_sDescription;           //任务描述
    enum STATUS   m_eStatus;                //任务状态
    enum LANGUAGE m_eTranslationForm;
    float         m_fReward;
    QPixmap       m_pixPicture;

    QDateTime     m_deadline;
    QDateTime     m_currentDDL;
    QStringList   m_keyWords;
};



#endif // ASSIGNMENT_H
