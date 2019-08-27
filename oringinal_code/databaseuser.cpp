#include "database.h"

DataBaseUser::DataBaseUser()
{
    m_sDataBase = openDataBase();
    m_tableName = "userMessage";
    m_table_parameters = "(id varchar(15) primary key,"
                         "password varchar(15),"
                         "username varchar(20),"
                         "money float,"
                         "score int)";
    //m_dataBaseName = "test.db";
}

DataBaseUser::~DataBaseUser()
{
}


/*************************************************************************
【函数名称】        insertUser
【函数功能】        插入用户类对象
【参数】           用户类对象
【返回值】          是否插入成功
【开发者及日期】     7/21
*************************************************************************/
bool DataBaseUser::insertUser(const User& m_user)
{
    QSqlQuery query(m_sDataBase);
    QString sql_create = "create table if not exists userMessage"
                         "(id varchar(15) primary key,"
                         "password varchar(15),"
                         "username varchar(20),"
                         "money float,"
                         "score int,"
                         "email varchar(30))";
    if (!query.exec(sql_create))
    {
        qDebug()<<"userMessage error"<<query.lastError();
    }
    QString username = m_user.getUserName();
    QString userID = m_user.getID();
    QString userPassword = m_user.getPassword();
    QString email = m_user.getEmail();
    float userMoney = m_user.getMoney();
    int userScore = m_user.getScore();
    QString value = QString("('%1', '%2', '%3', %4, %5, '%6')").arg(userID)
            .arg(userPassword).arg(username).arg(userMoney).arg(userScore).arg(email);
    QString insert = QString("insert into userMessage values %1").arg(value);
    if (!query.exec(insert))
    {
        qDebug()<<"InsertUserMassage error!"<<query.lastError();
        return false;
    }
    return true;
}

/*************************************************************************
【函数名称】        search
【函数功能】        查找用户是否存在
【参数】           用户参数
【返回值】          bool
【开发者及日期】     7/21
*************************************************************************/
bool DataBaseUser::search(const QString& key, const QString& parameter)
{
    QSqlQuery query(m_sDataBase);
    QString select_sql = QString("select * from %1 where %2 = '%3'").arg(m_tableName).arg(parameter).arg(key);
    if (!query.exec(select_sql))
    {
        qDebug()<<"searchUser error"<<query.lastError();
    }
    while (query.next())
    {
        return true;
    }
    return false;
}
/*************************************************************************
【函数名称】        updateData
【函数功能】        更新用户信息
【参数】           用户待更新信息
【返回值】          是否更新成功
【开发者及日期】     7/22
*************************************************************************/
bool DataBaseUser::updateData(const QString& id, const QString& value, const QString& parameter)
{
    QSqlQuery query(m_sDataBase);
    QString update_sql = QString("update %1 set %2 = :%2 where id = '%3'")
            .arg(m_tableName).arg(parameter).arg(id);
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), value);
    if (!query.exec())
    {
        qDebug()<<"updateUser error!"<<query.lastError();
        return false;
    }
    return true;
}


/*************************************************************************
【函数名称】        updateInt
【函数功能】        更新用户信息
【参数】           用户待更新信息
【返回值】          是否更新成功
【开发者及日期】     7/22
*************************************************************************/
bool DataBaseUser::updateInt(const QString &id, const int &value, const QString& parameter)
{
    QSqlQuery query(m_sDataBase);
    QString update_sql = QString("update %1 set %2 = :%2 where id = '%3'")
            .arg(m_tableName).arg(parameter).arg(id);
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), value);
    if (!query.exec())
    {
        qDebug()<<"updateInt error!"<<query.lastError();
        return false;
    }
    return true;
}


/*************************************************************************
【函数名称】        updateData
【函数功能】        更新用户信息
【参数】           用户待更新信息
【返回值】          是否更新成功
【开发者及日期】     7/22
*************************************************************************/
bool DataBaseUser::updateFloat(const QString& id, const float& value, const QString& parameter)
{
    QSqlQuery query(m_sDataBase);
    QString update_sql = QString("update %1 set %2 = :%2 where id = '%3'")
            .arg(m_tableName).arg(parameter).arg(id);
    query.prepare(update_sql);
    query.bindValue(QString(":%2").arg(parameter), value);
    if (!query.exec())
    {
        qDebug()<<"updateFloat error!"<<query.lastError();
        return false;
    }
    return true;
}
/*************************************************************************
【函数名称】        getUser
【函数功能】        获取用户列表
【参数】
【返回值】         用户对象列表
【开发者及日期】     7/26
*************************************************************************/
QVector<User> DataBaseUser::getUser()
{
    QSqlQuery query(m_sDataBase);
    QString select_sql = QString("select id from userMessage");
    if (!query.exec(select_sql))
    {
        qDebug()<<"select error!"<<query.lastError();
    }
    QStringList id;
    while (query.next())
    {
        id.push_back(query.value(0).toString());
    }
    QVector<User>  all_u;
    for (int i = 0;i < id.size();i++)
    {
        all_u.push_back(getUser(id[i]));
    }
    return all_u;
}


/*************************************************************************
【函数名称】        getUser
【函数功能】        获取用户
【参数】           用户id
【返回值】         用户对象
【开发者及日期】     7/26
*************************************************************************/
User DataBaseUser::getUser(const QString& id)
{
    if (!m_sDataBase.open())
        m_sDataBase = openDataBase();
    QSqlQuery query(m_sDataBase);

    //加载基本信息
    QString select_sql = QString("select username, password, money, score, email from userMessage where id = '%1'").arg(id);
    if (!query.exec(select_sql))
    {
        qDebug()<<"getUser fail bug1"<<query.lastError();
    }
    User m_user;
    while (query.next())
    {
        QString username = query.value(0).toString();
        QString password = query.value(1).toString();
        float money = query.value(2).toFloat();
        int score = query.value(3).toInt();
        QString email = query.value(4).toString();
        m_user = User(username, password, score, money, id, email);
    }
    if(m_user.getUserName() == "")
    {
        return m_user;
    }

    //加载头像
    select_sql = QString("select pixels from userPicture "
                                 "where id = '%1'").arg(id);
    QByteArray byteArray;
    QPixmap picture;
    if (!query.exec(select_sql))
    {
        qDebug()<<"getUserPicture fail! bug2"<<query.lastError();
    }
    else
    {
        while (query.next())
        {
            byteArray = query.value(0).toByteArray();
            QPixmap pix;
            pix.loadFromData(byteArray,"PNG");
            picture = pix;
            break;
        }
    }
    m_user.setPix(picture);
    return m_user;
}


/*************************************************************************
【函数名称】        getUserByName
【函数功能】        通过用户名获取用户
【参数】           用户名
【返回值】         用户对象
【开发者及日期】     7/29
*************************************************************************/
User DataBaseUser::getUserByName(const QString& name)
{
    if (!m_sDataBase.open())
        m_sDataBase = openDataBase();
    QSqlQuery query(m_sDataBase);

    //加载基本信息
    QString id;
    QString select_sql = QString("select id from userMessage where username = '%1'").arg(name);
    if (!query.exec(select_sql))
    {
        qDebug()<<"getUser fail bug2"<<query.lastError();
    }
    while (query.next())
    {
        id = query.value(0).toString();
    }
    return getUser(id);
}
