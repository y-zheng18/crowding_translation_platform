#include "messageinformbox.h"
#include "database.h"
MessageInformBox::MessageInformBox()
{

}

MessageInformBox::MessageInformBox(const QString& id):m_sUserId(id)
{
    DataBaseMessage db;
    db.getMessage(*this);
}

MessageInformBox::~MessageInformBox()
{
    if (m_sUserId == "")
        return;
    DataBaseMessage db;
    db.updateMessage(m_sUserId);
}

/*************************************************************************
【函数名称】        delete_Message
【函数功能】        删除消息列表
【参数】
【返回值】
【开发者及日期】     7/26
*************************************************************************/
void MessageInformBox::delete_Message()
{
    DataBaseMessage db;
    db.deleteMessage(m_sUserId);
    while (!m_newMessage.empty())
    {
        m_newMessage.pop_back();
    }
    while (!m_oldMessage.empty())
    {
        m_oldMessage.pop_back();
    }
}



Message::Message()
{

}

Message::Message(const QDateTime& time, const QString& assignmentName, const QString& sender,
                 const QString& receiver, const QString& text, const MESSAGE_STATUS& status):
    m_send_time(time), m_assignmentName(assignmentName), m_senderID(sender), m_receiverID(receiver),
    m_messageText(text), m_eIsRECEIVED(status)
{
}


Message::~Message()
{
    if (m_eIsRECEIVED == NEW)
    {
        DataBaseMessage db;
        db.insertMessage(*this);        //析构时存档
    }
}
