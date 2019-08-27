#ifndef MESSAGEINFORMBOX_H
#define MESSAGEINFORMBOX_H
/*************************************************************************
【文件名】                 messageInformBox.h
【功能模块和目的】          消息盒子类
【开发者及日期】           2019/7/25-7/26
*************************************************************************/
#include <QString>
#include <QVector>
#include <QDateTime>
#include "textinteraction.h"

enum MESSAGE_STATUS{NEW, OLD};


/*************************************************************************
【类名】             Message
【功能】             消息存取（新报名、新ddl等）
【接口说明】         get/set进行成员获取与设置
【开发者及日期】      2019/7/25-26
【更改记录】
*************************************************************************/
class Message
{
public:
    Message();
    Message(const QDateTime&, const QString&, const QString&, const QString&, const QString&, const MESSAGE_STATUS& = NEW);
    virtual ~Message();


    const QDateTime& get_send_time() const
    {
        return m_send_time;
    }
    const MESSAGE_STATUS& isReceived() const
    {
        return m_eIsRECEIVED;
    }
    const QString& get_Assignment() const
    {
        return m_assignmentName;
    }
    const QString& get_senderID() const
    {
        return m_senderID;
    }
    const QString& get_receiverID() const
    {
        return m_receiverID;
    }
    const QString& get_messageText() const
    {
        return m_messageText;
    }

    void Received()
    {
        m_eIsRECEIVED = OLD;
    }

private:
    QDateTime m_send_time;
    QString m_assignmentName;
    QString m_senderID;
    QString m_receiverID;
    QString m_messageText;
    MESSAGE_STATUS m_eIsRECEIVED;
};

/*************************************************************************
【类名】             MessageInformBox
【功能】             用户消息盒子，储存历史消息与新消息
【接口说明】         get/set对成员进行获取与赋值
【开发者及日期】      2019/7/25-26
【更改记录】
*************************************************************************/
class MessageInformBox
{
public:
    MessageInformBox();
    MessageInformBox(const QString&);
    ~MessageInformBox();

    const QString& getUser()
    {
        return m_sUserId;
    }

    void setUserId(const QString& id)
    {
        m_sUserId = id;
    }

    const QVector<Message>& getNew() const
    {
        return m_newMessage;
    }

    const QVector<Message>& getOld() const
    {
        return m_oldMessage;
    }

    void setNewMessage(const QVector<Message>& newMessage)
    {
        m_newMessage = newMessage;
    }

    void setOldMessage(const QVector<Message>& oldMessage)
    {
        m_oldMessage = oldMessage;
    }


    void delete_Message();
private:
    QString m_sUserId;
    QVector<Message> m_newMessage;
    QVector<Message> m_oldMessage;        //历史记录
};

#endif // MESSAGEINFORMBOX_H
