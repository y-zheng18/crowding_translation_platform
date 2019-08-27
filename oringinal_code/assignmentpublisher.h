#ifndef ASSIGNMENTPUBLISHER_H
#define ASSIGNMENTPUBLISHER_H


/*************************************************************************
【文件名】                 assignmentManager
【功能模块和目的】          实现负责人任务类基本要求
【开发者及日期】           2019/7/29-7/30
*************************************************************************/

#include "assignment.h"
#include "textinteraction.h"
#include "signupinteraction.h"
#include <QVector>
//首先，任务发布者在平台上发布任务;其次，根据报名情况，任务发布者确定该书的负责人，
//其职能是统筹协调负责整本书的翻译；最后，发布者收取译稿，支付酬金


/*************************************************************************
【类名】             AssignmentPublisher
【功能】             实现发布者任务基本功能
【接口说明】         set接口：设置类内部私有变量；get接口：获取类内部私有变量；虚函数重载实现ddl的设定；其余接口与任务相关
【开发者及日期】     2019/7/28-7/30
【更改记录】
*************************************************************************/
class AssignmentPublisher:public Assignment
{
public:
    AssignmentPublisher();
    AssignmentPublisher(const QString& id, const QString& assignmentName);      //仅在第一次定义（发布任务）时使用
    AssignmentPublisher(const QString& assignmentName);                         //加载时使用
    ~AssignmentPublisher();

    inline void uploadDescription(const QString& description)
    {
        m_sDescription = description;
    }

    void    chooseManager(const QString& managerID);
    bool    uploadText(const QString& filePath);
    bool    setStatus(const int&);
    bool    setReward(const float&);
    bool    setTranlationForm(const int&);
    void    setDDL(const QDateTime& ddl);                                       //负责人报名截止ddl
    void    setCurrentDDL(const QDateTime& ddl);
    bool    uploadPictureMessage(const QString& fileName);
    void    addKeywords(const QString& key);
    float    payReward();
    bool    downloadText();
    QString getFinalTranslation();
    const QVector<SignUpInteraction>& getSignUp() const;
private:
    TextInteraction m_textManagement;                                              //用来上传待翻译文本，由负责人接收
    TextInteraction m_finalText;                                                  //用来下载已翻译好文本，由负责人上传
    QVector<SignUpInteraction> m_managerSignUp;                                   //负责人报名情况
};

#endif // ASSIGNMENTPUBLISHER_H
