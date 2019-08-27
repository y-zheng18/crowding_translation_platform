#ifndef TEXTINTERACTION_H
#define TEXTINTERACTION_H
/*************************************************************************
【文件名】                textinteraction.h
【功能模块和目的】          文本交互平台
【开发者及日期】           2019/7/24
*************************************************************************/
#include <QString>


//文本交互平台，功能为：任务发布者发布文本（负责人下载待翻译文本），
//负责人上传译文(发布者接收整合好的文本)，
//负责人下发待翻译文本（译者下载文本），译者上传译文
//储存格式为：任务发布者发布译文平台：任务名+负责人ID+待翻译
//          负责人整合上传译文平台：任务名+负责人ID+译文
//          负责人下发待翻译文本：任务名+负责子任务翻译者ID+待翻译文本
//          译者上传译文：任务名+负责子任务翻译者ID+译文
//          负责人对译者上传译文给出评价：任务名+负责子任务翻译者ID+译文

enum PLATFORM{MANAGER_DOWNLOAD, TRANS_DOWNLOAD, TRANS_UPLOAD, MANAGER_UPLOAD, MANAGER_REVIEW};
/*************************************************************************
【类名】             TextInteraction
【功能】             实现文本信息交互
【接口说明】         set接口：设置类内部私有变量；get接口：获取类内部私有变量
【开发者及日期】      2019/7/24
【更改记录】
*************************************************************************/
class TextInteraction
{
public:
    TextInteraction(const QString& assignmentName = "", const QString& id = "",
                    const QString& text = "", const PLATFORM& form = MANAGER_DOWNLOAD);

    virtual ~TextInteraction();

    QString getName() const
    {
        return m_sAssignmentName;
    }

    QString getText() const
    {
        return m_sFileText;
    }

    QString getID() const
    {
        return m_sId;
    }

    PLATFORM getPlatForm() const
    {
        return m_ePlatform;
    }

    void setID(const QString& id);
    void setAssignmentName(const QString& name);
    void setFiletext(const QString& text);
    void setPlatForm(const PLATFORM& form);
private:
    QString m_sAssignmentName;
    QString m_sId;
    QString m_sFileText;
    PLATFORM m_ePlatform;
};

#endif // TEXTINTERACTION_H
