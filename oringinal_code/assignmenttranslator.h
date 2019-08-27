#ifndef ASSIGNMENTTRANSLATOR_H
#define ASSIGNMENTTRANSLATOR_H

/*************************************************************************
【文件名】                 assignmentTranslaTor
【功能模块和目的】          实现任务抽象展示界面，设置接口跳转到详细任务界面
【开发者及日期】           2019/7/29-7/30
*************************************************************************/
#include "assignment.h"
#include "textinteraction.h"


//用户能够查看翻译子任务，可以查看上次暂存（提交）的 翻译文字并可以删改，继续翻译并暂存和提交。
//同时该用户还应该能够看到负责人 给出的历史反馈信息。在任务结束后，能够领取酬金。

/*************************************************************************
【类名】              AssignmentTranslator
【功能】             实现任务翻译者功能
【接口说明】         set接口：设置类内部私有变量；get接口：获取类内部私有变量；虚函数重载实现ddl的设定与任务文本上传
【开发者及日期】      2019/7/29-7/30
【更改记录】
*************************************************************************/
class AssignmentTranslator:public Assignment
{
public:
    AssignmentTranslator();
    AssignmentTranslator(const QString& tranID, const QString& assignmentName);
    ~AssignmentTranslator();

    bool uploadText(const QString& filePath);           //上传译稿
    void editTextOnline(const QString& text);         //在线编辑
    const TextInteraction& getTranlatedText() const
    {
        return m_translatedText;
    }

    const TextInteraction& getReview() const
    {
        return m_managerReview;
    }

    const TextInteraction& getSubAssignment() const
    {
        return m_subAssignment;
    }

    const QString getUserId() const
    {
        return m_sUserId;
    }

private:
    TextInteraction m_subAssignment;                   //分配的子任务
    TextInteraction m_translatedText;                  //翻译好的子任务或暂存的子任务
    TextInteraction m_managerReview;                   //历史评价
};

#endif // ASSIGNMENTTRANSLATOR_H
