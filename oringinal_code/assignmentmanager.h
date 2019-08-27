#ifndef ASSIGNMENTMANAGER_H
#define ASSIGNMENTMANAGER_H

/*************************************************************************
【文件名】                 assignmentManager
【功能模块和目的】          实现负责人任务类基本要求
【开发者及日期】           2019/7/29-
*************************************************************************/
#include "assignment.h"
#include "signupinteraction.h"
#include "textinteraction.h"
#include <QVector>
#include <QMap>
//负责人报名，被发布者选为负责人后，会为该任务招募并确定合格的译者。此后，将整个翻译任务拆分成若干个子任务， 例如，将《The Inevitable》的每一章翻译作为一个子任务，分配给各个译者
//译者翻译所领取的子任务，负责人对其所提交的译文进行审核并提出修改意见。
//所有章节的译文审核通过后，负责人将全部译稿提交给任务发布者。

//对于负责人（每个任务只有一人），他主要负责选取有资质的译者，
//并将翻译资料以子任务的形式发放给各个译者。最终需要对译者提交的译稿进行质检，并将质检后的全文译稿整合提交给任务发布者；



/*************************************************************************
【类名】             AssignmentManager
【功能】             实现负责人任务基本功能
【接口说明】         set接口：设置类内部私有变量；get接口：获取类内部私有变量；虚函数重载实现ddl的设定；其余接口与任务相关
【开发者及日期】     2019/7/29-7/30
【更改记录】
*************************************************************************/

class AssignmentManager:public Assignment
{
public:
    AssignmentManager();
    AssignmentManager(const QString& assignmentName);                               //加载数据
    ~AssignmentManager();


    void setReward(const float&);                                                   //支付给译者的酬金
    void setCurrentDDL(const QDateTime& ddl);                                       //报名截止ddl

    bool chooseTranslator(const QString& tranID);
    void setDDL(const QDateTime& ddl);                                              //翻译任务ddl

    bool allocateAssignment(const QString& tranID, const QString& filePath);
    void giveReview(const QString& tranID, const QString& review);
    void setStatusProcess();
    void setStatusDone();

    float payReward();
    bool uploadText(const QString& filePath);
    const QVector<SignUpInteraction>& getTranSignUp() const
    {
        return m_translatorSignUp;
    }

    const QMap<QString, TextInteraction>& getSubAssignment() const
    {
        return m_subAssignment;
    }

    const QMap<QString, TextInteraction>& getSubTranslated() const
    {
        return m_subTranlatedAssignment;
    }

    const QMap<QString, TextInteraction>& getReview() const
    {
        return m_review;
    }

    const TextInteraction& getFinalText() const
    {
        return m_finalText;
    }

private:
    QVector<SignUpInteraction> m_translatorSignUp;                                      //译者报名情况

    QMap<QString, TextInteraction> m_subAssignment;                                     //分配子任务
    QMap<QString, TextInteraction> m_subTranlatedAssignment;                            //储存翻译好的子任务
    QMap<QString, TextInteraction> m_review;                                            //储存历史评价

    TextInteraction m_finalText;                  //最终翻译好的任务
};

#endif // ASSIGNMENTMANAGER_H
