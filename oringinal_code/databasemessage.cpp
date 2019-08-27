#include "database.h"


DataBaseMessage::DataBaseMessage()
{
    m_sDataBase = openDataBase();
    m_tableName = "messages";
}

DataBaseMessage::~DataBaseMessage()
{
}


/*************************************************************************
【函数名称】        insertMessage
【函数功能】        插入消息类对象
【参数】           消息类对象
【返回值】          是否插入成功
【开发者及日期】     7/29
*************************************************************************/
bool DataBaseMessage::insertMessage(const Message& newMessage)
{
    QSqlQuery query(m_sDataBase);
    QString sql_create = "create table if not exists messages"
                         "(assignmentName varchar(30),"
                         "senderID varchar(20),"
                         "receiverID varchar(20),"
                         "messageText varchar(255),"
                         "time varchar(30),"
                         "isReceived int)";

    if (!query.exec(sql_create))
    {
        qDebug()<<"message create error"<<query.lastError();
    }
    QDateTime time = newMessage.get_send_time();
    QString assgnmtName = newMessage.get_Assignment();
    QString senderID = newMessage.get_senderID();
    QString receiverID = newMessage.get_receiverID();
    QString text = newMessage.get_messageText();
    int year = time.date().year();
    int month = time.date().month();
    int day = time.date().day();
    int hour = time.time().hour();
    int minute = time.time().minute();
    QString sendtime = QString("%1 %2 %3 %4 %5").arg(year).arg(month).arg(day).arg(hour).arg(minute);
    QString value = QString("('%1', '%2', '%3', '%4', '%5', '%6')").arg(assgnmtName)
            .arg(senderID).arg(receiverID).arg(text).arg(sendtime).arg(int(NEW));
    QString insert = QString("insert into messages values %1").arg(value);
    if (!query.exec(insert))
    {
        qDebug()<<"InsertMassage error!"<<query.lastError();
        return false;
    }
    return true;
}


/*************************************************************************
【函数名称】        updateMessage
【函数功能】        更新消息类对象
【参数】           消息类对象
【返回值】          是否更新成功
【开发者及日期】     7/29
*************************************************************************/
bool DataBaseMessage::updateMessage(const QString& id)
{
    QSqlQuery query(m_sDataBase);
    QString parameter = "isReceived";
    QString update_sql = QString("update messages set %1 = :%1 where receiverID = '%2' and isReceived == 0")
            .arg(parameter).arg(id);
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), int(OLD));
    if (!query.exec())
    {
        qDebug()<<"update message error!"<<query.lastError();
        return false;
    }
    return true;
}


/*************************************************************************
【函数名称】        deleteMessage
【函数功能】        删除消息类对象
【参数】           消息接受者id
【返回值】          是否删除成功
【开发者及日期】     7/29
*************************************************************************/
bool DataBaseMessage::deleteMessage(const QString& id)
{
    QSqlQuery query(m_sDataBase);
    QString delete_sql = QString("delete from messages where receiverID = '%1'").arg(id);
    if (!query.exec(delete_sql))
    {
        qDebug()<<"delete message error!"<<query.lastError();
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】        getMessage
【函数功能】        获取消息盒子
【参数】           消息盒子对象引用
【返回值】          是否获取成功
【开发者及日期】     7/29
*************************************************************************/
bool DataBaseMessage::getMessage(MessageInformBox &box)
{
    QVector<Message> newMessages;
    QVector<Message> oldMessages;
    QSqlQuery query(m_sDataBase);
    QString select_sql = QString("select assignmentName, senderID, messageText, time "
                                 "from messages where receiverID = '%1' and isReceived = 0").arg(box.getUser());
    if (!query.exec(select_sql))
    {
        qDebug()<<"select message error!"<<query.lastError();
        return false;
    }
    while (query.next())
    {
        QString assgnmntName = query.value(0).toString();
        QString senderID = query.value(1).toString();
        QString text = query.value(2).toString();
        QString time = query.value(3).toString();

        int year = time.section(" ", 0, 0).toInt();
        int month = time.section(" ", 1, 1).toInt();
        int day = time.section(" ", 2, 2).toInt();
        int hour = time.section(" ", 3, 3).toInt();
        int minute = time.section(" ", 4, 4).toInt();
        QDateTime dt;
        QTime t;
        t.setHMS(hour, minute, 0);
        dt.setDate(QDate(year, month, day));
        dt.setTime(t);
        newMessages.push_back(Message(dt, assgnmntName, senderID, box.getUser(), text, OLD));
    }
    select_sql = QString("select assignmentName, senderID, messageText, time "
                         "from messages where receiverID = '%1' and isReceived = 1").arg(box.getUser());
    if (!query.exec(select_sql))
    {
        qDebug()<<"select message error!"<<query.lastError();
        return false;
    }
    while (query.next())
    {
        QString assgnmntName = query.value(0).toString();
        QString senderID = query.value(1).toString();
        QString text = query.value(2).toString();
        QString time = query.value(3).toString();

        int year = time.section(" ", 0, 0).toInt();
        int month = time.section(" ", 1, 1).toInt();
        int day = time.section(" ", 2, 2).toInt();
        int hour = time.section(" ", 3, 3).toInt();
        int minute = time.section(" ", 4, 4).toInt();
        QDateTime dt;
        QTime t;
        t.setHMS(hour, minute, 0);
        dt.setDate(QDate(year, month, day));
        dt.setTime(t);
        oldMessages.push_back(Message(dt, assgnmntName, senderID, box.getUser(), text, OLD));
    }
    box.setNewMessage(newMessages);
    box.setOldMessage(oldMessages);
    return true;
}
